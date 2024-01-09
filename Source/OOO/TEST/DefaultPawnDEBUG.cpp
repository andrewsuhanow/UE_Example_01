

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

#include "../Base/Amunition/WeaponComponent.h"

#include "../Base/Ability/Enum/AbilityType.h"

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
/*
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
*

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
*/



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






void AAAADefaultPawnDEBUG::InitTestInvertorItems()
{

	if (0 == ItemsToAddRes.Num())
	{
		TArray<UBlueprint*> wpnTMP;
		TArray<UTexture2D*> fullImageTexture;
		TArray<UTexture2D*> oneImageTexture;
		TArray<int32> sizeX;
		TArray<int32> sizeY;
		TArray<int32> Count;
		TArray<int32> CountMax;
		TArray<bool> IsStackable;

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Amunition/WeapomDT/BigWorldDT_BP.BigWorldDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_1x4.ITEM_CELL_1x4")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/BigSword/BibSword02.BibSword02")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(1);
		sizeY.Add(4);
		ItemsToAdd.Add(FName("1x4"));

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Amunition/WeapomDT/GunDT_BP.GunDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_2x4.ITEM_CELL_2x4")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Rifle/Rifle03.Rifle03")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(2);
		sizeY.Add(4);
		ItemsToAdd.Add(FName("2x4 Gun"));

		wpnTMP.Add(nullptr);
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugAbility/Blue_Potion.Blue_Potion")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugAbility/Blue_Potion.Blue_Potion")));
		Count.Add(3);
		CountMax.Add(10);
		IsStackable.Add(true);
		sizeX.Add(1);
		sizeY.Add(1);
		ItemsToAdd.Add(FName("1x1 3/10"));

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Amunition/WeapomDT/BowDT_BP.BowDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Bow/Bow01.Bow01")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Bow/Bow01.Bow01")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(4);
		sizeY.Add(2);
		ItemsToAdd.Add(FName("4x2 Bow"));

		wpnTMP.Add(nullptr);
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_4x1.ITEM_CELL_4x1")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_4x1.ITEM_CELL_4x1")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(4);
		sizeY.Add(1);
		ItemsToAdd.Add(FName("4x1"));

		wpnTMP.Add(nullptr);
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_3x3.ITEM_CELL_3x3")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_3x3.ITEM_CELL_3x3")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(3);
		sizeY.Add(3);
		ItemsToAdd.Add(FName("3x3"));

		wpnTMP.Add(nullptr);
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_2x2.ITEM_CELL_2x2")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_2x2.ITEM_CELL_2x2")));
		Count.Add(2);
		CountMax.Add(5);
		IsStackable.Add(true);
		sizeX.Add(2);
		sizeY.Add(2);
		ItemsToAdd.Add(FName("2x2 2/5"));

		wpnTMP.Add(nullptr);
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_4x4.ITEM_CELL_4x4")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_4x4.ITEM_CELL_4x4")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(4);
		sizeY.Add(4);
		ItemsToAdd.Add(FName("4x4"));

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Amunition/WeapomDT/SpearDT_BP.SpearDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pike/Spear01.Spear01")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pike/Spear01.Spear01")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(1);
		sizeY.Add(5);
		ItemsToAdd.Add(FName("1x5 Spear"));

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Amunition/WeapomDT/PistolDT_BP.PistolDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pistol/pistol01.pistol01")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pistol/pistol01.pistol01")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(1);
		sizeY.Add(2);
		ItemsToAdd.Add(FName("1x2 Pistol 1"));

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Amunition/WeapomDT/PistolDT_BP.PistolDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pistol/pistol02.pistol02")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pistol/pistol02.pistol02")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(2);
		sizeY.Add(1);
		ItemsToAdd.Add(FName("2x1 Pistol 2"));




		for (int32 i = 0; i < ItemsToAdd.Num(); ++i)
		{
			ItemsToAddRes.Add(MakeShared<FItemDT>());
			if(wpnTMP[i])
				ItemsToAddRes.Last().Get()->WeaponDT = (UClass*)wpnTMP[i]->GeneratedClass;
			ItemsToAddRes.Last().Get()->ItemImage = fullImageTexture[i];
			ItemsToAddRes.Last().Get()->ItemOneCellImage = oneImageTexture[i];

			ItemsToAddRes.Last().Get()->CountMax = CountMax[i];
			ItemsToAddRes.Last().Get()->Count = Count[i];

			ItemsToAddRes.Last().Get()->IsStackable = IsStackable[i];

			ItemsToAddRes.Last().Get()->InventorySizeX = sizeX[i];
			ItemsToAddRes.Last().Get()->InventorySizeY = sizeY[i];
		}
	}
}


void AAAADefaultPawnDEBUG::OpenMainInvertory()
{

	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SelectTestUnit && hud)
	{
		hud->ShowInventory(SelectTestUnit->Inventory);

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}


void AAAADefaultPawnDEBUG::AddItemToInventory()
{
	if (SelectTestUnit && AddItemIndex >= 0 && AddItemIndex < ItemsToAdd.Num())
	{
		SelectTestUnit->TryAddItemToMainInventory(ItemsToAddRes[AddItemIndex].Get(), AddToSlotIndex, nullptr, IsForseAdd);
		OpenMainInvertory();
	}
}


//---------------------------------------------------------  Global-Inventor


void AAAADefaultPawnDEBUG::OpenGlobalInvertory()
{
	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SelectTestUnit && hud)
	{
		hud->ShowGlobalInventory(SelectTestUnit->Inventory);

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}

void AAAADefaultPawnDEBUG::AddItemToGlobalInventory()
{

	if (SelectTestUnit && AddItemIndex >= 0 && AddItemIndex < ItemsToAdd.Num())
	{
		SelectTestUnit->AddItemToGlobalInventory(ItemsToAddRes[AddItemIndex].Get(), AddToSlotIndex);
		OpenGlobalInvertory();
	}
}

//---------------------------------------------------------  Equip-Panel

void AAAADefaultPawnDEBUG::OpenEquipPanel()
{
	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SelectTestUnit && hud)
	{
		hud->ShowEquipPanel(SelectTestUnit);

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}
void AAAADefaultPawnDEBUG::AddItemToEquipPanel()
{
	
	if (SelectTestUnit && AddItemIndex >= 0 && AddItemIndex < ItemsToAdd.Num())
	{
		//---SelectTestUnit->EquipWeaponByItemDT(ItemsToAddRes[AddItemIndex].Get());
		SelectTestUnit->EquipAmunitionByItemDT(ItemsToAddRes[AddItemIndex].Get());
		//---OpenEquipPanel();
	}
	
}




//---------------------------------------------------------  Ability


void AAAADefaultPawnDEBUG::ShowPerkPanel()
{
	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SelectTestUnit && hud)
	{
		hud->ShowPerkPanel(SelectTestUnit, gameMode);

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}

void AAAADefaultPawnDEBUG::AddAbility()
{
	//////////for (int32 i = 0; i < Ability.Num(); ++i)
	//////////{
	//////////	if (SelectTestUnit)
	//////////	{
	//////////		SelectTestUnit->AddAbility(Ability[i]);
	//////////	}
	//////////}

	if (SelectTestUnit)
	{
		SelectTestUnit->AddAbility(EAbilityType::drink);
		SelectTestUnit->AddAbility(EAbilityType::harvest);
		SelectTestUnit->AddAbility(EAbilityType::health);
		SelectTestUnit->AddAbility(EAbilityType::usem_middle);
		SelectTestUnit->AddAbility(EAbilityType::pick_up);
		SelectTestUnit->AddAbility(EAbilityType::throw_sing);
	}
}



//---------------------------------------------------------  Fast-Panel



void AAAADefaultPawnDEBUG::ShowFastPanel()
{
	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SelectTestUnit && hud)
	{
		hud->ShowFastPanel(SelectTestUnit);

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}

void AAAADefaultPawnDEBUG::AddItemToFastPanel()
{
	if (SelectTestUnit && AddItemIndex >= 0 && AddItemIndex < ItemsToAdd.Num())
	{
		SelectTestUnit->SetItemToFastPanel(ItemsToAddRes[AddItemIndex].Get(), AddToSlotIndex);
		ShowFastPanel();
	}
}


void AAAADefaultPawnDEBUG::AddAbilityToFastPanel()
{
	if (AbilityToAdd != EAbilityType::none)
	{
		SelectTestUnit->SetAbilityToFastPanel(AbilityToAdd, AddToSlotIndex);
	}

	ShowFastPanel();

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