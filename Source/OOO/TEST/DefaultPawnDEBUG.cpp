

#include "DefaultPawnDEBUG.h"


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

#include "../Base/Inventory/InventoryComponent.h"

#include "../Base/Controller/Task/Base/Task.h"


#include "../Base/Item/WorldItem.h"

//---------------------------------------------

#include "Kismet/GameplayStatics.h"   // ** GetAllActorsOfClass()

#include "DrawDebugHelpers.h"












void AAAADefaultPawnDEBUG::SelectUnit_1()
{
	SelectUnit_Performance(SelectUnitName_1);
}
void AAAADefaultPawnDEBUG::SelectUnit_2()
{
	SelectUnit_Performance(SelectUnitName_2);
}
void AAAADefaultPawnDEBUG::SelectUnit_3()
{
	SelectUnit_Performance(SelectUnitName_3);
}
void AAAADefaultPawnDEBUG::SelectUnit_Performance(FName _SelectUnitName)
{
	TArray<AActor*> AllUnitsActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), AllUnitsActor);
	for (int32 i = 0; i < AllUnitsActor.Num(); i++)
	{
		AUnit* unit = Cast<AUnit>(AllUnitsActor[i]);
		if (unit->GameName == _SelectUnitName)
		{
			SelectTestUnit = unit;
			
			SelectTestUnit->IsUnitSelected = true;

			return;
		}
	}
}

//---------------------------------------------------------

void AAAADefaultPawnDEBUG::MoveToPoint_1__________SET()
{
	MoveToPoint_Performance(Point_1_MoveTo, Point_1_IsRotateTo, false);
}
void AAAADefaultPawnDEBUG::MoveToPoint_2__________ADD()
{
	MoveToPoint_Performance(Point_2_MoveTo, Point_1_IsRotateTo, true);
}
void AAAADefaultPawnDEBUG::MoveToPoint_3__________ADD()
{
	MoveToPoint_Performance(Point_3_MoveTo, Point_1_IsRotateTo, true);
}
void AAAADefaultPawnDEBUG::MoveToPoint_4__________ADD()
{
	MoveToPoint_Performance(Point_4_MoveTo, Point_1_IsRotateTo, true);
}
void AAAADefaultPawnDEBUG::MoveToPoint_5__________ADD()
{
	MoveToPoint_Performance(Point_5_MoveTo, Point_1_IsRotateTo, true);
}
void AAAADefaultPawnDEBUG::MoveToPoint_Performance(FName _Point_MoveTo, bool _bPoint_IsRotateTo, bool _bAddMoreOneTask)
{
	TArray<AActor*> AllWayPointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), AllWayPointActors);
	for (int32 i = 0; i < AllWayPointActors.Num(); i++)
	{
		AWayPoint* wayPoint = Cast<AWayPoint>(AllWayPointActors[i]);
		if (wayPoint->WayPointName == _Point_MoveTo)
		{
			FTaskData taskData;
			taskData.Location = wayPoint->GetActorLocation();	// ** or Unit
			if (_bPoint_IsRotateTo)
			{
				taskData.Rotation = wayPoint->GetActorRotation();
				taskData.TaskDislocation = ETaskDislocation::PointRotate;
			}
			else
			{
				taskData.TaskDislocation = ETaskDislocation::PointNoRotate;
			}

			if (SelectTestUnit)
				SelectTestUnit->SetUnitTask(_bAddMoreOneTask, ETaskType::MoveToPoint, taskData);
		}
	}
}


//---------------------------------------------------------


void AAAADefaultPawnDEBUG::RotateToPoint_1________SET()
{
	RotateToPoint_Performance(Point_1_RotateTo, false);
}

void AAAADefaultPawnDEBUG::RotateToPoint_2________ADD()
{
	RotateToPoint_Performance(Point_2_RotateTo, true);
}

void AAAADefaultPawnDEBUG::RotateToPoint_3________ADD()
{
	RotateToPoint_Performance(Point_3_RotateTo, true);
}

void AAAADefaultPawnDEBUG::RotateToPoint_4________ADD()
{
	RotateToPoint_Performance(Point_4_RotateTo, true);
}

void AAAADefaultPawnDEBUG::RotateToPoint_5________ADD()
{
	RotateToPoint_Performance(Point_5_RotateTo, true);
}

void AAAADefaultPawnDEBUG::RotateToPoint_Performance(FName _Point_RotateTo, bool _bAddMoreOneTask)
{
	TArray<AActor*> AllWayPointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), AllWayPointActors);
	for (int32 i = 0; i < AllWayPointActors.Num(); i++)
	{
		AWayPoint* wayPoint = Cast<AWayPoint>(AllWayPointActors[i]);
		if (wayPoint->WayPointName == _Point_RotateTo)
		{
			FTaskData taskData;
			taskData.Location = wayPoint->GetActorLocation();	// ** or Unit
			//-----taskData.Rotation = wayPoint->GetActorRotation();

			if (SelectTestUnit)
				SelectTestUnit->SetUnitTask(_bAddMoreOneTask, ETaskType::RotateToPointNormal, taskData);
		}
	}
}




//---------------------------------------------------------


void AAAADefaultPawnDEBUG::AddHour_To_GameTime()
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

void AAAADefaultPawnDEBUG::InitDailyBehaviorDT()
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





//---------------------------------------------------------  Inventor


void AAAADefaultPawnDEBUG::OpenMainInvertory()
{

	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SelectTestUnit && hud && gameMode)
	{
		hud->ShowInventory(SelectTestUnit->Inventory, gameMode);
	}
}




void AAAADefaultPawnDEBUG::AddItemToInventory()
{
	if (SelectTestUnit)
	{
		for (int32 i = 0; i < AddStartItems.Num(); ++i)
		{
			SelectTestUnit->TryAddItemToInventory(nullptr, AddToSlotIndex, AddStartItems[i]);
			//AWorldItem* CDO = Cast<AWorldItem>(AddStartItems[i].Get());
			//SelectTestUnit->TryAddItemToInventory(&CDO->ItemDT, AddToSlotIndex, InventorWorldItem);
			
		}

		if (InventorWorldItem)
		{
			
		}
	}
}



//---------------------------------------------------------  Ability




void AAAADefaultPawnDEBUG::AddAbility()
{
	for (int32 i = 0; i < Ability.Num(); ++i)
	{
		if (SelectTestUnit)
		{
			SelectTestUnit->AddAbility(Ability[i]);
		}
	}
}




// *************************************************************************************************
// *************************************************************************************************
// *************************************************************************************************



AAAADefaultPawnDEBUG::AAAADefaultPawnDEBUG()
{
	
}


void AAAADefaultPawnDEBUG::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ** Key Left SHIFT
	FInputActionKeyMapping LeftShift("LeftShift", EKeys::LeftShift, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(LeftShift);
	PlayerInputComponent->BindAction("LeftShift", IE_Pressed, this, &AAAADefaultPawnDEBUG::Shift_Left_Press);
	PlayerInputComponent->BindAction("LeftShift", IE_Released, this, &AAAADefaultPawnDEBUG::Shift_Left_Release);

	// ** Key SpaceBar
	FInputActionKeyMapping SpaceBar("SpaceBar", EKeys::SpaceBar, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(SpaceBar);
	PlayerInputComponent->BindAction("SpaceBar", IE_Pressed, this, &AAAADefaultPawnDEBUG::SpaceBar_Press);
	PlayerInputComponent->BindAction("SpaceBar", IE_Released, this, &AAAADefaultPawnDEBUG::SpaceBar_Release);
}

void AAAADefaultPawnDEBUG::Shift_Left_Press()
{
	// UE_LOG(LogTemp, Warning, TEXT("1111(%s)"), *GetName());
}
void AAAADefaultPawnDEBUG::Shift_Left_Release()
{
	
}

void AAAADefaultPawnDEBUG::SpaceBar_Press()
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


void AAAADefaultPawnDEBUG::SpaceBar_Release()
{

}





void AAAADefaultPawnDEBUG::BeginPlay()
{
	Super::BeginPlay();

}

void AAAADefaultPawnDEBUG::Tick(float DeltaTime)
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
		}
		/*for (int32 i = 0; i < SelectTestUnit->AI->StoreQueueTaskDT.Num(); ++i)
		{FString str;
			str = FString::Printf(TEXT("Curr Task: %s"), *(SelectTestUnit->AI->CurrTaskDT.TaskRef->GetName()));
			GEngine->AddOnScreenDebugMessage(	// ** #include "Engine/GameEngine.h"
				1,								// ** string
				DeltaTime * 3.f,				// ** Time
				FColor::Yellow, str);

		}
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