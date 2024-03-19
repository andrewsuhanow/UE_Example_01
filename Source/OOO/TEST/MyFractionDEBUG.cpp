

// #include "TEST/MyFractionDEBUG.h"
#include "MyFractionDEBUG.h"

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
#include "../Base/Controller/Task/TMoveTo.h"

#include "../Base/Inventory/InventoryComponent.h"
#include "../Base/Amunition/WeaponWorldItem.h"

#include "../Base/Amunition/WeaponComponent.h"

//#include "../Base/Ability/Enum/AbilityLogic.h"

#include "../Base/Controller/Task/Base/Task.h"


#include "../Base/Item/WorldItem.h"

//---------------------------------------------

#include "Kismet/GameplayStatics.h"   // ** GetAllActorsOfClass()
#include "Kismet/KismetMathLibrary.h"

#include "DrawDebugHelpers.h"





void AMyFractionDEBUG::SelectUnit_1()
{
	SelectUnit_Performance(SelectUnitName_1);
}
void AMyFractionDEBUG::SelectUnit_2()
{
	SelectUnit_Performance(SelectUnitName_2);
}
void AMyFractionDEBUG::SelectUnit_3()
{
	SelectUnit_Performance(SelectUnitName_3);
}
void AMyFractionDEBUG::SelectUnit_Performance(FName _SelectUnitName)
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



void AMyFractionDEBUG::InitTestInvertorItems()
{

	if (0 == ItemsToAddRes.Num())
	{
		TArray<UBlueprint*> wpnTMP;
		TArray<UTexture2D*> fullImageTexture;
		TArray<UTexture2D*> oneImageTexture;
		TArray<UObject*> itemMesh;
		TArray<int32> sizeX;
		TArray<int32> sizeY;
		TArray<int32> Count;
		TArray<int32> CountMax;
		TArray<bool> IsStackable;

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Weapon/WeapomDT/BigSwordDT_BP.BigSwordDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_1x4.ITEM_CELL_1x4")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/BigSword/BibSword02.BibSword02")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/Weapon/Sword2H/BigSword02/BigSword02.BigSword02")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(1);
		sizeY.Add(4);
		ItemsToAdd.Add(FName("1x4"));

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Weapon/WeapomDT/GunDT_BP.GunDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_2x4.ITEM_CELL_2x4")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Rifle/Rifle03.Rifle03")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/Weapon/RapidGun01/SK_RapidGun01.SK_RapidGun01")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(2);
		sizeY.Add(4);
		ItemsToAdd.Add(FName("2x4 Gun"));

		wpnTMP.Add(nullptr);
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugAbility/Blue_Potion.Blue_Potion")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugAbility/Blue_Potion.Blue_Potion")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/Potion1.Potion1")));
		Count.Add(3);
		CountMax.Add(10);
		IsStackable.Add(true);
		sizeX.Add(1);
		sizeY.Add(1);
		ItemsToAdd.Add(FName("1x1 3/10"));

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Weapon/WeapomDT/BowDT_BP.BowDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Bow/Bow01.Bow01")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Bow/Bow01.Bow01")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/Weapon/RapidGun01/SK_RapidGun01.SK_RapidGun01")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(4);
		sizeY.Add(2);
		ItemsToAdd.Add(FName("4x2 Bow"));

		wpnTMP.Add(nullptr);
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_4x1.ITEM_CELL_4x1")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_4x1.ITEM_CELL_4x1")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/Weapon/Spear/SM_Spear.SM_Spear")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(4);
		sizeY.Add(1);
		ItemsToAdd.Add(FName("4x1"));

		wpnTMP.Add(nullptr);
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_3x3.ITEM_CELL_3x3")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_3x3.ITEM_CELL_3x3")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/BigGun.BigGun")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(3);
		sizeY.Add(3);
		ItemsToAdd.Add(FName("3x3"));

		wpnTMP.Add(nullptr);
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_2x2.ITEM_CELL_2x2")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_2x2.ITEM_CELL_2x2")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/Weapon/Dagger/SM_Dagger_1.SM_Dagger_1")));
		Count.Add(2);
		CountMax.Add(5);
		IsStackable.Add(true);
		sizeX.Add(2);
		sizeY.Add(2);
		ItemsToAdd.Add(FName("2x2 2/5"));

		wpnTMP.Add(nullptr);
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_4x4.ITEM_CELL_4x4")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugInvertor/ITEM_CELL_4x4.ITEM_CELL_4x4")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/BigGun.BigGun")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(4);
		sizeY.Add(4);
		ItemsToAdd.Add(FName("4x4"));

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Weapon/WeapomDT/SpearDT_BP.SpearDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pike/Spear01.Spear01")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pike/Spear01.Spear01")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/Weapon/Spear/SM_Spear.SM_Spear")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(1);
		sizeY.Add(5);
		ItemsToAdd.Add(FName("1x5 Spear"));

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Weapon/WeapomDT/PistolDT_BP.PistolDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pistol/pistol01.pistol01")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pistol/pistol01.pistol01")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/Weapon/Dagger/SM_Dagger_1.SM_Dagger_1")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(1);
		sizeY.Add(2);
		ItemsToAdd.Add(FName("1x2 Pistol 1"));

		wpnTMP.Add(LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Weapon/WeapomDT/PistolDT_BP.PistolDT_BP")));
		fullImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pistol/pistol02.pistol02")));
		oneImageTexture.Add(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/EquipSlot/Pistol/pistol02.pistol02")));
		itemMesh.Add(LoadObject<UObject>(nullptr, TEXT("/Game/Test/Geometry/Weapon/Dagger/SM_Dagger_1.SM_Dagger_1")));
		Count.Add(1);
		CountMax.Add(1);
		IsStackable.Add(false);
		sizeX.Add(2);
		sizeY.Add(1);
		ItemsToAdd.Add(FName("2x1 Pistol 2"));




		for (int32 i = 0; i < ItemsToAdd.Num(); ++i)
		{
			//ItemsToAddRes.Add(MakeShared<FItemDT>());
			ItemsToAddRes.Add(MakeShareable(new FItemDT()));
			if (wpnTMP[i])
				ItemsToAddRes.Last().Get()->WeaponDT = (UClass*)wpnTMP[i]->GeneratedClass;
			ItemsToAddRes.Last().Get()->ItemImage = fullImageTexture[i];
			ItemsToAddRes.Last().Get()->ItemOneCellImage = oneImageTexture[i];

			ItemsToAddRes.Last().Get()->MeshPrimitive = itemMesh[i];

			ItemsToAddRes.Last().Get()->CountMax = CountMax[i];
			ItemsToAddRes.Last().Get()->Count = Count[i];

			ItemsToAddRes.Last().Get()->IsStackable = IsStackable[i];

			ItemsToAddRes.Last().Get()->InventorySizeX = sizeX[i];
			ItemsToAddRes.Last().Get()->InventorySizeY = sizeY[i];
		}
	}
}




//---------------------------------------------------------  Equip-Panel

void AMyFractionDEBUG::OpenEquipPanel()
{
	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SelectTestUnit && hud)
	{
		hud->ShowEquipPanel(SelectTestUnit);

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}
void AMyFractionDEBUG::AddItemToEquipPanel()
{

	if (SelectTestUnit && AddItemIndex >= 0 && AddItemIndex < ItemsToAdd.Num())
	{
		//-----SelectTestUnit->EquipWeaponByItemDT(ItemsToAddRes[AddItemIndex].Get());
		SelectTestUnit->EquipAmunitionByItemDT(ItemsToAddRes[AddItemIndex].Get());
		//---OpenEquipPanel();
	}

}




void AMyFractionDEBUG::SetEquipPanelSet()
{
	if (SelectTestUnit)
	{
		InitTestInvertorItems();

		//////SelectTestUnit->EquipWeaponByItemDT(ItemsToAddRes[0].Get());
		//////SelectTestUnit->EquipWeaponByItemDT(ItemsToAddRes[1].Get());
		//////SelectTestUnit->EquipWeaponByItemDT(ItemsToAddRes[9].Get());

		SelectTestUnit->EquipAmunitionByItemDT(ItemsToAddRes[0].Get());
		SelectTestUnit->EquipAmunitionByItemDT(ItemsToAddRes[1].Get());
		SelectTestUnit->EquipAmunitionByItemDT(ItemsToAddRes[9].Get());





		OpenEquipPanel();
	}
}







AMyFractionDEBUG::AMyFractionDEBUG()
{

}


void AMyFractionDEBUG::BeginPlay()
{
	Super::BeginPlay();

}

void AMyFractionDEBUG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SelectTestUnit)
	{
		// ** Draw line to Tactical Move
		if (IsDebugLine_TacticalMove)
		{
			if (SelectTestUnit->AI->CurrTaskRef)
			{

				if (Cast<UTMoveTo>(SelectTestUnit->AI->CurrTaskRef))
				{
					if (Cast<UTMoveTo>(SelectTestUnit->AI->CurrTaskRef)->TaskType == ETaskType::MoveTo &&
						Cast<UTMoveTo>(SelectTestUnit->AI->CurrTaskRef)->GoalLocation != FVector(0.f, 0.f, 0.f))
					{
						EndPointTM == Cast<UTMoveTo>(SelectTestUnit->AI->CurrTaskRef)->GoalLocation;

						DrawDebugLine(
							GetWorld(),
							SelectTestUnit->GetActorLocation(),	// ** Start
							Cast<UTMoveTo>(SelectTestUnit->AI->CurrTaskRef)->GoalLocation,	// ** Trace_End,
							FColor::Blue,
							false, // is visible always
							2.5f, /// visible time
							5, /// DepthPriority
							4.0f); /// Siknes
					}
				}

				if (Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef))
				{


					/*if (Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->TaskType == ETaskType::WeaponAttack &&
						Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->EndPoint != FVector(0.f, 0.f, 0.f))
					{
						EndPointTM == Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->EndPoint;

						DrawDebugLine(
							GetWorld(),
							SelectTestUnit->GetActorLocation(),	// ** Start
							Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->EndPoint,	// ** Trace_End,
							FColor::Blue,
							false, // is visible always
							2.5f, /// visible time
							5, /// DepthPriority
							4.0f); /// Siknes
					}*/

					if (Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->TaskType == ETaskType::WeaponAttack && 
						Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->CurrTargetActor)
					{
						EndPointTM == Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->EndPoint;

						DrawDebugLine(
							GetWorld(),
							SelectTestUnit->GetActorLocation(),	// ** Start
							Cast<UTWeaponAttack>(SelectTestUnit->AI->CurrTaskRef)->CurrTargetActor->GetActorLocation(),	// ** end
							FColor::Red,
							false, // is visible always
							2.5f, /// visible time
							5, /// DepthPriority
							4.0f); /// Siknes
					}
					
				}
			}
		}




	}
}


//-------------------------------------------------------------------------


void AMyFractionDEBUG::PrepareMarcer(FVector _EndPoint, AActor* _Target)
{
	DrawDebugLine(
		GetWorld(),
		SelectTestUnit->GetActorLocation(),	// ** Start
		_EndPoint,	// ** Trace_End,
		FColor::Blue,
		false, // is visible always
		3.0f, /// visible time
		10, /// DepthPriority
		10.0f); /// Siknes

	if(_Target)
	DrawDebugSphere(
		GetWorld(),
		_Target->GetActorLocation(), // ** center
		20.f, // radius
		10, // Segments
		FColor(FColor::Red),
		false, // bPersistLine
		3.0f, //GetWorld()->GetDeltaSeconds() * 3,
		10, // DepthPriority
		10); // Siknes
}



void AMyFractionDEBUG::SetPrepare__________TEST()
{
	if (SelectTestUnit)
	{
		TArray<AActor*> allUnits;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), allUnits);
		for (int32 i = 0; i < allUnits.Num(); i++)
		{
			int32 targetSide = 1;
			int32 targetShift = 1;
			AUnit* unit = Cast<AUnit>(allUnits[i]);
			if (unit->GameName == UnitForAttackName)
			{


				// ** Weapon min-Di
				float dist = 100.f;


				// ** shift on side
			

				UnitTarget = unit;

				// ** TEST Position
				

				FVector upDir = SelectTestUnit->GetActorLocation() + SelectTestUnit->GetActorUpVector() * 10000;
				PrepareMarcer(upDir, UnitTarget);
			}
		}
	}
}



void AMyFractionDEBUG::Attack______________SET()
{
	Attack_Performance(UnitForAttackName, false);
}

void AMyFractionDEBUG::Attack______________ADD()
{
	Attack_Performance(UnitForAttackName, true);
}


void AMyFractionDEBUG::Attack_Performance(FName _UnitForAttackName, bool _bAddMoreOneTask)
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