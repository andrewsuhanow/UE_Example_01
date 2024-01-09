
// ** #include "Base/Controller/UnitAI.h"
#include "UnitAI.h"

#include "../Unit/Base/Unit.h"

#include "Task/Base/Task.h"
#include "Task/Struct/TaskData.h"
#include "Task/Base/DailyBhvrQueue.h"

#include "../Amunition/WeaponWorldItem.h"

//-------------------------

#include "../Base/BaseGameMode.h"
#include "../Base/BaseGameState.h"
#include "../HUD/BaseHUD.h"

//-------------------------

#include "Kismet/GameplayStatics.h"		// ** GetAuthGameMode()



/*
#include "Task/FinishMove.h"
#include "Task/AimingTarget.h"

#include "Task/ChangePose.h"
#include "Task/ChangeWeapon.h"
#include "Task/RotateToPointFast.h"
#include "Task/RotateToPointNormal.h"
#include "Task/RotateToPointSlow.h"
#include "Task/RotateAngleFast.h"
#include "Task/RotateAngleNormal.h"
#include "Task/RotateAngleSlow.h"
#include "Task/Wait.h"
#include "Task/MoveToPoint.h"--------------
#include "Task/FastMoveToPoint.h
#include "Task/MoveToUnit.h"
#include "Task/FastMoveToUnit.h"
#include "Task/BattleSideMove.h"
#include "Task/BattleRetreatMove.h"
#include "Task/LookPoint.h"
#include "Task/CheckPoint.h"
#include "Task/UseWeapon.h"
#include "Task/UseAbility.h"
#include "Task/UseEffect.h"				// ** Transform, Teleport, CreateSomeOne, StoredSomeOne, Fly
#include "Task/DailyBehavior.h"

#include "Task/Hit1_NoAnim.h"
#include "Task/Hit2_Normal.h"
#include "Task/Hit3_Big.h"

#include "Task/Block.h"
#include "Task/Parrir.h"
#include "Task/Dodge.h"
*/

AUnitAI::AUnitAI()
{
	PrimaryActorTick.bCanEverTick = true;

	//-----MainTaskDT.TaskCauser = ETaskCauser::MainTask;
	//-----PartTaskDT.TaskCauser = ETaskCauser::PartTask;
}


void AUnitAI::BeginPlay()
{
	Super::BeginPlay();

	// ** Generate "ActionTasksObj" (SET in UE)
	for (int32 i = 0; i < AvailableTaskType.Num(); ++i)
	{
		UTask* TaskTmp = NewObject<UTask>(this, AvailableTaskType[i], FName(*("TaskName_" + AvailableTaskType[i]->GetName() + "_" + GetName()))); //TEXT("BehaviorComponent"));;
		if (TaskTmp)
		{
			ActionTaskssObj.Add(TaskTmp);
		}
	}
	for (int32 i = 0; i < ActionTaskssObj.Num(); ++i)
	{
		if (ActionTaskssObj[i]->TaskType == ETaskType::DailyBehavior)
		{
			DailyBhvrTaskIndex = i;
			break;
		}
	}
}


void AUnitAI::Init(bool isStart)
{

	UnitOwner = Cast<AUnit>(GetPawn());
	if (!UnitOwner)
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ERROR:   '%s'::AUnitAI::Init():      'UnitOwner' not Get"), *GetName());


	GameState = Cast<ABaseGameState>(GetWorld()->GetGameState());
	if (!GameState)
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ERROR:   '%s'::AUnitAI::Init():      'GameState' not Get"), *GetName());

	GameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ERROR:   '%s'::AUnitAI::Init():      'GameMode' not Get"), *GetName());


	HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (!HUD)
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ERROR:   '%s'::AUnitAI::Init():      'HUD' not Get"), *GetName());



	if (isStart)
	{
		// ** DailyBhvr default-Queue Init()
		if (UnitOwner->DailyBhvrQueueClass)
		{
			UDailyBhvrQueue* DailyBhvrQueueCDO = UnitOwner->DailyBhvrQueueClass->GetDefaultObject<UDailyBhvrQueue>();
			int32 QueueNum = DailyBhvrQueueCDO->DailyBhvrTaskDT.Num();
			if (QueueNum > 0)
			{
				for (int32 i = 0; i < QueueNum; ++i)
				{
					DailyBhvrTaskDT.Add(DailyBhvrQueueCDO->DailyBhvrTaskDT[i]);
				}
			}
		}
	}


	UpdateLogic();

	return;
}









// **  ************************************************************************
// **  ************************       EVENT      ************************
// **  ************************************************************************


// (----------------------------------)
/*
void AUnitAI::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (CurrTaskRef)
		CurrTaskRef->ContinueTask(this);
	else
		UpdateLogic();
}
*/


void AUnitAI::OnFinishAnimation(UAnimMontage* FinishedAnimMontage, bool _bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>>      AUnitAI::OnFinishAnimation():         %s"), *GetName());

	UpdateLogic();
}

void AUnitAI::OnChangeTurnBaseGameState(ETurnBaseGameState _TurnBaseGameState)
{
	// ....
	UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>>      AUnitAI::OnChangeTurnBaseGameState():         %s"), *GetName());
}

void AUnitAI::OnAnimNotify(FString _NotifyName)
{
	if (CurrTaskRef)
		CurrTaskRef->OnAnimationNotify(this, _NotifyName);
}




// **  ************************************************************************
// **  ************************       Core_Action      ************************
// **  ************************************************************************








// **  ************************************************************************
// **  **********************       Global_Operation      **********************
// **  ************************************************************************


int32 AUnitAI::GetGameHour()
{
	return GameMode->GetGameHour();
}

void AUnitAI::OnNewGameHour(int32 iHour)
{
	UpdateLogic();
}

EPossesingGameState AUnitAI::GetPossesingGameState()
{
	return GameState->GetPossesingGameState();
}



// **  ************************************************************************
// **  **********************       Misc_Operation      **********************
// **  ************************************************************************


void AUnitAI::SetTask(bool _bAddMoreOne, ETaskType _TaskType, FTaskData _TaskData,
//--------					ETaskInstigator _TaskInstigator, ETaskPriority _TaskPriority)
							ETaskCauser _TaskCauser, ETaskPriority _TaskPriority)
{
	// ** Complete "_TaskData"

	_TaskData.TaskPriority = _TaskPriority;

	for (int32 i = 0; i < ActionTaskssObj.Num(); ++i)
	{
		if (ActionTaskssObj[i]->TaskType == _TaskType)
		{
			_TaskData.TaskRef = ActionTaskssObj[i];
			break;
		}
	}

	if (!_TaskData.TaskRef)
	{
		return;
	}


	// ** Confirm new Task to UnitAI

	if (_TaskCauser == ETaskCauser::CriticalTask)
	{
		CriticalTaskDT = _TaskData;
		CriticalTaskDT.TaskCauser = ETaskCauser::CriticalTask_New;
		UpdateLogic();
		//---------return;
	}
	else
	if (_TaskCauser == ETaskCauser::NpcTask)
	{
		NpcTaskDT = _TaskData;
		NpcTaskDT.TaskCauser = ETaskCauser::NpcTask_New;
		UpdateLogic();
		//----------return;
	}
	else
	if (_TaskCauser == ETaskCauser::FractionTask)
	{
		if (_bAddMoreOne)
		{
			FractionQueueTaskDT.Add(_TaskData);
			if (!CurrTaskRef)
				UpdateLogic();
		}
		else
		{
			if (CurrTaskRef)
				CurrTaskRef->BreakTask(this);
			FractionQueueTaskDT.Reset();
			FractionQueueTaskDT.Add(_TaskData);
			FractionTaskDT = _TaskData;
			FractionTaskDT.TaskCauser = ETaskCauser::FractionTask_New;
			UpdateLogic();

		}
	}
	else
	if (_TaskCauser == ETaskCauser::ChildTask)
	//if (_TaskCauser == ETaskInstigator::OtherTask)
	{
		TasksBuffer.Add(_TaskData);
		TasksBuffer.Last().TaskCauser = ETaskCauser::ChildTask;
		CurrTaskRef = _TaskData.TaskRef;
		CurrTaskRef->StartTask(this);
	}

	// ** HUD-Task-Queue update
	UnitOwner->UpdateTaskQueuePanel_HUD();
	// ** HUD-Attack-Wpn panel update
	UnitOwner->UpdateAttacksWpnPanel_HUD();
}


void AUnitAI::UpdateLogic()
{
	// ** if Unit "Fall-Down" now or other Hi-PriorityLogic

	if (TasksBuffer.Num() > 0)
		if(TasksBuffer.Last().TaskPriority == ETaskPriority::Great)
			return;


	/// ** *******  Set New Tasks  *******  
		/// --@@@@@@@@@@@@@@@@@@@@@@@@-- Lambda
		///if (CurrTaskRef)
		///	CurrTaskRef->TotalBreakTask(this);
		///else
		///{
		///	CurrTaskDT = MainTaskDT = CriticalTaskDT;
		///	CurrTaskRef = MainTaskDT.TaskRef;
		///	CurrTaskRef->StartTask();
		///}


	// ** *******  Check New Tasks  *******

	// ** Has Dominant task
	if (CriticalTaskDT.TaskCauser == ETaskCauser::CriticalTask_New)
	{
		if (CurrTaskRef)
			CurrTaskRef->BreakTask(this);
		else
		{
			TasksBuffer.Reset();

			FTaskData TaskDT_TMP;
			TaskDT_TMP = CriticalTaskDT;
			CriticalTaskDT.TaskCauser = ETaskCauser::none;
			TaskDT_TMP.TaskCauser = ETaskCauser::CriticalTask;
			TasksBuffer.Add(TaskDT_TMP);
			CurrTaskRef = TasksBuffer.Last().TaskRef;
			CurrTaskRef->StartTask(this);
		}
		//-----------return;
	}
	// ** Has AI task
	else 
	if (NpcTaskDT.TaskCauser == ETaskCauser::NpcTask_New)
	{
		if (CurrTaskRef)
			CurrTaskRef->BreakTask(this);
		else
		{
			TasksBuffer.Reset();

			FTaskData TaskDT_TMP;
			TaskDT_TMP = NpcTaskDT;
			NpcTaskDT.TaskCauser = ETaskCauser::none;
			TaskDT_TMP.TaskCauser = ETaskCauser::NpcTask;
			TasksBuffer.Add(TaskDT_TMP);
			CurrTaskRef = TasksBuffer.Last().TaskRef;
			CurrTaskRef->StartTask(this);
		}
		//-----------return;
	}
	// ** Has General task
	else
	if (FractionTaskDT.TaskCauser == ETaskCauser::FractionTask_New)
	{
		if (CurrTaskRef)
			CurrTaskRef->BreakTask(this);
		else
		{
			TasksBuffer.Reset();

			FTaskData TaskDT_TMP;
			TaskDT_TMP = FractionTaskDT;
			FractionTaskDT.TaskCauser = ETaskCauser::none;
			TaskDT_TMP.TaskCauser = ETaskCauser::FractionTask;
			TasksBuffer.Add(TaskDT_TMP);
			CurrTaskRef = TasksBuffer.Last().TaskRef; 
			CurrTaskRef->StartTask(this);
		}
		//-----------return;
	}	
	// ** Has Task in GeneralQuery
	else
	if (!CurrTaskRef && FractionQueueTaskDT.Num() > 0)
	{
		FractionTaskDT = FractionQueueTaskDT[0];
		FractionTaskDT.TaskCauser = ETaskCauser::FractionTask_New;
		UpdateLogic();
		//-----------return;
	}
	else
	if (CurrTaskRef)
	{
		CurrTaskRef->ContinueTask(this);
		//-----------return;
	}
	else if (DailyBhvrTaskIndex != -1 && DailyBhvrTaskDT.Num() != 0)
	{
		if (CurrTaskRef)
			CurrTaskRef->BreakTask(this);
		else
		{
			CurrTaskRef = ActionTaskssObj[DailyBhvrTaskIndex];
			CurrTaskRef->ContinueTask(this);
		}
	}
	else
	{
		//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			Go  HOME Point
		//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			Set HOME Rotate
		//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}

	// ** HUD-Task-Queue update
	UnitOwner->UpdateTaskQueuePanel_HUD();
}


// **  ************************************************************************
// **  **********************       Self_Operation      **********************
// **  ************************************************************************

FVector AUnitAI::GetCurrSelfLocation() const
{
	return UnitOwner->GetActorLocation();
}

FRotator AUnitAI::GetCurrSelfRotation()
{
	return UnitOwner->GetActorRotation();
}

void AUnitAI::SetSelfRotation(FRotator rot)
{
	UnitOwner->SetActorRotation(rot, ETeleportType::TeleportPhysics);
}

FVector AUnitAI::GetUnitRightVector()
{
	return UnitOwner->GetActorRightVector();
}

FVector AUnitAI::GetUnitForwardVector()
{
	return UnitOwner->GetActorForwardVector();
}



void AUnitAI::SetUnitRotateSpeedByPose(EUnitPose _UnitPose)
{
	UnitOwner->GetRotateSpeedFromPose(_UnitPose);
}

void AUnitAI::SetUnitMoveSpeed(float _Speed)
{
	UnitOwner->SetMoveSpeed(_Speed);
}

void AUnitAI::UnitStopMove()
{
	UnitOwner->StopMove();
}


float AUnitAI::GetUnitStopDistance()
{
	return UnitOwner->StopDistance;
}


bool AUnitAI::IsUnitInGroup()
{
	return UnitOwner->IsUnitInGroup();
}

bool AUnitAI::IsUnitSelected()
{
	return UnitOwner->GetIsUnitSelected();
}


FName AUnitAI::GetUnitGameName()
{
	return UnitOwner->GameName;
}


void AUnitAI::PlayAnimate(UAnimMontage* _AnimMontage, bool _isPlayTOP, float _fromTime)
{
	return UnitOwner->PlayAnimate(_AnimMontage, _isPlayTOP, _fromTime);
}

void AUnitAI::StopAnimate()
{
	UnitOwner->StopAnimate();
}



void AUnitAI::GetTasksQueDataFromAI(UTexture2D*& _CurrTaskImage,
	TArray<UTexture2D*>& _TasksImage,
	TArray<int32>& _TasksIndex)
{
	if (!CurrTaskRef)
		return;

	_CurrTaskImage = TasksBuffer[0].TaskRef->TaskIcon;

	for (int32 i = 0; i < FractionQueueTaskDT.Num(); ++i)
	{
		_TasksIndex.Add(i);

		// @@@@@@@@@@@@@@@@@@@@@@@@@@
		// @@@@@@@@@@@@@@@@@@@@@@@@@@
		// @@@@@@@@@@@@@@@@@@@@@@@@@@   if(FractionQueueTaskDT[i].Name == Attack)   =>>   Get Icon from Weapon->Attack->Texture
		_TasksImage.Add(FractionQueueTaskDT[i].TaskRef->TaskIcon);
		// @@@@@@@@@@@@@@@@@@@@@@@@@@
		// @@@@@@@@@@@@@@@@@@@@@@@@@@
	}
}



int32 AUnitAI::IsWeaponActive()
{
	return UnitOwner->IsWeaponActive();
}

bool AUnitAI::ActivateWeapon()
{
	return UnitOwner->ActivateWeapon();
}
bool AUnitAI::UnactivateWeapon()
{
	return UnitOwner->UnactivateWeapon();
}


UAnimMontage* AUnitAI::GetGameAnimation(EAnimationKey _AnimationKey)
{
	return GameMode->GetGameAnimation(UnitOwner->UnitGameType,
				UnitOwner->GetWeaponTypeBySlotIndex(UnitOwner->GetSelectedWeaponSlotIndex()), _AnimationKey);
}


AWeaponWorldItem* AUnitAI::GetCurrWeaponItem()
{
	return UnitOwner->GetCurrWeaponItem();
}


FTransform AUnitAI::GetUnitSocketParam(FName _SocketName)
{
	return UnitOwner->GetUnitSocketParam(_SocketName);

}


// **  ************************************************************************
// **  **********************       Target_Operation      **********************
// **  ************************************************************************

FVector AUnitAI::GetCurrTargetLocation()
{
	// (++++++++++++++++)
	/*
	if (CurrTaskRef)
		if (TasksBuffer.Last().TargetUnit)
		{
			return TasksBuffer.Last().TargetUnit->GetActorLocation();
		}
		else
		{
			return TasksBuffer.Last().Location;
		}
	*/
	return FVector::ZeroVector;
}

float AUnitAI::GetDistanceToTarget(AActor* _TargetActor, bool _WithMoveDistCorrector) const
{
	if (!_TargetActor)
		return 0.f;

	float moveDistCorrector = 0.f;
	if (_WithMoveDistCorrector)
		moveDistCorrector = UnitOwner->StopDistance;

	float dist =  FVector::Distance(GetCurrSelfLocation(), _TargetActor->GetActorLocation())
		- moveDistCorrector;

	return (dist > 0.f) ? dist : 0.f;
}

// ****************************************************
// *****************   TEST_DEBUG  *****************
// ****************************************************
/* (---------------------)
void AUnitAI::AddTaskMovePointTEST(ETaskType _TaskType, FVector _Location, bool _IsRotateByPoint, FRotator _Rotation)
{

}
*/