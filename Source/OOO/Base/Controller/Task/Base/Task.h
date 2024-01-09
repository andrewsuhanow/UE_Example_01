
//#include "Base/Controller/Task/Base/Task.h"

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../Enum/TaskType.h"

#include "../Struct/TaskData.h"

#include "Task.generated.h"

UCLASS(Blueprintable, Blueprinttype)
class OOO_API UTask : public UObject
{
	GENERATED_BODY()


public:

	//--------static void SetDataGoalLocation(FTaskData& _TaskData, FVector _GoalLocation);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO!")
		// ** # MoveToPoint, UseWeapon, UseAbility, ... 
		ETaskType TaskType = ETaskType::none;

	//++7777+++UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO")
	//++7777+++	bool IsBreakingTaskActivate = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO!")
		UTexture2D* TaskIcon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO!")
		FString TaskName = FString("none");
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO!")
		FString TaskDescription = FString("none");

public:

	UFUNCTION()
		virtual void StartTask(class AUnitAI* _OwnerAI) {};

	UFUNCTION()
		virtual void ContinueTask(class AUnitAI* _OvnerAI) {};

	UFUNCTION()
		virtual void TaskPerformance(class AUnitAI* _OvnerAI) {};

	UFUNCTION()
		virtual void OnAnimationNotify(class AUnitAI* _OwnerAI, FString _NotifyName) {};

	UFUNCTION()
		virtual void TaskComplit(class AUnitAI* _OvnerAI);

	UFUNCTION()
		virtual void BreakTask(class AUnitAI* _OwnerAI);

	// ** Set default Parameter
	UFUNCTION()
		virtual void ResetTask(class AUnitAI* _OwnerAI) {};

	UFUNCTION()
		virtual bool IdentifyTask(class AUnitAI* _ThisAI) { return false; };

};



