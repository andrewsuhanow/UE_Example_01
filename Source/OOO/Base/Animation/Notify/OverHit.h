

#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "OverHit.generated.h"

UCLASS()
class OOO_API UOverHit : public UAnimNotify
{
	GENERATED_BODY()
public:


	//class AUnit*		OwnerUnit;
	//class AUnitAI*	OwnerController;

	//class ABaseUnit* AgressorUnit;
	//class ABaseUnit* TargetUnit;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
