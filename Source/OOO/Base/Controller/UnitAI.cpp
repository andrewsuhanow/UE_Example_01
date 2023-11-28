
// ** #include "../Controller/UnitAI.h"
#include "UnitAI.h"

#include "../Unit/Base/Unit.h"

#include "Task/Base/Task.h"
#include "Task/Struct/TaskData.h"
#include "Task/Base/DailyBhvrQueue.h"

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

	//-----MainTaskDT.TaskStatus = ETaskStatus::MainTask;
	//-----PartTaskDT.TaskStatus = ETaskStatus::PartTask;
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
	// ....
	UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>>      AUnitAI::OnAnimNotify():         %s"), *GetName());

	UpdateLogic();
}




// **  ************************************************************************
// **  ************************       Core_Action      ************************
// **  ************************************************************************


void AUnitAI::MoveToPoint()
{

	/*
	// ** MOVE HOME
		//---------------------------------------------FVector Point = taskGoalLocation;
		Set_StopDistance_ForMoveAction(0.f);
		Set_UsingStrafe_ForMoveAction(false);
		MoveToActor(_Actor, _StopDistBefore, _bStopOnOverlap, _bUsePathfinding, _IsStrafe);

	// ** Move
		AI_MoveToPoint(_Location, _StopDistBefore + 30.f, false, true, false, false);
	*/

//	AI_MoveToPoint(GetCurrentTargetPoint(CurrTargetLocationEXIST), mStopDistance_ForMoveAction, bStopOnOverlap, bUsePathfinding, mIsStrafe_ForMoveAction, bDebugProjectileToNavigation);
//++++++	MoveToLocation(_Location, _StopDistBefore, _bStopOnOverlap, _bUsePathfinding, _bDebugProjectileToNavigation, _IsStrafe);
}

void AUnitAI::MoveToUnit()
{

	/*

	// ** MOVE for Attack (from far)
		if (BehaviorComp->mCurrDistToTarget > BehaviorComp->mCurrWeapon_Max_Dist)
			{
				float stopDistance = BehaviorComp->mCurrWeapon_Max_Dist - GetCapsuleRadius_Self() * 3.f;

				//ActionSTATE_TMP = EActionState::Move;
				//ActionParallelSTATE_TMP = EActionState::none;

				//---------bool IsOtherActionApplay = Action_MoveCloser_ToPoint(_Controller, targetPoint, _SelfCapsuleRadius, stopDistance);
				AI_MoveToActor(GetCurrentTargetActor(), stopDistance, true, true, false);
			}
	// ** ATTACK (contack <can from far but neer close>)
			if (IsAIContactWeaponType())
			{

				AI_MoveToActor(GetCurrentTargetActor(), BehaviorComp->mCurrWeapon_Min_Dist, true, true, false);
			}
	
	*/
//+++++++	MoveToActor(_Actor, _StopDistBefore, _bStopOnOverlap, _bUsePathfinding, _IsStrafe);

}

void AUnitAI::Rotate()
{
	/*
	// ** Vector from Rotator
	FVector dir = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);

	// ** Rotator from vector
	FRotator Rot = LocalDir = PosDir.Rotation();
	*/


	/*
	SetCurrTargetLocation(EndLocation); // ** FVector
	FVector selfPosition = _Controller->GetPawn()->GetActorLocation();
	FVector _Direction = (EndLocation - selfPosition).GetSafeNormal();
	NormalRotateToPoint(_Direction); // ** FVector
		float DeltaRotate = GetAngleRotateToPoint(PawnOwner, _Direction);
		if (FMath::Abs(DeltaRotate) > 0.01f)
		{
			SetCurrTargetLocation(PawnOwner->GetActorLocation() + _Direction * 100);
			SetRotateSpeed(3);
		}
	*/
}


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

// **  ************************************************************************
// **  **********************       Misc_Operation      **********************
// **  ************************************************************************


void AUnitAI::SetTask(bool _bAddMoreOne, ETaskType _TaskType, FTaskData _TaskData,
					ETaskInstigator _TaskInstigator, ETaskPriority _TaskPriority)
{
	// ** Complete "_TaskData"

	_TaskData.TaskInstigator = _TaskInstigator;
	_TaskData.TaskPriority = _TaskPriority;

	for (int32 i = 0; i < ActionTaskssObj.Num(); ++i)
	{
		if (ActionTaskssObj[i]->TaskType == _TaskType)
		{
			_TaskData.TaskRef = ActionTaskssObj[i];
			break;
		}
	}

	// ** Confirm new Task to UnitAI

	if (_TaskInstigator == ETaskInstigator::Dominant)
	{
		StoreDominantTaskDT = _TaskData;
		StoreDominantTaskDT.TaskStatus = ETaskStatus::NewTask;
		UpdateLogic();
		return;
	}
	else
	if (_TaskInstigator == ETaskInstigator::AI)
	{
		StoreAITaskDT = _TaskData;
		StoreAITaskDT.TaskStatus = ETaskStatus::NewTask;
		UpdateLogic();
		return;
	}
	else
	if (_TaskInstigator == ETaskInstigator::General)
	{
		if (_bAddMoreOne)
		{
			StoreQueueTaskDT.Add(_TaskData);
			//--77--if (!CurrTaskRef)
				UpdateLogic();
		}
		else
		{
			StoreQueueTaskDT.Reset();
			StoreQueueTaskDT.Add(_TaskData);
			StoreGeneralTaskDT = _TaskData;
			StoreGeneralTaskDT.TaskStatus = ETaskStatus::NewTask;
			if (CurrTaskRef)
				CurrTaskRef->BreakTask(this);
			else
				UpdateLogic();

		}
	}
	else
	if (_TaskInstigator == ETaskInstigator::OtherTask)
	{
		CurrTaskDTBuffer.Add(_TaskData);
		CurrTaskRef = _TaskData.TaskRef;
		CurrTaskRef->StartTask(this);
	}

	
}


void AUnitAI::UpdateLogic()
{
	// ** if Unit "Fall-Down" now or other Hi-PriorityLogic

	if (CurrTaskDTBuffer.Num() > 0)
		if(CurrTaskDTBuffer.Last().TaskPriority == ETaskPriority::Great)
			return;


	// ** *******  Set New Tasks  *******  
		// --@@@@@@@@@@@@@@@@@@@@@@@@-- Lambda
		//if (CurrTaskRef)
		//	CurrTaskRef->TotalBreakTask(this);
		//else
		//{
		//	CurrTaskDT = MainTaskDT = StoreDominantTaskDT;
		//	CurrTaskRef = MainTaskDT.TaskRef;
		//	CurrTaskRef->StartTask();
		//}

	// ** *******  Check New Tasks  *******

	// ** Has Dominant task
	if (StoreDominantTaskDT.TaskStatus == ETaskStatus::NewTask)
	{
		if (CurrTaskRef)
			CurrTaskRef->BreakTask(this);
		else
		{
			CurrTaskDTBuffer.Reset();

			FTaskData TaskDT_TMP;
			TaskDT_TMP = StoreDominantTaskDT;
			StoreDominantTaskDT.TaskStatus = ETaskStatus::none;
			TaskDT_TMP.TaskStatus = ETaskStatus::DominantComand;
			CurrTaskDTBuffer.Add(TaskDT_TMP);
			CurrTaskRef = CurrTaskDTBuffer.Last().TaskRef;
			CurrTaskRef->StartTask(this);
		}
		return;
	}
	// ** Has AI task
	else 
	if (StoreAITaskDT.TaskStatus == ETaskStatus::NewTask)
	{
		if (CurrTaskRef)
			CurrTaskRef->BreakTask(this);
		else
		{
			CurrTaskDTBuffer.Reset();

			FTaskData TaskDT_TMP;
			TaskDT_TMP = StoreAITaskDT;
			StoreAITaskDT.TaskStatus = ETaskStatus::none;
			TaskDT_TMP.TaskStatus = ETaskStatus::AIComand;
			CurrTaskDTBuffer.Add(TaskDT_TMP);
			CurrTaskRef = CurrTaskDTBuffer.Last().TaskRef;
			CurrTaskRef->StartTask(this);
		}
		return;
	}
	// ** Has General task
	else
	if (StoreGeneralTaskDT.TaskStatus == ETaskStatus::NewTask)
	{
		if (CurrTaskRef)
			CurrTaskRef->BreakTask(this);
		else
		{
			CurrTaskDTBuffer.Reset();

			FTaskData TaskDT_TMP;
			TaskDT_TMP = StoreGeneralTaskDT;
			StoreGeneralTaskDT.TaskStatus = ETaskStatus::none;
			TaskDT_TMP.TaskStatus = ETaskStatus::GeneralComand;
			CurrTaskDTBuffer.Add(TaskDT_TMP);
			CurrTaskRef = CurrTaskDTBuffer.Last().TaskRef;
			CurrTaskRef->StartTask(this);
		}
		return;
	}	
	// ** Has Task in GeneralQuery
	else
	if (!CurrTaskRef && StoreQueueTaskDT.Num() > 0)
	{
		StoreGeneralTaskDT = StoreQueueTaskDT[0];
		StoreGeneralTaskDT.TaskStatus = ETaskStatus::NewTask;
		UpdateLogic();
		return;
	}
	else
	if (CurrTaskRef)
	{
		CurrTaskRef->ContinueTask(this);
		return;
	}
	else
	{
		if (DailyBhvrTaskIndex == -1 || DailyBhvrTaskDT.Num() == 0)
			return;

		if (CurrTaskRef)
			CurrTaskRef->BreakTask(this);
		else
		{
			//-----CurrTaskDTBuffer;							 // ** TEST_TEST
			CurrTaskRef = ActionTaskssObj[DailyBhvrTaskIndex];
			CurrTaskRef->ContinueTask(this);
		}
	}
}


// **  ************************************************************************
// **  **********************       Self_Operation      **********************
// **  ************************************************************************

FVector AUnitAI::GetCurrSelfLocation()
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



void AUnitAI::SetUnitRotateSpeed(uint8 _RotSpeedIndex)
{
	UnitOwner->SetRotateSpeed(_RotSpeedIndex);
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

void AUnitAI::GetTasksQueDataFromAI(UTexture2D*& _CurrTaskImage,
	TArray<UTexture2D*>& _TasksImage,
	TArray<int32>& _TasksIndex)
{
	if (!CurrTaskRef)
		return;

	_CurrTaskImage = CurrTaskDTBuffer[0].TaskRef->TaskIcon;

	for (int32 i = 0; i < StoreQueueTaskDT.Num(); ++i)
	{
		_TasksIndex.Add(i);
		_TasksImage.Add(StoreQueueTaskDT[i].TaskRef->TaskIcon);
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
				UnitOwner->GetCurrentWeaponType(), _AnimationKey);
}

// **  ************************************************************************
// **  **********************       Target_Operation      **********************
// **  ************************************************************************

FVector AUnitAI::GetCurrTargetLocation()
{
	if (CurrTaskRef)
		if (CurrTaskDTBuffer.Last().TargetUnit)
		{
			return CurrTaskDTBuffer.Last().TargetUnit->GetActorLocation();
		}
		else
		{
			return CurrTaskDTBuffer.Last().Location;
		}
	return FVector::ZeroVector;
}



// ****************************************************
// *****************   TEST_DEBUG  *****************
// ****************************************************
/* (---------------------)
void AUnitAI::AddTaskMovePointTEST(ETaskType _TaskType, FVector _Location, bool _IsRotateByPoint, FRotator _Rotation)
{

}
*/