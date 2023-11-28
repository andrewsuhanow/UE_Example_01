
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "TActivateWeapon.generated.h"

UCLASS()
class OOO_API UTActivateWeapon : public UTask
{
	GENERATED_BODY()

public:

	UTActivateWeapon();


	// ** TaskData.Param1 - is Task stage
	// ** 0 - start animate
	// ** 1 - AnimNotify (Take or Push or Change weapon)


public:

	UPROPERTY()	AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	//virtual void TaskPerformance(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	//UPROPERTY()			FTimerHandle TH_Move;
	//UFUNCTION()			void MoveTick();
};



