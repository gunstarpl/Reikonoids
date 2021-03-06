#pragma once

#include <UObject/Object.h>
#include "RModifier_Base.generated.h"

class AActor;

UCLASS(EditInlineNew)
class REIKONOIDS_API URModifier_Base : public UObject
{
    GENERATED_BODY()

public:
    virtual ~URModifier_Base();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FText Name = NSLOCTEXT("Modifier", "Unnamed", "Unnamed");

    UPROPERTY(EditDefaultsOnly)
    float InitialDuration = 0.0f;

    UPROPERTY(EditDefaultsOnly)
    bool ReplaceExisting = true;

protected:
    friend class URModifierStackComponent;
    URModifier_Base();

    virtual bool Apply(AActor* ModifiedActor);
    virtual void Tick(float DeltaTime);
    virtual void Revert();

    bool IsExpired() const;

    float RemainingDuration = 0.0f;
};
