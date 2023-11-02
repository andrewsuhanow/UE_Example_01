// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../Enum/TaskType.h"

#include "../../Enum/TaskInstigator.h"

#include "Task.generated.h"

UCLASS()
class OOO_API UTask : public UObject
{
	GENERATED_BODY()


public:

	//-------NO-it's in Struct::TaskData--- int32 Priority = 0;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO")
		// ** # MoveToPoint, UseWeapon, UseAbility, ... 
		ETaskType TaskType = ETaskType::none;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO")
		bool IsBreakingTaskActivate = false;


public:

	UFUNCTION()
		virtual void StartTask(class AUnitAI* _OwnerAI) {};

	UFUNCTION()
		virtual void ContinueTask(class AUnitAI* _OvnerAI) {};

	UFUNCTION()
		virtual void TaskPerformance(class AUnitAI* _OvnerAI) {};

	UFUNCTION()
		virtual void TaskComplit(class AUnitAI* _OvnerAI);

	UFUNCTION()
		virtual void BreakTask(class AUnitAI* _OwnerAI);

};



