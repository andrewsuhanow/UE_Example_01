

#pragma once

#include "../Enum/TaskStatus.h"
#include "../Enum/TaskDislocation.h"
#include "../Enum/TaskPriority.h"
#include "../../Enum/TaskInstigator.h"

#include "TaskData.generated.h"







USTRUCT(BlueprintType) // , Blueprintable
struct FTaskData
{
	// ** GENERATED_BODY()
	GENERATED_USTRUCT_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		// ** none, newTask,		
		// ** GeneralComand, AIComand, DominantComand, 		
		// ** ChildTask
		ETaskStatus TaskStatus = ETaskStatus::none;								
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		// ** GeneralComand = 0,	AI-Comand = 1,	DominantComand = 2
		ETaskInstigator TaskInstigator = ETaskInstigator::General;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		// ** Normal,  Hi,  Great
		ETaskPriority TaskPriority = ETaskPriority::Normal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 777777777777777777777777777777777
		class UTask* TaskRef = nullptr;
		
		// ** What parameter using (Actor, point, rotate)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		ETaskDislocation TaskDislocation = ETaskDislocation::PointNoRotate;		// ** PointRotate,  UnitNoRotate,  UnitRotate,  RotatePointNoMove, RotateUnitNoMove

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 777777777777777777777777777777777
		class AUnit* TargetUnit = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		FVector Location;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		FRotator Rotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		int32 TaskStage = 0;


	FTaskData& operator=(const FTaskData& Other)
	{
		// ** this->TaskStatus	= Other.TaskStatus;
		this->TaskInstigator	= Other.TaskInstigator;
		this->TaskPriority		= Other.TaskPriority;
		this->TaskRef			= Other.TaskRef;
		this->TaskDislocation	= Other.TaskDislocation;
		this->TargetUnit		= Other.TargetUnit;
		this->Location			= Other.Location;
		this->Rotation			= Other.Rotation;
		this->TaskStage			= Other.TaskStage;

		return *this;
	}

};


