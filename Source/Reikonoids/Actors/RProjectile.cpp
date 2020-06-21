#include "RProjectile.h"
#include <Components/SphereComponent.h>

ARProjectile::ARProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Setup sphere collision component.
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    SphereCollision->SetSphereRadius(16.0f);
    RootComponent = SphereCollision;
}

void ARProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    // React when projectile hits another actor.
    AActor::OnActorBeginOverlap.AddDynamic(this, &ARProjectile::OnActorBeginOverlap);
}

void ARProjectile::BeginPlay()
{
    Super::BeginPlay();

    // Expire projectile when life time ends.
    GetWorld()->GetTimerManager().SetTimer(LifetimeTimer, this, &ARProjectile::OnExpire, LifeTime, false);

    // Orientate projectile towards direction.
    SetActorRotation(Direction.ToOrientationRotator());
}

void ARProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Move projectile forward at constant speed with sweep enabled.
    SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime, true);
}

void ARProjectile::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    // Make hit actor receive damage.
    if(OtherActor != nullptr)
    {
        FDamageEvent DamageEvent;
        OtherActor->TakeDamage(Damage, DamageEvent, nullptr, this);
    }

    // Destroy projectile.
    Destroy();
}

void ARProjectile::OnExpire()
{
    // Destroy when life time ends.
    Destroy();
}
