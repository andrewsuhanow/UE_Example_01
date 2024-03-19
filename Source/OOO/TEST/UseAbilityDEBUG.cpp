

// #include "TEST/UseAbilityDEBUG.h"
#include "UseAbilityDEBUG.h"



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

//#include "../Base/Ability/Enum/AbilityLogic.h"
#include "../Base/Ability/AbilityComponent.h"
#include "../Base/Controller/Enum/TargetType.h"

#include "../Base/Ability/AbilityDT.h"

#include "../Base/Controller/Task/Base/Task.h"
#include "../Base/Controller/Task/TMoveTo.h"
#include "../Base/Controller/Task/TUnitRotate.h"
#include "../Base/Controller/Task/TCheckPoint.h"
#include "../Base/Controller/Task/TUseAbility.h"

// ** Unit-Effect
#include "../Base/UnitEffect/UnitEffectRealizer/UER_ChangeUnitParam.h"

#include "../Base/Item/WorldItem.h"

//---------------------------------------------

#include "Kismet/GameplayStatics.h"   // ** GetAllActorsOfClass()

#include "DrawDebugHelpers.h"









AUseAbilityDEBUG::AUseAbilityDEBUG()
{
	PrimaryActorTick.bCanEverTick = true;
	   
	UnitTargetName.Add(FName("Un5_DrawWpn"));
	UnitTargetName.Add(FName("Un3"));
	UnitTargetName.Add(FName("Un6"));

}


void AUseAbilityDEBUG::BeginPlay()
{
	Super::BeginPlay();

}

void AUseAbilityDEBUG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// ************************    Select Unit


void AUseAbilityDEBUG::SelctUn_1()
{
	SelctUn_Performance(SelectUnitName_1);
}
void AUseAbilityDEBUG::SelctUn_2()
{
	SelctUn_Performance(SelectUnitName_2);
}
void AUseAbilityDEBUG::SelctUn_3()
{
	SelctUn_Performance(SelectUnitName_3);
}
void AUseAbilityDEBUG::SelctUn_4()
{
	SelctUn_Performance(SelectUnitName_4);
}
void AUseAbilityDEBUG::SelctUn_Performance(FName _SelectUnitName)
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


			// ** Init and Add Ability to unit
			if (AbiilityAddToFastPanel.Num() == 0)
			{
				/*AbiilityAddToFastPanel.Add(FName("TEST__TargetLocation"));
				AbiilityAddToFastPanel.Add(FName("TEST__TargetOneUnit"));
				AbiilityAddToFastPanel.Add(FName("TEST__SelfAnimateOnly"));
				AbiilityAddToFastPanel.Add(FName("FireBolt"));
				AbiilityAddToFastPanel.Add(FName("FireExplosion"));
				AbiilityAddToFastPanel.Add(FName("Health"));*/
			}
			for (int32 m = 0; m < AbiilityAddToFastPanel.Num(); ++m)
			{
//+++++				SelectTestUnit->AddAbilityByName(AbiilityAddToFastPanel[m]);
			}




			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		}
	}

	// ** ShowPerkPanel();
	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SelectTestUnit && hud)
	{
		hud->ShowPerkPanel(SelectTestUnit);

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}



// **************************

void AUseAbilityDEBUG::AddAbility()
{
	if (SelectTestUnit)
	{
		for (int32 i = 0; i < AbilityClass.Num(); ++i)
		{
			SelectTestUnit->AddAbilityByClass(AbilityClass[i]);
		}
	}

	////if (SelectTestUnit)
	{
		////SelectTestUnit->AddAbility(EAbilityType::drink);
		////SelectTestUnit->AddAbility(EAbilityType::harvest);
		////SelectTestUnit->AddAbility(EAbilityType::health);
		////SelectTestUnit->AddAbility(EAbilityType::usem_middle);
		////SelectTestUnit->AddAbility(EAbilityType::pick_up);
		////SelectTestUnit->AddAbility(EAbilityType::throw_sing);
	}

	// ** ShowPerkPanel();
	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SelectTestUnit && hud)
	{
		hud->ShowPerkPanel(SelectTestUnit);

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}

void AUseAbilityDEBUG::Add_ToFastPanel()
{

	// ** ShowFastPanel();
	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	ABaseGameState* GameState1 = Cast<ABaseGameState>(GetWorld()->GetGameState());
	if (GameState1 && GameState1->GetCountOfSelectUnits() == 1)
	{
		SelectTestUnit = GameState1->GetSelectedUnit(0);
	}


	// ** Init and Add Ability to unit
	

	if (AbiilityAddToFastPanel.Num() == 0)
	{
		//AddAbility();
	}
/*		AbiilityAddToFastPanel.Add(FName("FireBolt"));
		AbiilityAddToFastPanel.Add(FName("FireExplosion"));
		AbiilityAddToFastPanel.Add(FName("Health"));
	}
	for (int32 m = 0; m < AbiilityAddToFastPanel.Num(); ++m)
	{
//+++++		SelectTestUnit->AddAbilityByName(AbiilityAddToFastPanel[m]);
	}
*/


	//if (AbilityIndexToFastPanel < 0 || AbilityIndexToFastPanel >= AbiilityAddToFastPanel.Num())
	//	return;

	//if (AbilityIndexToFastPanel >= 0) //&& AbiilityAddToFastPanel[AbilityIndexToFastPanel] != FName("none"))
	{
		SelectTestUnit->SetAbilityToFastPanelByIndex(AbilityIndexToFastPanel, FastPanelSlotIndex);
	}

	
	if (SelectTestUnit && hud)
	{
		hud->ShowFastPanel(SelectTestUnit);

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}


// **************************


void AUseAbilityDEBUG::PrepareToUseAbilitty()
{
	if (SelectTestUnit)
	{

	}
}

void AUseAbilityDEBUG::UseAbility______SET()
{
	UseAbilityk_Performance(UnitTargetName, false);
}

void AUseAbilityDEBUG::UseAbility______ADD()
{
	UseAbilityk_Performance(UnitTargetName, true);
}


void AUseAbilityDEBUG::UseAbilityk_Performance(TArray<FName> _UnitTargetName, bool _bAddMoreOneTask)
{
	if (SelectTestUnit)
	{

		//if (UseAbilityIndex < 0 ||
		//	UseAbilityIndex >= AbiilityAddToFastPanel.Num() ||
		//	AbiilityAddToFastPanel[UseAbilityIndex] == FName("none"))
		//	return;




		{
			TArray<AActor*> allUnits;
			TArray<AUnit*> TargetUnits;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), allUnits);
			// ** Geterate Target-Units
			for (int32 i = 0; i < allUnits.Num(); i++)
			{
				AUnit* unit = Cast<AUnit>(allUnits[i]);
				for (int32 k = 0; k < _UnitTargetName.Num(); k++)
				{
					if (unit->GameName == _UnitTargetName[k])
					{
						TargetUnits.Add(unit);
						break;
					}
				}
			}

			FTaskData abilityTaskData;
			UTUseAbility::SetTaskData_UseAbilityToUnit(abilityTaskData,
				SelectTestUnit, UseAbilityIndex, false, TargetUnits); // ** false - is item or ability

			SelectTestUnit->SetUnitTask(false, ETaskType::UseAbility, abilityTaskData);
		}
		
/*		bool isHasAbility = SelectTestUnit->Ability->FindUnitAbilityByName(AbiilityAddToFastPanel[UseAbilityIndex], _AbolityRef);

		FTaskData taskData;
		switch (_AbolityRef->DefaultTargetType)
		{

		case ETargetType::Unit:
		{	
			TArray<AActor*> allUnits;
			TArray<AUnit*> TargetUnits;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), allUnits);
			// ** Geterate Target-Units
			for (int32 i = 0; i < allUnits.Num(); i++)
			{
				AUnit* unit = Cast<AUnit>(allUnits[i]);
				for (int32 k = 0; k < _UnitTargetName.Num(); k++)
				{
					if (unit->GameName == _UnitTargetName[k])
					{
						TargetUnits.Add(unit);
						break;
					}
				}
			}
			// ** Use Ability
			if (TargetUnits.Num() > 0)
			{
				UTUseAbility::SetTaskData_UseAbilityToUnit(taskData, SelectTestUnit, AbiilityAddToFastPanel[UseAbilityIndex], TargetUnits);
				SelectTestUnit->SetUnitTask(_bAddMoreOneTask, ETaskType::UseAbility, taskData);
			}
			break;
		}
		case ETargetType::Location:

			UTUseAbility::SetTaskData_UseAbilityToLocation(taskData, SelectTestUnit, AbiilityAddToFastPanel[UseAbilityIndex], PointTargetLocation);
			SelectTestUnit->SetUnitTask(_bAddMoreOneTask, ETaskType::UseAbility, taskData);
			break;

		default: // ** ETargetType::none:

			UTUseAbility::SetTaskData_UseAbility(taskData, SelectTestUnit, AbiilityAddToFastPanel[UseAbilityIndex]);
			SelectTestUnit->SetUnitTask(_bAddMoreOneTask, ETaskType::UseAbility, taskData);
			
		}
*/
	}
}

// UTUseAbility::SetTaskData_UseAbilityToUnit(taskData, SelectTestUnit, AbilityName, Location);    
// UTUseAbility::SetTaskData_UseAbility(taskData, SelectTestUnit, AbilityName);    



void AUseAbilityDEBUG::InitEffect()
{

	TatgUnitName.Reset();
	TatgUnitName.Add(FName("Un6_Ability"));
	TatgUnitName.Add(FName("Un2"));
	TatgUnitName.Add(FName("Un5_DrawWpn"));

	UnitEffects.Reset();
	UTexture2D* texture = nullptr;

	{
		FUnitEffectDT unitEffectDT_TMP;

		FUnitParamModifier unitParamModifierTMP;
		unitParamModifierTMP.ModifierType = FMath::RandRange(8, 13);
		unitParamModifierTMP.UnitParam = EUnitParam::HP;
		unitParamModifierTMP.Value = 3.f;

		unitEffectDT_TMP.UnitParamModifier.Add(unitParamModifierTMP);
		unitEffectDT_TMP.UnitEffectRealizer = UUER_ChangeUnitParam::StaticClass();

		UnitEffects.Add(unitEffectDT_TMP);

		texture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/MagikIcon/Health.Health"));
		UnitEffects.Last().EffectImage = texture;
		UnitEffects.Last().IsUnitEffectCanBeCanel = false;

		UnitEffectsName.Add(FName("HP + 3,  Duration,    Health-Icon,   NOT-Break"));
	}

	{
		FUnitEffectDT unitEffectDT_TMP;

		FUnitParamModifier unitParamModifierTMP;
		unitParamModifierTMP.ModifierType = FMath::RandRange(8, 13);
		unitParamModifierTMP.UnitParam = EUnitParam::HP;
		unitParamModifierTMP.Value = -3.f;

		unitEffectDT_TMP.UnitParamModifier.Add(unitParamModifierTMP);
		unitEffectDT_TMP.UnitEffectRealizer = UUER_ChangeUnitParam::StaticClass();

		UnitEffects.Add(unitEffectDT_TMP);

		texture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/MagikIcon/FireArea.FireArea"));
		UnitEffects.Last().EffectImage = texture;

		UnitEffectsName.Add(FName("HP - 3,  Duration,   Flame-Icon"));
	}

	{
		FUnitEffectDT unitEffectDT_TMP;

		FUnitParamModifier unitParamModifierTMP;
		unitParamModifierTMP.ModifierType = ONCE;
		unitParamModifierTMP.UnitParam = EUnitParam::HP;
		unitParamModifierTMP.Value = 15.f;

		unitEffectDT_TMP.UnitParamModifier.Add(unitParamModifierTMP);
		unitEffectDT_TMP.UnitEffectRealizer = UUER_ChangeUnitParam::StaticClass();

		UnitEffects.Add(unitEffectDT_TMP);

		texture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/DebugAbility/Red_Potion.Red_Potion"));
		UnitEffects.Last().EffectImage = texture;

		UnitEffectsName.Add(FName("HP + 15  Once"));
	}

	{
		FUnitEffectDT unitEffectDT_TMP;

		FUnitParamModifier unitParamModifierTMP;
		unitParamModifierTMP.ModifierType = ONCE;
		unitParamModifierTMP.UnitParam = EUnitParam::HP;
		unitParamModifierTMP.Value = -15.f;

		unitEffectDT_TMP.UnitParamModifier.Add(unitParamModifierTMP);
		unitEffectDT_TMP.UnitEffectRealizer = UUER_ChangeUnitParam::StaticClass();

		UnitEffects.Add(unitEffectDT_TMP);

		texture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/MagikIcon/FireExplosion.FireExplosion"));
		UnitEffects.Last().EffectImage = texture;

		UnitEffectsName.Add(FName("HP - 15,  Once"));
	}
	

	{
		FUnitEffectDT unitEffectDT_TMP;

		FUnitParamModifier unitParamModifierTMP;
		unitParamModifierTMP.ModifierType = ONGOING;
		unitParamModifierTMP.UnitParam = EUnitParam::HP;
		unitParamModifierTMP.Value = 3.f;

		unitEffectDT_TMP.UnitParamModifier.Add(unitParamModifierTMP);
		unitEffectDT_TMP.UnitEffectRealizer = UUER_ChangeUnitParam::StaticClass();

		UnitEffects.Add(unitEffectDT_TMP);

		texture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/MagikIcon/FireExplosion.FireExplosion"));
		UnitEffects.Last().EffectImage = texture;
		UnitEffects.Last().IsUnitEffectCanBeCanel = true;

		UnitEffectsName.Add(FName("HP + 3,  Ongoing,  can-Be-break"));
	}

	{
		FUnitEffectDT unitEffectDT_TMP;

		FUnitParamModifier unitParamModifierTMP;
		unitParamModifierTMP.ModifierType = ONGOING;
		unitParamModifierTMP.UnitParam = EUnitParam::HP;
		unitParamModifierTMP.Value = 3.f;

		unitEffectDT_TMP.UnitParamModifier.Add(unitParamModifierTMP);
		unitEffectDT_TMP.UnitEffectRealizer = UUER_ChangeUnitParam::StaticClass();

		UnitEffects.Add(unitEffectDT_TMP);

		texture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Test/TextureUI/UI/MagikIcon/FireExplosion.FireExplosion"));
		UnitEffects.Last().EffectImage = texture;
		UnitEffects.Last().IsUnitEffectCanBeCanel = false;

		UnitEffectsName.Add(FName("HP + 3,  Ongoing,  NOT-break"));
	}
}

void AUseAbilityDEBUG::AddEffect()
{
	if (SelectTestUnit && UnitEffectsIndex >= 0 && UnitEffectsIndex < UnitEffects.Num())
	{
		TArray<AActor*> allUnits;
		TArray<AUnit*> targetUnits;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), allUnits);
		// ** Geterate Target-Units
		for (int32 i = 0; i < allUnits.Num(); i++)
		{
			AUnit* unit = Cast<AUnit>(allUnits[i]);
			for (int32 k = 0; k < TatgUnitName.Num(); k++)
			{
				if (unit->GameName == TatgUnitName[k])
				{
					targetUnits.Add(unit);
					break;
				}
			}
		}
		// ** Add Unit-Effect
		for (int32 k = 0; k < targetUnits.Num(); k++)
		{
 			targetUnits[k]->AddUnitEffect(&UnitEffects[UnitEffectsIndex]);		// ** FUnitEffectDT

			DrawDebugSphere(
				 GetWorld(),
				 targetUnits[k]->GetActorLocation(), // center
				 30.f, // radius
				 20, // Segments
				 FColor(FColor::Yellow),
				 false, // bPersistLine
				 3.5f, //GetWorld()->GetDeltaSeconds() * 3,
				 5, // DepthPriority
				 5); // Thick
		}
	}
}


