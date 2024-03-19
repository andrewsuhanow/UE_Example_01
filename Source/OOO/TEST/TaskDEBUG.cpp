

#include "TaskDEBUG.h"


#include "../Base/Base/BaseGameState.h"
#include "../Base/Base/BaseGameMode.h"

#include "../Base/Base/Enum/TurnBaseGameState.h"

#include "../Base/HUD/BaseHUD.h"

#include "../Base/Unit/Base/Unit.h"
#include "../Base/Controller/UnitAI.h"
#include "../Base/Controller/Task/TDailyTask.h"
#include "../Base/Controller/Task/Struct/DailyBhvrData.h"
#include "../Base/Controller/Task/Enum/DailyBhvrPointPos.h"
#include "../Base/WorldObject/WayPoint/WayPoint.h"
#include "../Base/Controller/Task/TWeaponAttack.h"

#include "../Base/Inventory/InventoryComponent.h"

#include "../Base/Amunition/WeaponComponent.h"
#include "../Base/Amunition/WeaponWorldItem.h"


#include "../Base/Controller/Task/Base/Task.h"
#include "../Base/Controller/Task/TMoveTo.h"
#include "../Base/Controller/Task/TUnitRotate.h"
#include "../Base/Controller/Task/TCheckPoint.h"

#include "../Base/Item/WorldItem.h"

//---------------------------------------------

#include "Kismet/GameplayStatics.h"   // ** GetAllActorsOfClass()

#include "DrawDebugHelpers.h"












void ATaskDEBUG::SelctUn_1()
{
	SelctUn_Performance(SelectUnitName_1);
}
void ATaskDEBUG::SelctUn_2()
{
	SelctUn_Performance(SelectUnitName_2);
}
void ATaskDEBUG::SelctUn_3()
{
	SelctUn_Performance(SelectUnitName_3);
}
void ATaskDEBUG::SelctUn_4()
{
	SelctUn_Performance(SelectUnitName_4);
}
void ATaskDEBUG::SelctUn_Performance(FName _SelectUnitName)
{
	GameState = Cast<ABaseGameState>(GetWorld()->GetGameState());
	GameMod = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	

	TArray<AActor*> AllUnitsActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), AllUnitsActor);
	for (int32 i = 0; i < AllUnitsActor.Num(); i++)
	{
		AUnit* unit = Cast<AUnit>(AllUnitsActor[i]);
		if (unit->GameName == _SelectUnitName)
		{
			SelectTestUnit = unit;
			GameState->SelectOneUnit(unit);

			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			return;
		}
	}
} 

//---------------------------------------------------------

void ATaskDEBUG::MoveTo_1_SET()
{
	MoveTo_Performance(Point_1_MoveTo, Point_1_IsRotateTo, false);
}
void ATaskDEBUG::MoveTo_2_ADD()
{
	MoveTo_Performance(Point_2_MoveTo, Point_1_IsRotateTo, true);
}
void ATaskDEBUG::MoveTo_3_ADD()
{
	MoveTo_Performance(Point_3_MoveTo, Point_1_IsRotateTo, true);
}
void ATaskDEBUG::MoveTo_4_ADD()
{
	MoveTo_Performance(Point_4_MoveTo, Point_1_IsRotateTo, true);
}
void ATaskDEBUG::MoveTo_5_ADD()
{
	MoveTo_Performance(Point_5_MoveTo, Point_1_IsRotateTo, true);
}
void ATaskDEBUG::MoveTo_Performance(FName _Point_MoveTo, bool _bPoint_IsRotateTo, bool _bAddMoreOneTask)
{
	TArray<AActor*> AllWayPointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllWayPointActors);
	for (int32 i = 0; i < AllWayPointActors.Num(); i++)
	{
		AWayPoint* wayPoint = Cast<AWayPoint>(AllWayPointActors[i]);
		if (wayPoint && wayPoint->WayPointName == _Point_MoveTo)
		{
			

			if (SelectTestUnit)
			{
				FTaskData taskData;
				FVector Loc = wayPoint->GetActorLocation();
				UTMoveTo::SetMoveData_MoveToPoint(taskData, SelectTestUnit, Loc);

				SelectTestUnit->SetUnitTask(_bAddMoreOneTask, ETaskType::MoveTo, taskData);
			}
			return;
		}
		AUnit* unit = Cast<AUnit>(AllWayPointActors[i]);  // ** AllUnitsActor
		if (unit && unit->GameName == _Point_MoveTo)
		{
			if (SelectTestUnit)
			{
				FTaskData taskData;
				FVector Loc = unit->GetActorLocation();
				UTMoveTo::SetMoveData_MoveToActor(taskData, SelectTestUnit, unit, 100.f, EUnitPose::Run);

				SelectTestUnit->SetUnitTask(_bAddMoreOneTask, ETaskType::MoveTo, taskData);
			}

		}
	}
}


//---------------------------------------------------------


void ATaskDEBUG::RotateToPoint_1________SET()
{
	RotateToPoint_Performance(Point_1_RotateTo, false);
}

void ATaskDEBUG::RotateToPoint_2________ADD()
{
	RotateToPoint_Performance(Point_2_RotateTo, true);
}

void ATaskDEBUG::RotateToPoint_3________ADD()
{
	RotateToPoint_Performance(Point_3_RotateTo, true);
}

void ATaskDEBUG::RotateToPoint_4________ADD()
{
	RotateToPoint_Performance(Point_4_RotateTo, true);
}

void ATaskDEBUG::RotateToPoint_5________ADD()
{
	RotateToPoint_Performance(Point_5_RotateTo, true);
}

void ATaskDEBUG::RotateAngle________SET()
{
	if (!SelectTestUnit)
		return;

	FTaskData taskData;
	//UTUnitRotate::SetRotateData_ToPoint(taskData, SelectTestUnit, wayPoint->GetActorLocation(), RotateSpeed);
	UTUnitRotate::SetRotateData_OnAngle(taskData, SelectTestUnit, RotateAngle, RotateSide, RotateSpeed);

	SelectTestUnit->SetUnitTask(false, ETaskType::Rotate, taskData);
}


void ATaskDEBUG::RotateToPoint_Performance(FName _Point_RotateTo, bool _bAddMoreOneTask)
{
	
	if (!SelectTestUnit)
		return;

	//RotateAngle = 0.f;
	//RotateSide = 1;
	//RotateSpeed = EUnitPose::Run;

	if (RotateAngle != 0.f)
	{
		/*
		FTaskData taskData;
			UTUnitRotate::SetRotateData_ToPoint(taskData, SelectTestUnit, FVector _GoalPoint, EUnitPose _Pose)
		*/
	}
	else
	{
		TArray<AActor*> AllWayPointActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), AllWayPointActors);
		for (int32 i = 0; i < AllWayPointActors.Num(); i++)
		{
			AWayPoint* wayPoint = Cast<AWayPoint>(AllWayPointActors[i]);
			if (wayPoint->WayPointName == _Point_RotateTo)
			{
				DefaultRotate = SelectTestUnit->GetActorRotation();

				FTaskData taskData;
				UTUnitRotate::SetRotateData_ToPoint(taskData, SelectTestUnit, wayPoint->GetActorLocation(), RotateSpeed);

				SelectTestUnit->SetUnitTask(_bAddMoreOneTask, ETaskType::Rotate, taskData);
			}
		}
	}
}

void ATaskDEBUG::SetDefaultRotate()
{
	if (SelectTestUnit)
	{
		DefaultRotate.Yaw = FMath::RandRange(0, 360);
		SelectTestUnit->SetActorRotation(DefaultRotate, ETeleportType::TeleportPhysics);
	}
}

//---------------------------------------------------------

void ATaskDEBUG::SetTargetRotationToAttacker()
{
	if (SelectTestUnit)
	{
		TArray<AActor*> allUnits;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), allUnits);
		for (int32 i = 0; i < allUnits.Num(); i++)
		{
			AUnit* unit = Cast<AUnit>(allUnits[i]);
			if (unit->GameName == UnitForAttackName)
			{
				FRotator AttackerRotator = SelectTestUnit->GetActorRotation();
				AttackerRotator.Yaw += 180.f;
				FRotator NewRotation = FRotator(
					AttackerRotator.Pitch, 
					AttackerRotator.Yaw + TargetRotateDependTarget_Degres, 
					AttackerRotator.Roll);

				FQuat QuatRotation = FQuat(NewRotation);
				//+++AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
				unit->SetActorRotation(NewRotation);
			}
		}
	}
}


void ATaskDEBUG::SetSelectAttackIndex()
{
	if (SelectTestUnit)
	{
		AWeaponWorldItem*  WpnItm = SelectTestUnit->WeaponComponent->GetCurrWeaponItem();
		if (WpnItm)
			WpnItm->SelectedAttacIndex = SelectAttackIndex;
	}
}

void ATaskDEBUG::SetPermanentAttackIndex()
{
	if (SelectTestUnit)
	{
		AWeaponWorldItem* WpnItm = SelectTestUnit->WeaponComponent->GetCurrWeaponItem();
		if (WpnItm)
			WpnItm->PermanentAttacIndex = PermanentAttackIndex;
	}
}

void ATaskDEBUG::Attack______SET()
{
	Attack_Performance(UnitForAttackName, false);
}

void ATaskDEBUG::Attack______ADD()
{
	Attack_Performance(UnitForAttackName, true);
}


void ATaskDEBUG::Attack_Performance(FName _UnitForAttackName, bool _bAddMoreOneTask)
{

	TArray<AActor*> allUnits;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), allUnits);
	for (int32 i = 0; i < allUnits.Num(); i++)
	{
		AUnit* unit = Cast<AUnit>(allUnits[i]);
		if (unit->GameName == _UnitForAttackName)
		{
			FTaskData taskData;				
			UTWeaponAttack::SetAttackData_AttackUnit(taskData, unit);    //------------taskData.TargetUnit = unit;

			if (SelectTestUnit)
			{
				AWeaponWorldItem* weaponItem = SelectTestUnit->GetCurrWeaponItem();
				UWeaponDT* weaponDT_CDO = weaponItem->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();
				if (weaponDT_CDO)
				{
					SelectTestUnit->SetUnitTask(_bAddMoreOneTask, ETaskType::WeaponAttack, taskData);
				}
			}
		}
	}
}

//---------------------------------------------------------

void ATaskDEBUG::Parrir()
{
	if (SelectTestUnit)
	{
		FTaskData taskData;
		SelectTestUnit->SetUnitTask(false, ETaskType::Parrir, taskData);
	}
}
void ATaskDEBUG::Block()
{
	if (SelectTestUnit)
	{
		FTaskData taskData;
		SelectTestUnit->SetUnitTask(false, ETaskType::Block, taskData);
	}
}
void ATaskDEBUG::Dodge()
{
	if (SelectTestUnit)
	{
		FTaskData taskData;
		SelectTestUnit->SetUnitTask(false, ETaskType::Dodge, taskData);
	}
}
void ATaskDEBUG::GetHit()
{
	if (SelectTestUnit)
	{
		FTaskData taskData;
		SelectTestUnit->SetUnitTask(false, ETaskType::GetHit, taskData);
	}
}

//---------------------------------------------------------

void ATaskDEBUG::Tactical_Move()
{
	
	if (SelectTestUnit)
	{
		//ETacticalMoveType Side_To_Move = ETacticalMoveType::move_closer;
		//FName TargetUnitName = FName("Un1");


		FTaskData taskData;
		bool isDataCorrect = false;

		TArray<AActor*> AllActor;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActor);
		AUnit* unit = nullptr;
		AWayPoint* wayPoint = nullptr;
		AUnit* unitFocusing = nullptr;
		for (int32 i = 0; i < AllActor.Num(); i++)
		{

			AUnit* unitTMP = Cast<AUnit>(AllActor[i]);
			if (unitTMP && unitTMP->GameName == TargetName)
			{
				unit = unitTMP;
			}
			if (unitTMP && unitTMP->GameName == FocusActorName)
			{
				unitFocusing = unitTMP;
			}
			AWayPoint* wayPointTMP = Cast<AWayPoint>(AllActor[i]);
			if (wayPointTMP && wayPointTMP->WayPointName == TargetName)
			{
				wayPoint = wayPointTMP;
			}
		}

		switch (TacticMoveType)
		{
		case ETacticalMoveType::SimpleMoveToPoint:
			UTMoveTo::SetMoveData_MoveToPoint(taskData, SelectTestUnit, wayPoint->GetActorLocation(), StopDistance, UnitPose);
			break;
		case ETacticalMoveType::SimpleMoveToActor:
			UTMoveTo::SetMoveData_MoveToActor(taskData, SelectTestUnit, unit, StopDistance, UnitPose);
			break;
		case ETacticalMoveType::MoveToPointWithUnitFocus:
			UTMoveTo::SetMoveData_MoveToPointWithUnitFocus(taskData, SelectTestUnit, wayPoint->GetActorLocation(), unitFocusing, StopDistance, UnitPose);
			break;
		case ETacticalMoveType::MoveToActorWithUnitFocus:
			UTMoveTo::SetMoveData_MoveToActorWithUnitFocus(taskData, SelectTestUnit, unit, unitFocusing, StopDistance, UnitPose);
			break;
		case ETacticalMoveType::MoveToPointWithRotateFix:
			UTMoveTo::SetMoveData_MoveToPointWithRotateFix(taskData, SelectTestUnit, wayPoint->GetActorLocation(), StopDistance, UnitPose);
			break;
		case ETacticalMoveType::MoveToActorWithRotateFix:
			UTMoveTo::SetMoveData_MoveToActorWithRotateFix(taskData, SelectTestUnit, unit, StopDistance, UnitPose);
			break;
		}
/*			if (unit && unit->GameName == TargetName)
			{
				if (TacticMoveType == ETacticalMoveType::SimpleMoveToPoint || TacticMoveType == ETacticalMoveType::SimpleMoveToActor)
				{
					-------UTMoveTo::SetMoveData_MoveToActor(taskData, SelectTestUnit, unit, StopDistance, UnitPose);
				}
				if (TacticMoveType == ETacticalMoveType::MoveToPointWithUnitFocus || TacticMoveType == ETacticalMoveType::MoveToActorWithUnitFocus)
				{
					----UTMoveTo::SetMoveData_MoveToActorWithUnitFocus(taskData, SelectTestUnit, unit, StopDistance, UnitPose);
				}
				if (TacticMoveType == ETacticalMoveType::MoveToPointWithRotateFix || TacticMoveType == ETacticalMoveType::MoveToActorWithRotateFix)
				{
					UTMoveTo::SetMoveData_MoveToActorWithRotateFix(taskData, SelectTestUnit, unit, StopDistance, UnitPose);
				}
				isDataCorrect = true;
				break;
			}
		}
			AWayPoint* wayPoint = Cast<AWayPoint>(AllActor[i]);
			if (wayPoint && wayPoint->WayPointName == TargetName)
			{
				if (TacticMoveType == ETacticalMoveType::SimpleMoveToActor || TacticMoveType == ETacticalMoveType::SimpleMoveToPoint)
				{
					------------UTMoveTo::SetMoveData_MoveToPoint(taskData, SelectTestUnit, wayPoint->GetActorLocation(), StopDistance, UnitPose);
					isDataCorrect = true;
				}
				if (TacticMoveType == ETacticalMoveType::MoveToActorWithUnitFocus || TacticMoveType == ETacticalMoveType::MoveToPointWithUnitFocus)
				{
					FocusActorName;
					TArray<AActor*> AllActorFocusing;
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActorFocusing);
					for (int32 j = 0; j < AllActorFocusing.Num(); j++)
					{
						AUnit* unitFocusing = Cast<AUnit>(AllActorFocusing[j]);
						if (unitFocusing && unitFocusing->GameName == TargetName)
						{
							UTMoveTo::SetMoveData_MoveToPointWithUnitFocus(taskData, SelectTestUnit, unitFocusing, wayPoint->GetActorLocation(), StopDistance, UnitPose);
							isDataCorrect = true;
						}
					}
				}
				if (TacticMoveType == ETacticalMoveType::MoveToActorWithRotateFix || TacticMoveType == ETacticalMoveType::MoveToPointWithRotateFix)
				{
					------------------UTMoveTo::SetMoveData_MoveToPointWithRotateFix(taskData, SelectTestUnit, wayPoint->GetActorLocation(), StopDistance, UnitPose);
					isDataCorrect = true;
				}
				break;
			}
		}
*/

		SelectTestUnit->SetUnitTask(false, ETaskType::MoveTo, taskData);
	}

}


//---------------------------------------------------------




void ATaskDEBUG::TheckThePoint_1() 
{
	TheckThePoint_Performance(Point_1_ToCheck);
}
void ATaskDEBUG::TheckThePoint_2() 
{
	TheckThePoint_Performance(Point_2_ToCheck);
}
void ATaskDEBUG::TheckThePoint_3()
{
	TheckThePoint_Performance(Point_3_ToCheck);
}
void ATaskDEBUG::TheckThePoint_Performance(FName _Point_ToCheck)
{
	if (SelectTestUnit)
	{
		TArray<AActor*> AllWayPointActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), AllWayPointActors);
		for (int32 i = 0; i < AllWayPointActors.Num(); i++)
		{
			AWayPoint* wayPoint = Cast<AWayPoint>(AllWayPointActors[i]);
			if (wayPoint->WayPointName == _Point_ToCheck)
			{
				DefaultRotate = SelectTestUnit->GetActorRotation();

				FTaskData taskData;
				if(CheckBySpeed == EUnitPose::RelaxMove)
					UTCheckPoint::SetTaskData_RelaxCheckingPoint(taskData, SelectTestUnit, wayPoint->GetActorLocation());
				else if(CheckBySpeed == EUnitPose::Run)
					UTCheckPoint::SetTaskData_FastCheckingPoint(taskData, SelectTestUnit, wayPoint->GetActorLocation());
				else
					UTCheckPoint::SetTaskData_CautionCheckingPoint(taskData, SelectTestUnit, wayPoint->GetActorLocation());	// @@@@@@@@@  NOT Use jet

				SelectTestUnit->SetUnitTask(false, ETaskType::CheckPoint, taskData);
			}
		}
	}
}


void ATaskDEBUG::SetDefaultPosition()
{

}




//---------------------------------------------------------


void ATaskDEBUG::AddHour_To_GameTime()
{
	ABaseGameMode *gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		gameMode->AddTime(TimeCountToAdd);
		GameTimePresent = gameMode->GetGameHour();

		if (SelectTestUnit)
		{
			SelectTestUnit->AI->OnNewGameHour(GameTimePresent);
			/*int32 dailyTaskIndex;
			for (int32 i = 0; i < SelectTestUnit->AI->ActionTaskssObj.Num(); ++i)
			{
				if (SelectTestUnit->AI->ActionTaskssObj[i]->TaskType == ETaskType::DailyBehavior)
				{
					//dailyTaskIndex = i;
					break;
				}
			}*/


			//if(SelectTestUnit->AI->DailyBhvrTaskDT.Num() == 0)
			//	InitDailyBehaviorDT();


			//Cast<UTDailyTask>(SelectTestUnit->AI->ActionTaskssObj[dailyTaskIndex])->CheckCorrectingTaskData(SelectTestUnit->AI);
			//SelectTestUnit->AI->UpdateLogic();
		}

	}
}

void ATaskDEBUG::InitDailyBehaviorDT()
{
	TArray<AActor*> AllWayPointActors;
	TArray<AWayPoint*> AllWayPoint;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), AllWayPointActors);
	for (int32 i = 0; i < AllWayPointActors.Num(); i++)
	{
		AWayPoint* wayPoint = Cast<AWayPoint>(AllWayPointActors[i]);
		if (wayPoint)
		{
			if (wayPoint->WayPointName != FName("none"))
			{
				AllWayPoint.Add(wayPoint);
			}
		}
	}
	for (int32 i = 0; i < AllWayPoint.Num(); i++)
	{
		FDailyBhvrData newDlTaskDT;
		//newDlTaskDT.PointActor = AllWayPoint[i];
		newDlTaskDT.WayPointTag = AllWayPoint[i]->WayPointName;
		newDlTaskDT.StartTime = i;
		newDlTaskDT.EndTime = i+3;
		newDlTaskDT.DailyBhvrPointPos = EDailyBhvrPointPos::on_point_rotata_forward;
		newDlTaskDT.Shifting = 0;
		newDlTaskDT.DurationTypeAndTime = 3;
		SelectTestUnit->AI->DailyBhvrTaskDT.Add(newDlTaskDT);
	}


}








// *************************************************************************************************
// *************************************************************************************************
// *************************************************************************************************



ATaskDEBUG::ATaskDEBUG()
{
	
}


void ATaskDEBUG::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ** Key Left SHIFT
	FInputActionKeyMapping LeftShift("LeftShift", EKeys::LeftShift, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(LeftShift);
	PlayerInputComponent->BindAction("LeftShift", IE_Pressed, this, &ATaskDEBUG::Shift_Left_Press);
	PlayerInputComponent->BindAction("LeftShift", IE_Released, this, &ATaskDEBUG::Shift_Left_Release);

	// ** Key SpaceBar
	FInputActionKeyMapping SpaceBar("SpaceBar", EKeys::SpaceBar, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(SpaceBar);
	PlayerInputComponent->BindAction("SpaceBar", IE_Pressed, this, &ATaskDEBUG::SpaceBar_Press);
	PlayerInputComponent->BindAction("SpaceBar", IE_Released, this, &ATaskDEBUG::SpaceBar_Release);
}

void ATaskDEBUG::Shift_Left_Press()
{
	// UE_LOG(LogTemp, Warning, TEXT("1111(%s)"), *GetName());
}
void ATaskDEBUG::Shift_Left_Release()
{
	
}

void ATaskDEBUG::SpaceBar_Press()
{
	ABaseGameState* GmState = Cast<ABaseGameState>(GetWorld()->GetGameState());
	if (GmState)
	{
		if (GmState->TurnBaseGameState == ETurnBaseGameState::RealTime)
		{
			GmState->SetNewTurnBaseGameState(ETurnBaseGameState::Pause);
			UE_LOG(LogTemp, Warning, TEXT("Stop Game"));
		}
		else
		{
			GmState->SetNewTurnBaseGameState(ETurnBaseGameState::RealTime);
			UE_LOG(LogTemp, Warning, TEXT("Resume Game"));
		}
	}
}


void ATaskDEBUG::SpaceBar_Release()
{

}





void ATaskDEBUG::BeginPlay()
{
	Super::BeginPlay();

}

void ATaskDEBUG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ** Update UnitAi TasksDT
	if (SelectTestUnit)
	{
		/*if (StoreQueueTaskDT.Num() != SelectTestUnit->AI->StoreQueueTaskDT.Num())
		{
			StoreQueueTaskDT.Reset();
			for (int32 i = 0; i < SelectTestUnit->AI->StoreQueueTaskDT.Num(); ++i)
			{
				StoreQueueTaskDT.Add(SelectTestUnit->AI->StoreQueueTaskDT[i]);
			}
		}*/

		if (SelectTestUnit->AI->CurrTaskRef)
		{
			FString str;
			str = FString::Printf(TEXT("Curr Task: %s"), *(SelectTestUnit->AI->CurrTaskRef->GetName()));
			GEngine->AddOnScreenDebugMessage(	// ** #include "Engine/GameEngine.h"
				1,								// ** string
				DeltaTime * 3.f,				// ** Time
				FColor::Yellow, str);



			if (Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef) &&
				Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->WeaponLenght != 0.f)
			{
				TArray<FHitResult> traceBoundHit;
				TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesQuery;
				ObjectTypesQuery.Add(EObjectTypeQuery(ECC_Pawn));
				ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldStatic));
				ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldDynamic));
				//++FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);
				TArray<AActor*> ActorsToIgnore;
				ActorsToIgnore.Add(SelectTestUnit);

				UKismetSystemLibrary::SphereTraceMultiForObjects
				(
					GetWorld(),
					Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->StartPoint,	// ** Start,
					Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->EndPoint,	// ** End,
					Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->WeaponLenght,	// **Radius,
					ObjectTypesQuery,
					false,			// ** bool bTraceComplex,
					ActorsToIgnore,
					EDrawDebugTrace::Persistent,	// ** None, ForOneFrame, ForDuration, ++Persistent++
					traceBoundHit,						// ** TArray< FHitResult >& OutHits,
					true,							// ** bIgnoreSelf
					FColor::Green,					// ** TraceColor
					FColor::Green,					// ** TraceHitColor
					4.5f							// ** float DrawTime
				);

				Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->StartPoint = FVector(0.f, 0.f, 0.f);	// ** Start,
				Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->EndPoint = FVector(0.f, 0.f, 0.f);	// ** End,
				Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->WeaponLenght = 0.f;					// **Radius,
				/*DrawDebugSphere(
					GetWorld(),
					FVector(Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->StartPoint.ImpactPoint.X,
						Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->StartPoint.ImpactPoint.Y,
						Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->StartPoint.ImpactPoint.Z), // ** center
					Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->WeaponLenght, // radius
					10, // Segments
					FColor(FColor::Red),
					false, // bPersistLine
					4.5f, //GetWorld()->GetDeltaSeconds() * 3,
					5, // DepthPriority
					2); // Siknes
				*/
			}


			// ** TEST DRAW-WEAPON-Attack---Line---or---HitPoint
			if (Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef) &&
				Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->TaskType == ETaskType::WeaponAttack)
			{
				if (isDrawWeaponTRACE_DebugLine)
				{
					//FTransform zewroTransform = FTransform(FVector(0.f, 0.f, 0.f));
					if (Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->StartPoint != FVector(0.f, 0.f, 0.f) &&
						Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->EndPoint != FVector(0.f, 0.f, 0.f))
					{
						DrawDebugLine(
							GetWorld(),
							Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->StartPoint,
							Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->EndPoint,	//TraceEnd,
							FColor::Blue,
							false,			// is visible always
							4.5f,			// visible time
							0,
							2.0f); // siknes

						Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->StartPoint = FVector(0.f, 0.f, 0.f);	// ** Start,
						Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->EndPoint = FVector(0.f, 0.f, 0.f);	// ** End,
					}
				}

				if (Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->TraceHit.bBlockingHit == true)
				{
					if (isPrintingHitingActor_DebugLOG)
					{
						UE_LOG(LogTemp, Error, TEXT("num:    '%i' "), Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->CurrHittingActors.Num());
					}

					if (isDrawWeaponHIT_DebugSphere)
					{
						DrawDebugSphere(
							GetWorld(),
							FVector(Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->TraceHit.ImpactPoint.X,
								Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->TraceHit.ImpactPoint.Y,
								Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->TraceHit.ImpactPoint.Z), // ** center
							5.f, // radius
							5, // Segments
							FColor(FColor::Red),
							false, // bPersistLine
							4.5f, //GetWorld()->GetDeltaSeconds() * 3,
							5, // DepthPriority
							2); // Siknes
					}
					if (isPrintingHitingActor_DebugLOG)
					{
						for (int32 i = 0; i < Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->CurrHittingActors.Num(); ++i)
							UE_LOG(LogTemp, Error, TEXT("AUn:    '%s' "), *(Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->CurrHittingActors[i]->GetName()));
					}

					
					/*
									//------ (----------------------------)
									//------UE_LOG(LogTemp, Warning, TEXT("NO:    '%s' "), *(TraceHit.GetActor()->GetName()));
									//------if(CurrHittingActors.Num() >=2)
									//------	return;

									// -------if(TraceHit.GetActor())
									//--------UE_LOG(LogTemp, Warning, TEXT("OKK:    '%s' "), *(TraceHit.GetActor()->GetName()));
					*/
				}
			}
		}


		if (IsDrawMoveGoalRay)
		{
			++sh;
			if (sh == 5.f)
			{
				StoreQueueTaskDTCopy.Reset();
				CurrTaskDTBufferCopy.Reset();
				sh = 0.f;
				for (int32 i = 0; i < SelectTestUnit->AI->FractionQueueTaskDT.Num(); ++i)
				{

					StoreQueueTaskDTCopy.Add(SelectTestUnit->AI->FractionQueueTaskDT[i]);
				}
				for (int32 i = 0; i < SelectTestUnit->AI->TasksBuffer.Num(); ++i)
				{
					CurrTaskDTBufferCopy.Add(SelectTestUnit->AI->TasksBuffer[i]);
				}
			}

			// ** StoreQueueTaskDT   Task
			for (int32 i = 0; i < StoreQueueTaskDTCopy.Num(); ++i)
			{
				// ** All Queue movew task
				if (StoreQueueTaskDTCopy[i].TaskRef->TaskType == ETaskType::MoveTo)
				{
					FVector Pos;
					if (StoreQueueTaskDTCopy[i].Actor.Num() > 0 && StoreQueueTaskDTCopy[i].Actor[0])
						Pos = StoreQueueTaskDTCopy[i].Actor[0]->GetActorLocation();
					else if(StoreQueueTaskDTCopy[i].Vector3dParam.Num() > 0)
						Pos = StoreQueueTaskDTCopy[i].Vector3dParam[0];
					DrawDebugLine(
						GetWorld(),
						SelectTestUnit->GetActorLocation(),	// ** Start
						Pos,								// ** Trace_End,
						FColor::Blue,
						false, // is visible always
						DeltaTime * 2.5f, /// visible time
						5, /// DepthPriority
						4.0f); /// Siknes
				}
			}

			// ** DailyBehavior   /   TasksBuffer

			if (CurrTaskDTBufferCopy.Num() > 0 &&
				CurrTaskDTBufferCopy[0].TaskRef->TaskType == ETaskType::DailyBehavior)
			{
				FVector Pos;
				if (Cast<UTDailyTask>(CurrTaskDTBufferCopy[0].TaskRef)->CurrTargetActor != nullptr)
				//if (CurrTaskDTBufferCopy[0].Actor.Num() > 0 )
					Pos = Cast<UTDailyTask>(CurrTaskDTBufferCopy[0].TaskRef)->CurrTargetActor->GetActorLocation();
				else
					Pos = Cast<UTDailyTask>(CurrTaskDTBufferCopy[0].TaskRef)->CurrTargetLocation;

				DrawDebugLine(
					GetWorld(),
					SelectTestUnit->GetActorLocation(), /// ** Start
					Pos,								/// ** Trace_End,
					FColor::Yellow,
					false, /// is visible always
					DeltaTime * 2.5, /// visible time
					5, /// DepthPriority
					4.0f); /// Siknes
			}
		}

		if (DrawDebugRotate && SelectTestUnit->AI->CurrTaskRef && Cast<UTUnitRotate>(SelectTestUnit->AI->CurrTaskRef))
		{
			//if (Cast<UTUnitRotate>(SelectTestUnit->AI->CurrTaskRef)->Angle > 0.f)
			{
				DrawDebugLine(
					GetWorld(),
					SelectTestUnit->GetActorLocation(), /// ** Start
					SelectTestUnit->GetActorLocation() + SelectTestUnit->GetActorForwardVector() * 200.f,		/// ** Trace_End,
					FColor::Blue,
					false, /// is visible always
					DeltaTime * 2.5, /// visible time
					5, /// DepthPriority
					4.0f); /// Siknes

				//float angl = Cast<UTUnitRotate>(SelectTestUnit->AI->CurrTaskRef)->Angle;
				DrawDebugLine(
					GetWorld(),
					SelectTestUnit->GetActorLocation(), /// ** Start
					Cast<UTUnitRotate>(SelectTestUnit->AI->CurrTaskRef)->GoalPoint,	/// ** Trace_End,
					//------SelectTestUnit->GetActorLocation() + FRotator(0.f, angl, 0.f).RotateVector(SelectTestUnit->GetActorForwardVector() * 200.f),	/// ** Trace_End,
					FColor::Yellow,
					false, /// is visible always
					DeltaTime * 2.5, /// visible time
					5, /// DepthPriority
					4.0f); /// Siknes
			}
		}
		/*	FString str;
			str = FString::Printf(TEXT("Curr Task: %s"), *(SelectTestUnit->AI->CurrTaskDT.TaskRef->GetName()));
			GEngine->AddOnScreenDebugMessage(	// ** #include "Engine/GameEngine.h"
				1,								// ** string
				DeltaTime * 3.f,				// ** Time
				FColor::Yellow, str);
		*/

	}
}

/*
DrawDebugLine(
GetWorld(),
GetPawn()->GetActorLocation(),	// ** Start
GetCurrentTargetActor()->GetActorLocation(),// ** Trace_End,
FColor::Red,
false,						// is visible always
3.0f,						// visible time
5, 							// DepthPriority
5.0f);						// Siknes




DrawDebugBox(
																								GetWorld(),
																								_Location,  			// ** center
																								FVector(5.f), 				// ** size
																								FColor(FColor::Blue), 		// ** Extent
																								false,
																								3.0f,						// ** LifeTime
																								5, 							// ** DepthPriority
																								3); 						// ** Thickness




DrawDebugSphere(
																									GetWorld(),
																									mCoverPoints[Cover_BestPointIndex].Location,  				// ** center
																									15.f,						// radius
																									5,							// Segments
																									FColor(FColor::Yellow),
																									false, 						// bPersistLine
																									3.f, 						//GetWorld()->GetDeltaSeconds() * 3,
																									5,							// DepthPriority
																									3);							// Siknes







*/