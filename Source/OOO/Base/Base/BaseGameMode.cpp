

//#include "Base/Base/BaseGameMode.h"
#include "BaseGameMode.h"

#include "BaseGameState.h"
#include "Spectator.h"
#include "../HUD/BaseHUD.h"
#include "../HUD/Widget/W_Screen.h"
#include "../HUD/Widget/Slot/W_Slot.h"
//----#include "../HUD/Widget/Slot/W_EffectSlot.h"

#include "../Unit/Base/Unit.h"
#include "../Controller/UnitAI.h"
#include "../Controller/Fraction/FractionController.h"

//----------------

#include "Kismet/GameplayStatics.h"   // ** GetAllActorsOfClass(),  QuitGame()

#include "Engine/DataTable.h"

ABaseGameMode::ABaseGameMode()
{
	
	// *******************************************    Fraction    *****************************************
	Fraction = CreateDefaultSubobject<UFractionSystem>(TEXT("Fraction"));
	// ** SET in UE
	FractionsAttitude.Add(FFractionUnit(0, 1, EUnitAttitudeStatus::Enemy));
	FractionsAttitude.Add(FFractionUnit(0, 2, EUnitAttitudeStatus::Enemy));
	FractionsAttitude.Add(FFractionUnit(0, 3, EUnitAttitudeStatus::Friend));
	FractionsAttitude.Add(FFractionUnit(1, 2, EUnitAttitudeStatus::Enemy));
	FractionsAttitude.Add(FFractionUnit(1, 3, EUnitAttitudeStatus::Friend));
	FractionsAttitude.Add(FFractionUnit(2, 3, EUnitAttitudeStatus::Enemy));

}


void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	// ** Init-Animation
	InitAnimations();

	// ** "Game-Delay" 
	GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::StartGame, 1.f, false);

}

void ABaseGameMode::StartGame()
{

	// ****** 11111111111 (NEED exec before other) 
	// *******************************************    Set GameState    *****************************************
	
	if (!BGameState)
	{
		AGameStateBase* SimpleGameState = GetWorld()->GetGameState();
		if (nullptr == (BGameState = Cast<ABaseGameState>(SimpleGameState)))
		{
			if (BaseGameState_Class)
			{
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.Instigator = GetInstigator();
				SpawnInfo.ObjectFlags |= RF_Transient;	// ** We never want to save game states or network managers into a map

				BGameState = GetWorld()->SpawnActor<ABaseGameState>(BaseGameState_Class, SpawnInfo);
				GetWorld()->SetGameState(BGameState);
				if (BGameState)
				{
					BGameState->AuthorityGameMode = this;

					if (SimpleGameState)
						SimpleGameState->Destroy();
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame():  'GameState' not init"));
					GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::StartGame, 1.f, false);
					return;
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame():  'GameState' not init   >>>>>>>>   'BaseGameState_Class' - absent"));
				UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, true);
				return; 
			}
		}
	}

	// ****** 11111111111 (NEED exec before other) 
	
	if (!HUD)
	{
		AHUD* SimpleHud = GetWorld()->GetFirstPlayerController()->GetHUD();
		if (nullptr == (HUD = Cast<ABaseHUD>(SimpleHud)))
		{
			if (BaseHUD_Class)
			{
				GetWorld()->GetFirstPlayerController()->ClientSetHUD(BaseHUD_Class);
				HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
				if (!HUD)
				{
					//HUD->Init(W_Screen_Class);
					UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame():  'HUD' not init"));
					GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::StartGame, 1.f, false);
					return;
				}
				if (SimpleHud)
					SimpleHud->Destroy();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame():  'HUD' not init   >>>>>>>>   'BaseHUD_Class' - absent"));
				UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, true);
				return;
			}
		}

		if (!W_Screen_Class || !W_Slot_Class)//---------- || !W_EffectSlot_Class)
		{
			UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR:    ABaseGameMode::Init():  'W_Screen' not init   >>>>>>>>   'W_Screen_Class' - absent"));
			UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, true);
			return;
		}
		else if (!HUD->Init(W_Screen_Class))
		{
			GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::StartGame, 1.f, false);
			return;
		}
	}

	// ****** 11111111111 (NEED exec before other)

	if (!Spectator)
	{
		TArray<AActor*> SpecPawn;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Spectator_Class, SpecPawn);

		if (SpecPawn.Num() > 0)
		{
			Spectator = Cast<ASpectator>(SpecPawn[0]);
		}
		else
		{
			if (Spectator_Class)
			{
				// ** Spawn new PawnSpectator
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				Spectator = GetWorld()->SpawnActor<ASpectator>(Spectator_Class, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame():  'ASpectator' not init   >>>>>>>>   'Spectator_Class' - dont set"));
				UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, true);
				return;
			}
		}
		// ** Posses to new PawnSpectator
		GetWorld()->GetFirstPlayerController()->Possess(Spectator);
	}





	// ** Remove All default classes
	TArray<AActor*> DefaultPawn;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DefaultPawnClass, DefaultPawn);
	if (DefaultPawn.Num() > 0)
	{	
		/// ** DefaultPawnClass = Spectator_Class;
		DefaultPawn[0]->Destroy();
	}
	TArray<AActor*> DefaultSpectator;


	


/*
	if (!GameAbilityArchive)
	{
		UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR:    ABaseGameMode::Init():     >>>>>>>>   'GameAbilityArchive' - absent"));
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, true);
	}
*/

	// *******************************************    Init fraction    *****************************************
	if (!Fraction)
	{	
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame(): \"Fraction\" not init"));
		GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::StartGame, 1.f, false);
		return;
	}
	else
	{
		Fraction->Init(FractionsAttitude);
		UE_LOG(LogTemp, Log, TEXT(">>>>>>>>>> OK: ABaseGameMode::StartGame(): \"Fraction\" Init Succes"));
	}


	// **************************************    Set default game param    ************************************



	HUD->SetDefaultGameParam(this, BGameState, Spectator);

	BGameState->SetDefaultGameParam(this, HUD, Spectator);

	Spectator->SetDefaultGameParam(this, HUD, BGameState);


	// ********************    All Scene-Units Init    ********************
	SceneUnitsInit();
}


void ABaseGameMode::SceneUnitsInit()
{
	TArray<AActor*> UnitsIt;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), UnitsIt);
	for (int32 i = 0; i < UnitsIt.Num(); ++i)
	{
		AUnit*unit = Cast<AUnit>(UnitsIt[i]);
		if (unit)
		{
			bool isSucces = unit->StartGame(false);
			if (!isSucces)
			{
				GetWorld()->GetTimerManager().SetTimer(TH_SceneUnitsInit, this, &ThisClass::SceneUnitsInit, 0.5f, false);
				return;
			}
		}
	}


	// ** Finish Unit-Init

	for (int32 i = 0; i < UnitsIt.Num(); ++i)
	{
		AUnit* unit = Cast<AUnit>(UnitsIt[i]);
		if (unit)
		{
			if (unit->Fraction >= FractionController.Num())
			{
				// @@@@@@@  Create New Fraction
				// @@@@@@@  Create New Fraction
				// @@@@@@@  Create New Fraction
			}
			for(int32 f = 0; i < FractionController.Num(); ++f)
				if (FractionController[f]->FractionIndex == unit->Fraction)
				{
					FractionController[f]->RegisterUnit(unit);
					break;
				}


			unit->StartGame(true);

			// ** XXXXXXXXXXXXXXX
			BGameState->TurnBaseGmStateSender.AddUObject(unit->AI, &AUnitAI::OnChangeTurnBaseGameState);
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(TH_SceneUnitsInit);

}



// ****************************************************************************************************	
// **********************************      Default Game Param      ************************************

UAnimMontage* ABaseGameMode::GetGameAnimation(EUnitGameType _UnitGameType,
	EWeaponType _WeaponType, 
	EAnimationKey _AnimationKey)
{
	for (int32 i = 1; i <= 2; ++i)
	{
		FWeaponAnimateGroup* unitGroup = GameAnimation.Find(_UnitGameType);
		if (unitGroup)
		{
			FAnimateGroup* animGroup = unitGroup->WeaponGroupAnimation.Find(_WeaponType);
			if (animGroup)
			{
				auto animMontag = animGroup->Animation.Find(_AnimationKey);
				if (animMontag)
					return *animMontag;
			}
		}

		// ** if cant find in current Weapon-AnimGroup, try find in Locomotion-AnimGroup
		_WeaponType = EWeaponType::Locomotion;
	}
	return nullptr;
}










// ** TEST  TEST   TEST
// ** TEST  TEST   TEST
// ** TEST  TEST   TEST				// ** All Game animations  (need add in Game-Mod  (TMap <Unit, (TMap <Weapon, (TMap <AnimKEY, Animation))>>>))
// ** TEST  TEST   TEST
// ** TEST  TEST   TEST
void ABaseGameMode::InitAnimations()
{

	FWeaponAnimateGroup weaponElement;
	FAnimateGroup animElement;
	UAnimMontage* montage_use = nullptr;
	UAnimMontage* montage_equip = nullptr;
	UAnimMontage* montage_unequip = nullptr;
	UAnimMontage* montage_attack1 = nullptr;
	UAnimMontage* montage_attack2 = nullptr;
	UAnimMontage* montage_attack3 = nullptr;
	UAnimMontage* montage_attack4 = nullptr;
	UAnimMontage* montage_attack5 = nullptr;
	UAnimMontage* montage_failedAttackParrired = nullptr;
	UAnimMontage* montage_block = nullptr;
	UAnimMontage* montage_parrir = nullptr;
	UAnimMontage* montage_dodge_back = nullptr;
	UAnimMontage* montage_attack_1_novice = nullptr;
	UAnimMontage* montage_attack_2_novicer = nullptr;
	UAnimMontage* montage_attack2_altern = nullptr;
	UAnimMontage* montage_attack3_altern = nullptr;
	UAnimMontage* montage_attack4_altern = nullptr;

	UAnimMontage* montage_Throw_Prepare = nullptr;
	UAnimMontage* montage_Throw_Loop = nullptr;
	UAnimMontage* montage_Throw_Cast = nullptr;

	UAnimMontage* throw_spell_Prepare_mid = nullptr;
	UAnimMontage* throw_spell_Loop_mid = nullptr;
	UAnimMontage* throw_spell_cast_mid = nullptr;
	
	// **      7777777777777777
	
	montage_use = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Shared_Mutual/Cast___LaftHand___AO/M_Ability_E.M_Ability_E"));
	montage_parrir = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Parir/M_Parrir____Longs_Block_p_L___Faster.M_Parrir____Longs_Block_p_L___Faster"));
	montage_failedAttackParrired = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Hit/FailedAttackParir.FailedAttackParir"));
	montage_block = LoadObject<UAnimMontage>(nullptr, TEXT("AnimMontage'/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Block/AsCatana/Long_BlockLoop.Long_BlockLoop"));
	montage_dodge_back = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Dodge/Longs_DodgeBack.Longs_DodgeBack"));

	throw_spell_Prepare_mid = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Fire_as_rifle/M_OneShoot__lSw_PapidFire_Big.M_OneShoot__lSw_PapidFire_Big"));
	throw_spell_Loop_mid = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Bow/Idle/M_Bow_Aim_Loop.M_Bow_Aim_Loop"));
	throw_spell_cast_mid = LoadObject<UAnimMontage>(nullptr, TEXT("AnimMontage'/Game/Test/CharacterHuman/Animation/Human/Dagger/M_Dagge_BaseAttack_1.M_Dagge_BaseAttack_1'"));

	montage_Throw_Prepare = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Shared_Mutual/Cast___LeftPistol__AO/M_ShotGun_FireHolster.M_ShotGun_FireHolster"));
	montage_Throw_Loop = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Shared_Mutual/ThrowItem/Rifle_Grenade_Throw_Loop_Montage.Rifle_Grenade_Throw_Loop_Montage"));
	montage_Throw_Cast = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Shared_Mutual/ThrowItem/M_Rifle_Grenade_Throw_Far.M_Rifle_Grenade_Throw_Far"));

	if (montage_use)	animElement.Animation.Add(EAnimationKey::use, montage_use);
	if (montage_equip)	animElement.Animation.Add(EAnimationKey::equip, montage_equip);
	if (montage_unequip)	animElement.Animation.Add(EAnimationKey::unequip, montage_unequip);
	if (montage_attack1)	animElement.Animation.Add(EAnimationKey::attack1, montage_attack1);
	//if (montage_attack2)	animElement.Animation.Add(EAnimationKey::attack2, montage_attack2);
	//if (montage_attack3)	animElement.Animation.Add(EAnimationKey::attack3, montage_attack3);
	//if (montage_attack4)	animElement.Animation.Add(EAnimationKey::attack4, montage_attack4);
	//if (montage_attack5)	animElement.Animation.Add(EAnimationKey::attack5, montage_attack5);
	if (montage_block)	animElement.Animation.Add(EAnimationKey::block, montage_block);
	if (montage_parrir)	animElement.Animation.Add(EAnimationKey::parrir, montage_parrir);
	if (montage_dodge_back)	animElement.Animation.Add(EAnimationKey::dodge_bwd, montage_dodge_back);

	if (throw_spell_Prepare_mid)	animElement.Animation.Add(EAnimationKey::throw_spell_Prepare_mid, throw_spell_Prepare_mid);
	if (throw_spell_Loop_mid)	animElement.Animation.Add(EAnimationKey::throw_spell_Loop_mid, throw_spell_Loop_mid);
	if (throw_spell_cast_mid)	animElement.Animation.Add(EAnimationKey::throw_spell_cast_mid, throw_spell_cast_mid);

	if (montage_failedAttackParrired)	animElement.Animation.Add(EAnimationKey::failed_attack_parrired, montage_failedAttackParrired);

	if (montage_Throw_Prepare)	animElement.Animation.Add(EAnimationKey::throw_Prepare_up, montage_Throw_Prepare);
	if (montage_Throw_Loop)	animElement.Animation.Add(EAnimationKey::throw_Loop_up, montage_Throw_Loop);
	if (montage_Throw_Cast)	animElement.Animation.Add(EAnimationKey::throw_cast_up, montage_Throw_Cast);

	//if (montage_attack_1_novice)	animElement.Animation.Add(EAnimationKey::attack_1_novice, montage_attack_1_novice);
	//if (montage_attack_2_novicer)	animElement.Animation.Add(EAnimationKey::attack_2_novice, montage_attack_2_novicer);
	//if (montage_attack2_altern)	animElement.Animation.Add(EAnimationKey::attack2_altern, montage_attack2_altern);
	//if (montage_attack3_altern)	animElement.Animation.Add(EAnimationKey::attack3_altern, montage_attack3_altern);
	//if (montage_attack4_altern)	animElement.Animation.Add(EAnimationKey::attack4_altern, montage_attack4_altern);
	montage_use = montage_equip = montage_unequip = montage_attack1 = montage_attack2 =
	montage_attack3 = montage_attack4 = montage_attack5 = montage_parrir =
	montage_attack_1_novice = montage_attack_2_novicer = montage_attack2_altern = montage_attack3_altern = montage_attack4_altern = nullptr;

	weaponElement.WeaponGroupAnimation.Add(EWeaponType::Locomotion, animElement);
	animElement.Animation.Reset();



	montage_equip = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/NoWeapon__Fight/ReadyOnOff/M_Idle2Fists.M_Idle2Fists"));
	montage_unequip = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/NoWeapon__Fight/ReadyOnOff/M_Fists2Idle.M_Fists2Idle"));
	montage_attack1 = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/NoWeapon__Fight/Attack/M_Fists_InPlace_Heavy1.M_Fists_InPlace_Heavy1"));
	montage_attack2 = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/NoWeapon__Fight/Attack/M_NoWpn_Attack_1_Fists_Punch_Move_L.M_NoWpn_Attack_1_Fists_Punch_Move_L"));
	montage_parrir = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Parir/M_Parrir____Longs_Block_p_L___Faster.M_Parrir____Longs_Block_p_L___Faster"));
	//animElement.Animation.Add(EAnimationKey::use, frffff);
	if (montage_equip)	animElement.Animation.Add(EAnimationKey::equip, montage_equip);
	if (montage_unequip)	animElement.Animation.Add(EAnimationKey::unequip, montage_unequip);
	if (montage_attack1)	animElement.Animation.Add(EAnimationKey::attack1, montage_attack1);
	if (montage_attack2)	animElement.Animation.Add(EAnimationKey::attack2, montage_attack2);
	if (montage_parrir)animElement.Animation.Add(EAnimationKey::parrir, montage_parrir);
	//animElement.Animation.Add(EAnimationKey::attack2, frffff);
	//animElement.Animation.Add(EAnimationKey::attack3, frffff);
	//animElement.Animation.Add(EAnimationKey::attack4, frffff);
	//animElement.Animation.Add(EAnimationKey::attack5, frffff);
	//animElement.Animation.Add(EAnimationKey::block, frffff);
	//animElement.Animation.Add(EAnimationKey::parrir, frffff);
	//if (montage_attack_1_novice)	animElement.Animation.Add(EAnimationKey::attack_1_novice, montage_parrir);
	//if (montage_attack_2_novicer)	animElement.Animation.Add(EAnimationKey::attack_2_novice, montage_parrir);
	//if (montage_attack2_altern)	animElement.Animation.Add(EAnimationKey::attack2_altern, montage_parrir);
	//if (montage_attack3_altern)	animElement.Animation.Add(EAnimationKey::attack3_altern, montage_parrir);
	//if (montage_attack4_altern)	animElement.Animation.Add(EAnimationKey::attack4_altern, montage_parrir);
	montage_use = montage_equip = montage_unequip = montage_attack1 = montage_attack2 =
	montage_attack3 = montage_attack4 = montage_attack5 = montage_parrir =
	montage_attack_1_novice = montage_attack_2_novicer = montage_attack2_altern = montage_attack3_altern = montage_attack4_altern = nullptr;

	weaponElement.WeaponGroupAnimation.Add(EWeaponType::HandFight, animElement);
	animElement.Animation.Reset();





	//montage_use = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXX"));
	montage_equip = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Weapon_OnOff__Alternate/M_LSw_WeaponOn.M_LSw_WeaponOn"));
	montage_unequip = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Weapon_OnOff__Alternate/M_LSw_WeaponOff.M_LSw_WeaponOff"));
	montage_attack1 = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Attack_Range_1/M_LSw_Attack_1_b__Longs_Attack_RD.M_LSw_Attack_1_b__Longs_Attack_RD"));
	montage_attack2 = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Attack_Range_1/M_LSw_Attack_2_b__Longs_Attack_LD.M_LSw_Attack_2_b__Longs_Attack_LD"));
	montage_attack3 = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Attack_Range_1/M_LSw_Attack_3_b__Longs_Attack_L.M_LSw_Attack_3_b__Longs_Attack_L"));
	montage_attack4 = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Attack_Range_2/M_LSw_Attack_4_c__Longs_Attack_D.M_LSw_Attack_4_c__Longs_Attack_D"));
	montage_attack5 = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Attack_Range_1/M_LSw_Sting_Attack_A_b__CC.M_LSw_Sting_Attack_A_b__CC"));
	montage_block = LoadObject<UAnimMontage>(nullptr, TEXT("AnimMontage'/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Block/AsCatana/Long_BlockLoop.Long_BlockLoop'"));
	montage_dodge_back = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Dodge/Longs_DodgeBack.Longs_DodgeBack"));
	//montage_parrir = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	montage_attack_1_novice = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Attack_Range_0/M_LSw_Attack_1_a__Longs_Attack_RD2.M_LSw_Attack_1_a__Longs_Attack_RD2"));
	montage_attack_2_novicer = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Attack_Range_0/M_LSw_Attack_2_a__Sword_Attack_Sp_U.M_LSw_Attack_2_a__Sword_Attack_Sp_U"));
	montage_attack2_altern = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Attack_Range_1/M_LSw_Attack_2a_b__Longs_Attack_L__After-15.M_LSw_Attack_2a_b__Longs_Attack_L__After-15"));
	montage_parrir = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Parir/M_Parrir____Longs_Block_p_L___Faster.M_Parrir____Longs_Block_p_L___Faster"));
	montage_failedAttackParrired = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Hit/FailedAttackParir.FailedAttackParir"));
	//montage_attack3_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack4_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	if (montage_use)	animElement.Animation.Add(EAnimationKey::use, montage_use);
	if (montage_equip)	animElement.Animation.Add(EAnimationKey::equip, montage_equip);
	if (montage_unequip)	animElement.Animation.Add(EAnimationKey::unequip, montage_unequip);
	if (montage_attack1)	animElement.Animation.Add(EAnimationKey::attack1, montage_attack1);
	if (montage_attack2)	animElement.Animation.Add(EAnimationKey::attack2, montage_attack2);
	if (montage_attack3)	animElement.Animation.Add(EAnimationKey::attack3, montage_attack3);
	if (montage_attack4)	animElement.Animation.Add(EAnimationKey::attack4, montage_attack4);
	if (montage_attack5)	animElement.Animation.Add(EAnimationKey::attack5, montage_attack5);
	if (montage_failedAttackParrired)	animElement.Animation.Add(EAnimationKey::failed_attack_parrired, montage_failedAttackParrired);
	if (montage_block)	animElement.Animation.Add(EAnimationKey::block, montage_block);
	if (montage_parrir)	animElement.Animation.Add(EAnimationKey::parrir, montage_parrir);
	if (montage_dodge_back)	animElement.Animation.Add(EAnimationKey::dodge_bwd, montage_dodge_back);
	if (montage_attack_1_novice)	animElement.Animation.Add(EAnimationKey::attack_1_novice, montage_attack_1_novice);
	if (montage_attack_2_novicer)	animElement.Animation.Add(EAnimationKey::attack_2_novice, montage_attack_2_novicer);
	if (montage_attack2_altern)	animElement.Animation.Add(EAnimationKey::attack2_altern, montage_attack2_altern);
	if (montage_attack3_altern)	animElement.Animation.Add(EAnimationKey::attack3_altern, montage_attack3_altern);
	if (montage_attack4_altern)	animElement.Animation.Add(EAnimationKey::attack4_altern, montage_attack4_altern);

	montage_use = montage_equip = montage_unequip = montage_attack1 = montage_attack2 = 
	montage_attack3 = montage_attack4 = montage_attack5 = montage_parrir =
	montage_attack_1_novice = montage_attack_2_novicer = montage_attack2_altern = montage_attack3_altern = montage_attack4_altern = nullptr;

	weaponElement.WeaponGroupAnimation.Add(EWeaponType::LongSword, animElement);
	animElement.Animation.Reset();





	//montage_use = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXX"));
	montage_equip = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Gun_Rifle/ReadyOnOff/M_EquipRifle.M_EquipRifle"));
	montage_unequip = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Gun_Rifle/ReadyOnOff/M_HolsterRifle.M_HolsterRifle"));
	montage_attack1 = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Gun_Rifle/Attack/M_Rifle_ShootOnce.M_Rifle_ShootOnce"));
	montage_attack2 = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Gun_Rifle/Attack/M_Rifle_ShootBurstLoop.M_Rifle_ShootBurstLoop"));
	//montage_attack3 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack4 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack5 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_block = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_parrir = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack_1_novice = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack_2_novicer = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack2_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack3_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack4_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	if (montage_use)	animElement.Animation.Add(EAnimationKey::use, montage_use);
	if (montage_equip)	animElement.Animation.Add(EAnimationKey::equip, montage_equip);
	if (montage_unequip)	animElement.Animation.Add(EAnimationKey::unequip, montage_unequip);
	if (montage_attack1)	animElement.Animation.Add(EAnimationKey::attack1, montage_attack1);
	if (montage_attack2)	animElement.Animation.Add(EAnimationKey::attack2, montage_attack2);
	if (montage_attack3)	animElement.Animation.Add(EAnimationKey::attack3, montage_attack3);
	if (montage_attack4)	animElement.Animation.Add(EAnimationKey::attack4, montage_attack4);
	if (montage_attack5)	animElement.Animation.Add(EAnimationKey::attack5, montage_attack5);
	//------if (montage_block)	animElement.Animation.Add(EAnimationKey::block, montage_block);
	if (montage_parrir)	animElement.Animation.Add(EAnimationKey::parrir, montage_parrir);
	if (montage_attack_1_novice)	animElement.Animation.Add(EAnimationKey::attack_1_novice, montage_attack_1_novice);
	if (montage_attack_2_novicer)	animElement.Animation.Add(EAnimationKey::attack_2_novice, montage_attack_2_novicer);
	if (montage_attack2_altern)	animElement.Animation.Add(EAnimationKey::attack2_altern, montage_attack2_altern);
	if (montage_attack3_altern)	animElement.Animation.Add(EAnimationKey::attack3_altern, montage_attack3_altern);
	if (montage_attack4_altern)	animElement.Animation.Add(EAnimationKey::attack4_altern, montage_attack4_altern);
	montage_use = montage_equip = montage_unequip = montage_attack1 = montage_attack2 =
		montage_attack3 = montage_attack4 = montage_attack5 = montage_parrir =
	montage_attack_1_novice = montage_attack_2_novicer = montage_attack2_altern = montage_attack3_altern = montage_attack4_altern = nullptr;

	weaponElement.WeaponGroupAnimation.Add(EWeaponType::RapidGun, animElement);
	animElement.Animation.Reset();

	//montage_use = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXX"));
	//montage_equip = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_unequip = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack1 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack2 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack3 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack4 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack5 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_block = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_parrir = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack_1_novice = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack_2_novicer = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack2_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack3_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack4_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//if (montage_use)	animElement.Animation.Add(EAnimationKey::use, montage_use);
	//if (montage_equip)	animElement.Animation.Add(EAnimationKey::equip, montage_equip);
	//if (montage_unequip)	animElement.Animation.Add(EAnimationKey::unequip, montage_unequip);
	//if (montage_attack1)	animElement.Animation.Add(EAnimationKey::attack1, montage_attack1);
	//if (montage_attack2)	animElement.Animation.Add(EAnimationKey::attack2, montage_attack2);
	//if (montage_attack3)	animElement.Animation.Add(EAnimationKey::attack3, montage_attack3);
	//if (montage_attack4)	animElement.Animation.Add(EAnimationKey::attack4, montage_attack4);
	//if (montage_attack5)	animElement.Animation.Add(EAnimationKey::attack5, montage_attack5);
	//if (montage_block)	animElement.Animation.Add(EAnimationKey::block, montage_block);
	//if (montage_parrir)	animElement.Animation.Add(EAnimationKey::parrir, montage_parrir);
	//if (montage_attack_1_novice)	animElement.Animation.Add(EAnimationKey::attack_1_novice, montage_attack_1_novice);
	//if (montage_attack_2_novicer)	animElement.Animation.Add(EAnimationKey::attack_2_novice, montage_attack_2_novicer);
	//if (montage_attack2_altern)	animElement.Animation.Add(EAnimationKey::attack2_altern, montage_attack2_altern);
	//if (montage_attack3_altern)	animElement.Animation.Add(EAnimationKey::attack3_altern, montage_attack3_altern);
	//if (montage_attack4_altern)	animElement.Animation.Add(EAnimationKey::attack4_altern, montage_attack4_altern);
	//montage_use = montage_equip = montage_unequip = montage_attack1 = montage_attack2 =
	//	montage_attack3 = montage_attack4 = montage_attack5 = montage_block = montage_parrir =
	//montage_attack_1_novice = montage_attack_2_novicer = montage_attack2_altern = montage_attack3_altern = montage_attack4_altern = nullptr;

	//weaponElement.WeaponGroupAnimation.Add(EWeaponType::Sword, animElement);
	//animElement.Animation.Reset();

	//montage_use = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXX"));
	//montage_equip = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_unequip = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack1 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack2 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack3 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack4 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack5 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_block = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_parrir = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack_1_novice = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack_2_novicer = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack2_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack3_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack4_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//if (montage_use)	animElement.Animation.Add(EAnimationKey::use, montage_use);
	//if (montage_equip)	animElement.Animation.Add(EAnimationKey::equip, montage_equip);
	//if (montage_unequip)	animElement.Animation.Add(EAnimationKey::unequip, montage_unequip);
	//if (montage_attack1)	animElement.Animation.Add(EAnimationKey::attack1, montage_attack1);
	//if (montage_attack2)	animElement.Animation.Add(EAnimationKey::attack2, montage_attack2);
	//if (montage_attack3)	animElement.Animation.Add(EAnimationKey::attack3, montage_attack3);
	//if (montage_attack4)	animElement.Animation.Add(EAnimationKey::attack4, montage_attack4);
	//if (montage_attack5)	animElement.Animation.Add(EAnimationKey::attack5, montage_attack5);
	//if (montage_block)	animElement.Animation.Add(EAnimationKey::block, montage_block);
	//if (montage_parrir)	animElement.Animation.Add(EAnimationKey::parrir, montage_parrir);
	//if (montage_attack_1_novice)	animElement.Animation.Add(EAnimationKey::attack_1_novice, montage_attack_1_novice);
	//if (montage_attack_2_novicer)	animElement.Animation.Add(EAnimationKey::attack_2_novice, montage_attack_2_novicer);
	//if (montage_attack2_altern)	animElement.Animation.Add(EAnimationKey::attack2_altern, montage_attack2_altern);
	//if (montage_attack3_altern)	animElement.Animation.Add(EAnimationKey::attack3_altern, montage_attack3_altern);
	//if (montage_attack4_altern)	animElement.Animation.Add(EAnimationKey::attack4_altern, montage_attack4_altern);
	//montage_use = montage_equip = montage_unequip = montage_attack1 = montage_attack2 =
	//	montage_attack3 = montage_attack4 = montage_attack5 = montage_block = montage_parrir =
	//montage_attack_1_novice = montage_attack_2_novicer = montage_attack2_altern = montage_attack3_altern = montage_attack4_altern = nullptr;

	//weaponElement.WeaponGroupAnimation.Add(EWeaponType::Pistol, animElement);

	GameAnimation.Add(EUnitGameType::Human, weaponElement);

	animElement.Animation.Reset();
	weaponElement.WeaponGroupAnimation.Reset();

	// ****************************   Holem   *********************************

	//montage_use = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXX"));
	//montage_equip = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_unequip = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack1 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack2 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack3 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack4 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack5 = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_block = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_parrir = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	montage_attack_1_novice = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Test/CharacterHuman/Animation/Human/Sword_Long/Attack_Range_1/M_LSw_Sting_Attack_A_b__CC.M_LSw_Sting_Attack_A_b__CC"));
	//montage_attack_2_novicer = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack2_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack3_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	//montage_attack4_altern = LoadObject<UAnimMontage>(nullptr, TEXT("XXXXXXXXXXXXXXXXXXXXXXXX"));
	if (montage_use)	animElement.Animation.Add(EAnimationKey::use, montage_use);
	if (montage_equip)	animElement.Animation.Add(EAnimationKey::equip, montage_equip);
	if (montage_unequip)	animElement.Animation.Add(EAnimationKey::unequip, montage_unequip);
	if (montage_attack1)	animElement.Animation.Add(EAnimationKey::attack1, montage_attack1);
	if (montage_attack2)	animElement.Animation.Add(EAnimationKey::attack2, montage_attack2);
	if (montage_attack3)	animElement.Animation.Add(EAnimationKey::attack3, montage_attack3);
	if (montage_attack4)	animElement.Animation.Add(EAnimationKey::attack4, montage_attack4);
	if (montage_attack5)	animElement.Animation.Add(EAnimationKey::attack5, montage_attack5);
	//----if (montage_block)	animElement.Animation.Add(EAnimationKey::block, montage_block);
	if (montage_parrir)	animElement.Animation.Add(EAnimationKey::parrir, montage_parrir);
	if (montage_attack_1_novice)	animElement.Animation.Add(EAnimationKey::attack_1_novice, montage_attack_1_novice);
	if (montage_attack_2_novicer)	animElement.Animation.Add(EAnimationKey::attack_2_novice, montage_attack_2_novicer);
	if (montage_attack2_altern)	animElement.Animation.Add(EAnimationKey::attack2_altern, montage_attack2_altern);
	if (montage_attack3_altern)	animElement.Animation.Add(EAnimationKey::attack3_altern, montage_attack3_altern);
	if (montage_attack4_altern)	animElement.Animation.Add(EAnimationKey::attack4_altern, montage_attack4_altern);
	//montage_use = montage_equip = montage_unequip = montage_attack1 = montage_attack2 =
	//montage_attack3 = montage_attack4 = montage_attack5 = montage_block = montage_parrir =
	//montage_attack_1_novice = montage_attack_2_novicer = montage_attack2_altern = montage_attack3_altern = montage_attack4_altern = nullptr;

	weaponElement.WeaponGroupAnimation.Add(EWeaponType::HandFight, animElement);
	animElement.Animation.Reset();

	GameAnimation.Add(EUnitGameType::Holem, weaponElement);

}




// ****************************************************************************************************	
// *****************************************    Game_Command    ***************************************


bool ABaseGameMode::SpawnUnit(TSubclassOf<AUnit> _UnitType, int32 _Fraction) // @@@@@@@@@@@  TSubclassOf<XXXXXX> 
{
	if (!_UnitType)
		return false;
	if (_Fraction < 0)
		return false;

	AUnit* newUnit = nullptr;
	//++++++++++++++ newUnit = SpawnActor<AUnit>(_UnitType)

	if (_Fraction < FractionController.Num())
	{
		newUnit->SetFraction(_Fraction);
		FractionController[_Fraction]->RegisterUnit(newUnit);
		return true;
	}
	else
	{
		// @@@@@@@  Create New Fraction
		// @@@@@@@  Create New Fraction
		// @@@@@@@  Create New Fraction
	}

	return false;
}






// ****************************************************************************************************	
// *******************************************    Fraction    *****************************************
EUnitAttitudeStatus ABaseGameMode::GetFractionAttitude(uint8 A, uint8 B)
{
	return Fraction->GetAttitude(FractionsAttitude, A, B);
}


// ****************************************************************************************************	
// ***************************************    Global Inventory    *************************************


//...................................




// ****************************************************************************************************	
// *******************************************    Ability    ******************************************



// ****************************************************************************************************	
// ******************************************    Game_Time    *****************************************

int32 ABaseGameMode::GetGameHour()
{
	return Hour;
}


void ABaseGameMode::AddTime(int32 _Hour)
{
	Hour += _Hour;

	// ** Hour > 24 
	// ** Day > 30 
	// ** Month > 12 
	if (Hour > 23)
	{
		Hour = 0;
		++Day;
		if (Day > 30)
		{
			Day = 0;
			++Month;
			if (Month > 12)
			{
				Month = 0;
				++Year;
			}
		}
	}
}