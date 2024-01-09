
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "TWait.generated.h"

UCLASS()
class OOO_API UTWait : public UTask
{
	GENERATED_BODY()

public:

	UTWait();

public:

	float TimeLeft = 0.f;

	// ** FTaskData::Param1[0]  -  Waiting time

public:

	UPROPERTY()			AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	//virtual void TaskPerformance(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	virtual bool IdentifyTask(class AUnitAI* _ThisAI) override;


	UPROPERTY()			FTimerHandle TH_Wait;
	UFUNCTION()			void WaitTick();


	// ** ---------------------  Static func  ------------------------

public:

	UFUNCTION()
		static void SetTaskData_WaitParam(FTaskData& _TaskData, class AUnit* _SelfUnit, float _Time = 0.f);

};



