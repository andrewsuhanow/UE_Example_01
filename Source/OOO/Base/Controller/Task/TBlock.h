
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "TBlock.generated.h"

UCLASS()
class OOO_API UTBlock : public UTask
{
	GENERATED_BODY()

public:

	UTBlock();

public:

	float TimeLength = 0.f;

	bool IsUsingAnimate = true;

	UAnimMontage* Animate = nullptr;


public:

	UPROPERTY()			AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	//---virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void TaskPerformance(class AUnitAI* _OwnerAI) override;

	//virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	//virtual void BreakTask(class AUnitAI* _ThisAI) override;

	UPROPERTY()			FTimerHandle TH_Block;
	//UFUNCTION()			void BlockUp();
	//UFUNCTION()			void BlockDown();
	UFUNCTION()			void BlockHolding();
};



