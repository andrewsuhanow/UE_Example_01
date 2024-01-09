
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "TNewTask.generated.h"

UCLASS()
class OOO_API UTNewTask : public UTask
{
	GENERATED_BODY()

public:

	UTNewTask();



public:

	UPROPERTY()			AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	//virtual void TaskPerformance(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	virtual bool IdentifyTask(class AUnitAI* _ThisAI) override;





	// ** ---------------------  Static func  ------------------------
/*
public:

	UFUNCTION()
		static void SetTaskData_WaitParam(FTaskData& _TaskData, class AUnit* _SelfUnit, float _Time = 0.f);
	*/
};



