
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "TDailyTask.generated.h"

UCLASS()
class OOO_API UTDailyTask : public UTask
{
	GENERATED_BODY()

public:

	UTDailyTask();

public:

	int32 iLastCurrentDailyBhvrData = -1;		// ** -1 no DailyTask
	int32 iCurrentDailyBhvrData = -1;

	AActor* CurrTargetActor = nullptr;
	FVector CurrTargetLocation;
	FRotator CurrTargetDirectuin;
	float CurrTargetWidth = -1;
	float CurrTargetHeight = -1;


public:
	
	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	UFUNCTION()			bool SetNextTaskData(class AUnitAI* _OwnerAI);
	UFUNCTION()			bool CheckTaskTimeWithGlobalTime(class AUnitAI* _OwnerAI);
	UFUNCTION()			bool InitNewDailyTaskData(class AUnitAI* _OwnerAI);

	//** getting something in game
	UFUNCTION()			void TaskResult(class AUnitAI* _OwnerAI);

};



