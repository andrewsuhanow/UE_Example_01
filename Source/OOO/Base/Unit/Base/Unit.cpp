
// #include "Base/Unit/Base/Unit.h"
#include "Unit.h"


#include "../../Base/BaseGameMode.h"
#include "../../Base/BaseGameState.h"
#include "../../HUD/BaseHUD.h"

#include "../../UnitState/UnitParamComponent.h"

#include "../../Controller/UnitAI.h"

#include "../../Animation/AnimInstance/HumanAnimInst.h"

#include "../../WorldObject/WayPoint/WayPoint.h"

#include "../../Controller/Task/Base/DailyBhvrQueue.h"		// ** 7777777777777777777
#include "../../Controller/Task/TUseAbility.h"

#include "../../Fraction/FractionSystem.h"

#include "../../Inventory/InventoryComponent.h"

#include "../../Amunition/WeaponComponent.h"
#include "../../Amunition/WeaponDT.h"

#include "../../Amunition/ArmorComponent.h"

#include "../../Ability/AbilityComponent.h"
#include "../../Ability/AbilityDT.h"

//#include "../../Item/WorldItem.h"
#include "../../Amunition/WeaponWorldItem.h"

#include "../../Unit/3DWidget/W_UnitParamBar.h"
#include "../../Unit/3dWidget/UnitParamBar.h"

// --------------------------------------------

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// --------------------------------------------

//#include "../../Base/BaseGameMode.h"
//#include "../../Base/BaseGameState.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Perception/AIPerceptionComponent.h" 
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"			// ** FAIDamageEvent
// --------------------------------------------

#include "Kismet/GameplayStatics.h"   // ** GetAllActorsOfClass()


#include "DrawDebugHelpers.h"			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = true;



	// **  ************************     PERCEPTION     *************************

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightSense"));
	HearingSense = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearSense"));
	DamageSense = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("gamagwSense"));

	Perception->ConfigureSense(*HearingSense);
	Perception->ConfigureSense(*DamageSense);
	Perception->ConfigureSense(*SightSense);

	Perception->SetDominantSense(SightSense->GetSenseImplementation());		// ** Priority Sense

	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::TargetPerceptionUpdated);

	SightSense->SightRadius = 2500;						// ** View 
	SightSense->LoseSightRadius = 3000;					// ** view 
	SightSense->PeripheralVisionAngleDegrees = 70; 		// ** Angle
	SightSense->SetMaxAge(15.f);
	// ** SightSense ->AutoSuccessRangeFromLastSeenLocation = 200;
	SightSense->DetectionByAffiliation.bDetectEnemies = true;
	SightSense->DetectionByAffiliation.bDetectFriendlies = true;
	SightSense->DetectionByAffiliation.bDetectNeutrals = true;

	HearingSense->HearingRange = 3300.f;	// ** Hear 
	HearingSense->SetMaxAge(15.f);
	HearingSense->DetectionByAffiliation.bDetectEnemies = true;
	HearingSense->DetectionByAffiliation.bDetectNeutrals = true;
	HearingSense->DetectionByAffiliation.bDetectFriendlies = true;

	DamageSense->SetMaxAge(15.f);


	
	// **  UnitParam
	UnitParam = CreateDefaultSubobject<UUnitParamComponent>(TEXT("UnitParam"));
	UnitParam->Init();

	// **  Inventory   
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	// **  Ability   
	Ability = CreateDefaultSubobject<UAbilityComponent>(TEXT("Ability"));

	// **  Weapon  
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));

	// **  Armor  
	ArmorComponent = CreateDefaultSubobject<UArmorComponent>(TEXT("Armor"));

	// ** Pose locomotion default param
	if (PoseLocomotionParam.Num() == 0)
	{
		PoseLocomotionParam.Add(FPoseLocomotion());
		PoseLocomotionParam.Last().Pose = EUnitPose::RelaxMove;
		PoseLocomotionParam.Last().MoveSpeed = 200.f;
		PoseLocomotionParam.Last().RotateSpeed = 400.f;

		// ** Crawl		= 200.f
		// ** Crouch	= 300.f
		// ** RelaxMove = 400.f
		// ** FastMove	= 800.f
		// ** Run		= 1200.f
		// ** Sprint	= 1600.f
	}
}


void AUnit::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	// **  AI Controller (Default class)
	if (!AIController_Class)
	{
		UBlueprint * AI_BpClass = LoadObject<UBlueprint>(nullptr, TEXT("/Game/Core/Controller/Base/UnitAi_BP.UnitAi_BP"));
		if (AI_BpClass)
			AIController_Class = (UClass*)AI_BpClass->GeneratedClass;
	}
	if (AIController_Class)	AIControllerClass = AIController_Class;



	// **  AnimInstance (Default class)
	if (AnimInstance_Class)
	{
		GetMesh()->SetAnimInstanceClass(Cast<UAnimBlueprintGeneratedClass>(AnimInstance_Class));
	}
	else
	{
		
		UAnimBlueprint* AnimBp_BpClass = LoadObject<UAnimBlueprint>(nullptr, TEXT("/Game/Core/Animation/AnimInstance/HumanAnimInstance_BP.HumanAnimInstance_BP"));
		if (AnimBp_BpClass)
			GetMesh()->SetAnimInstanceClass(AnimBp_BpClass->GetAnimBlueprintGeneratedClass());
	}

}	

void AUnit::BeginPlay()
{
	Super::BeginPlay();

	
	// ** Collision
	//++++++++++++++++ GetCapsuleComponent()->GetScaledCapsuleSize(CapsuleRadius, CapsuleHalfHaight);

}


bool AUnit::StartGame(bool finalInit)
{
	UE_LOG(LogTemp, Warning, TEXT("ERROR:_______________AUnitAI::Start()_______________Init Continue"));


	if(UnitGameType == EUnitGameType::none)
		UE_LOG(LogTemp, Error, TEXT("ERROR:_______________AUnitAI::Start()_______________'UnitType' is not Init"));



	bool isAllComponentInited = false;


	GameState = Cast<ABaseGameState>(GetWorld()->GetGameState());
	if (!GameState)
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ERROR:   '%s'::AUnit::Init():      'GameState' not Get"), *GetName());

	GameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ERROR:   '%s'::AUnit::Init():      'GameMode' not Get"), *GetName());


	HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (!HUD)
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ERROR:   '%s'::AUnit::Init():      'HUD' not Get"), *GetName());



	// ** Init AI
	if (AI)
		isAllComponentInited = true;
	else
		AI = Cast<AUnitAI>(GetController());
	if (!AI)
	{
		isAllComponentInited = false;
		return false;
	}
	if (finalInit)
	{
		AI->Init(true);
		// **  Anim Finish     
		FinishAnimationDELEGATE.BindUObject(AI, &AUnitAI::OnFinishAnimation);
	}


	// ** Init AnimInstance
	if (AnimInstance)
		isAllComponentInited = true;
	else
		AnimInstance = Cast<UHumanAnimInst>(GetMesh()->GetAnimInstance());
	if(!AnimInstance)
	{
		isAllComponentInited = false;
		return false;
	}

	// ** Invertor param (DEFAULLT)
	if (finalInit)
	{
		if (FullRowNum == 0)
		{
			FullRowNum = GameMode->FullRowNum;
		}
		if (!MainInvertorySlotTexture)
		{
			MainInvertorySlotTexture = GameMode->MainInvertorySlotTexture;
		}

		// ** Inventory Component
		Inventory->Init();

	
		// ** Ability Component
		Ability->Init();


		InitFastPanel();


		// ** Weapon Component
		WeaponComponent->InitWeapons(this);
		

		// ** Armor Component
		ArmorComponent->InitArmor(this);

		SetPose(EUnitPose::RelaxMove);

		// ** Unit-Param-Bar
		if (W_UnitParamBar_class)
		{
			UnitParamBar = GetWorld()->SpawnActor<AUnitParamBar>();
			if (UnitParamBar)
				UnitParamBar->Init(this, W_UnitParamBar_class);
			else
			{
				UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ERROR:   '%s'::AUnit::Init():      Widget Bar = 'W3dBar_UnitParam_class'   not Set"), *GetName());
				UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, true);
			}
		}

		// ** Add default items to MainInventor
		//++++ for(int32 i = 0; i < InitInvertorItems.Num(); ++i)
		//++++	TryAddItemToMainInventory(nullptr, -1, InitInvertorItems[i]);
		

		// +++  ** Bind to delegate for End-Animation-EVENT   (ABaseUnit::    FOnMontageEnded OnAnimationFinish;)
		// +++ FinishAnimationDELEGATE.BindUObject(AIController, &AUnitAI::OnAnimationFinish);
	}

	return  isAllComponentInited;
}


void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



// **  ************************************************************************
// **  ************************     AI_Controller     ************************* 
// **  ************************************************************************ 


void AUnit::SetUnitTask(bool _bAddMoreOne, ETaskType _TaskType, 
	FTaskData _TaskData, ETaskCauser _TaskCauser, ETaskPriority _TaskPriority)
{
	AI->SetTask(_bAddMoreOne, _TaskType, _TaskData, _TaskCauser, _TaskPriority);
}



// **  ************************************************************************
// **  ***************************       HUD       **************************** 
// **  ************************************************************************ 


void AUnit::UpdateTaskQueuePanel_HUD()
{
	if (GetIsUnitSelected() && !IsUnitInGroup())
	{
		UTexture2D* CurrTaskImage = nullptr;
		TArray<UTexture2D*> TasksImage;
		TArray<int32> TasksIndex;

		AI->GetTasksQueDataFromAI(CurrTaskImage, TasksImage, TasksIndex);

		HUD->UpdateTaskQueuePanel(this, CurrTaskImage, TasksImage, TasksIndex);
	}
}



void AUnit::UpdateAttacksWpnPanel_HUD()
{
	if (GetIsUnitSelected() && !IsUnitInGroup())
	{
		TArray<UTexture2D*> attackImage;
		int32 selectIndex;
		int32 permanentIndex;
		WeaponComponent->GetSelectedWeaponAttacksData(attackImage,
			selectIndex, permanentIndex);

		HUD->UpdateAttacksWpnPanel(this, attackImage, selectIndex, permanentIndex);
	}
}


void AUnit::UpdateParameterPanel_HUD()
{
	if (GetIsUnitSelected() && 
		!IsUnitInGroup())
		HUD->UpdateParameterPanel(this);
}


void AUnit::UpdateFastPanel_HUD()
{
	if (GetIsUnitSelected() &&
		!IsUnitInGroup())
		HUD->ShowFastPanel(this);
}

// **  ************************************************************************
// **  ************************     PERCEPTION     ************************* 
// **  ************************************************************************

void AUnit::TargetPerceptionUpdated(AActor* _ActorActivator, FAIStimulus _Stimulus)
{
	if (!AI)
		return;

	if (_Stimulus.Type.Name == FName("Default__AISense_Sight"))
	{
		//++++++++AI->UpdateLogic();
	}
	/*
	else if (_Stimulus.Type.Name == FName("Default__AISense_Damage"))
	{
		// ** UE_LOG(LogTemp, Error, TEXT("---Unit DAMAGED---"));

		// +++++++++  SetTask()   // ** PlayAnimation

	}
	*/
	else if (_Stimulus.Type.Name == FName("Default__AISense_Hearing"))
	{
		// ** UE_LOG(LogTemp, Error, TEXT("---Unit REMEMBERING (Hearing)---"));
		//+++++++AI->UpdateLogic();
	}
}

/*
void AUnit::NoticeSelfDamageAsPerception(float _DamageAmount, struct FDamageEvent const& _DamageEvent, AController* _Instigator, AActor* _ActorCauser)
{

	UAIPerceptionSystem* PerceptionSystem = UAIPerceptionSystem::GetCurrent(GetPawn());
	if (PerceptionSystem)
	{
		// ** #include "Perception/AISense_Damage.h"
		FAIDamageEvent Event(GetPawn(), _ActorCauser, _DamageAmount, _ActorCauser->GetActorLocation(), GetPawn()->GetActorLocation());
		PerceptionSystem->OnEvent(Event);
	}
}
*/



// **  ************************************************************************
// **  ************************     AnimInstance     ************************ 
// **  ************************************************************************


void AUnit::SetWeaponAnimType(EWeaponType _NewWeaponAnim)
{
	AnimInstance->SetWeaponAnimType(_NewWeaponAnim);
}

void  AUnit::UpdateRotateAnimSpeedHandler(TArray<FPoseLocomotion>* _ActualPosesArray)
{
	if (!_ActualPosesArray)
		GetActualPoseLocomotion(*_ActualPosesArray);

	TArray<float> RotateSpeedSwetcher;

	for (uint8 i = uint8(EUnitPose::Fly); i >= uint8(EUnitPose::Crawl); --i)
	{
		RotateSpeedSwetcher.Add(9999.f);	// ** Extra-MAX  --- it mean thet Pose is absent

		for (int32 n = 0; n < _ActualPosesArray->Num(); ++n)
		{
			if ((*_ActualPosesArray)[n].Pose == EUnitPose(i))
			{
				RotateSpeedSwetcher.Last() = (*_ActualPosesArray)[n].RotateSpeed;
				break;
			}
		}
	}
	AnimInstance->SetRotateSpeedHandle(RotateSpeedSwetcher);
}


void AUnit::PlayAnimate(UAnimMontage* _AnimMontage, bool _isPlayTOP, float _fromTime)
{
	AnimInstance->CurrentMontage = _AnimMontage;
	AnimInstance->IsPlayTOP = _isPlayTOP;
	AnimInstance->MontageStartTime = _fromTime;

	AnimInstance->Montage_Play(_AnimMontage, 1.f, EMontagePlayReturnType::MontageLength, _fromTime);
	AnimInstance->Montage_SetEndDelegate(FinishAnimationDELEGATE, _AnimMontage);
}

void AUnit::StopAnimate()
{
	StopAnimMontage(GetCurrentMontage());
}

void AUnit::OnAnimNotify(FString _NotifyName)
{
	AI->OnAnimNotify(_NotifyName);
}


// **  ********************************************************************************
// **  **********************       Unit_Parameter_Getters       ********************** 
// **  ********************************************************************************


FTransform AUnit::GetUnitSocketParam(FName _SocketName)
{
	return GetMesh()->GetSocketTransform(_SocketName, ERelativeTransformSpace::RTS_World);
}


float AUnit::GetUnitCapsuleRadius()
{
	float capsuleRadius;
	float capsuleHalfHaight;
	GetCapsuleComponent()->GetScaledCapsuleSize(capsuleRadius, capsuleHalfHaight);
	return capsuleRadius;
}

float AUnit::GetUnitCapsuleHalfHaight()
{
	float capsuleRadius;
	float capsuleHalfHaight;
	GetCapsuleComponent()->GetScaledCapsuleSize(capsuleRadius, capsuleHalfHaight);
	return capsuleHalfHaight;
}



// **  ********************************************************************************
// **  **************************     Unit_Main_Function     ************************** 
// **  ********************************************************************************



void AUnit::SelectUnit()
{
	IsUnitSelected = true;

	if (!IsUnitInGroup())
	{
		int32 weaponSlotIndex;
		ESlotType weaponSlotType;
		UTexture2D* weaponSlotTexture;

		if (!WeaponComponent->GetCurrentWeaponSlotData(weaponSlotIndex,
			weaponSlotType, weaponSlotTexture))
		{
			weaponSlotIndex = -1;
		}

		HUD->ShowWpnChangePanel(this, weaponSlotIndex,
			weaponSlotType, weaponSlotTexture);

		if (HUD->IsEquipPanelShown)
			HUD->ShowEquipPanel(this);	// ** update

		HUD->ShowFastPanel(this);	// ** update


		if (CurrUnitEffectSlots.Num() > 0)
			HUD->ShowUnitEffectPanel(this);


		HUD->ShowParameterPanel(this);

	}

	UpdateTaskQueuePanel_HUD();

	TArray<UTexture2D*> attackImage;
	int32 selectIndex;
	int32 permanentIndex;
	WeaponComponent->GetSelectedWeaponAttacksData(attackImage,
		selectIndex, permanentIndex);
	HUD->ShowAttacksWpnPanel(this, attackImage, selectIndex, permanentIndex);

	// @@@@@ ...
	// @@@@@ ...
	// @@@@@ ...
}

void AUnit::DeselectUnit()
{
	IsUnitSelected = false;

	if(!IsUnitInGroup())
		HUD->HideWpnChangePanel(this);

	UpdateTaskQueuePanel_HUD();

	HUD->HideAttacksWpnPanel();
	HUD->HideFastPanel();

	// ** Deselect all Selected on Fast-Panem
	//--------GameMode->ActivateFastPanelBtnInSpectator(-1);



	if (GameState->GetCountOfSelectUnits() == 1 && 
		GameState->GetSelectedUnit(0)->CurrUnitEffectSlots.Num() > 0)
		HUD->ShowUnitEffectPanel(this);
	else
		HUD->HideUnitEffectPanel();


	HideNavPathMarkers();


	HUD->HideParameterPanel();

	// @@@@@ ...
	// @@@@@ ...
	// @@@@@ ...
}

bool AUnit::GetIsUnitSelected()
{
	return IsUnitSelected;
}

bool AUnit::IsUnitInGroup()
{
	return (GameState->GetCountOfSelectUnits() > 1);
}


void AUnit::SetUnitMouseFocused(bool _IsSet)
{
	IsUnitMouseFocused = _IsSet;
}

bool AUnit::GetIsUnitMouseFocused() const
{
	return IsUnitMouseFocused;
}




/*
void AUnit::SetCommandData_Unit(AUnit* _TargetUnit, bool _IsShiftPresed)
{
	// ** Is has Select-Weapon-Attack
	if (true)
	{

	}
	// ** Is has Permanent-Weapon-Attack
	else if (true)
	{

	}
}

void AUnit::SetCommandData_Location(bool _IsShiftPresed)
{

}
*/



bool AUnit::GenerateNavPath(bool _IsDrawPath, bool _UseSpecialPoint, FVector _GoalPoint)
{
	return AI->GenerateNavPath(_IsDrawPath, _UseSpecialPoint, _GoalPoint);
}


bool AUnit::IsNavPathGenerate()
{
	return AI->IsNavPathGenerate();
}

void AUnit::HideNavPathMarkers()
{
	AI->HideNavPathMarkers();
}





// **  ************************************************************************
// **  *************************     Unit_Effect     *************************** 
// **  ************************************************************************


void AUnit::AddUnitEffect(FUnitEffectDT* _UnitEffect)
{
	if (!_UnitEffect)
		return;


	FUnitEffectSlotDT newUnitEffectSlotDT;
	newUnitEffectSlotDT.CastSlotEffectFromUnitEffect(*_UnitEffect);

	bool isHoldingEffect = newUnitEffectSlotDT.Init(this);
	if (isHoldingEffect)
	{
		CurrUnitEffectSlots.Add(newUnitEffectSlotDT);
		CurrUnitEffectSlots.Last().IndexInUnit = CurrUnitEffectSlots.Num() - 1;
		
		// ** Redraw HUD-Element
		if (IsUnitSelected && !IsUnitInGroup())
		{
			if (CurrUnitEffectSlots.Num() > 0)
				HUD->ShowUnitEffectPanel(this);
		}

		// ** Effect Loop
		if (!GetWorld()->GetTimerManager().IsTimerActive(TH_UpdateUnitEffect))
		{
			GetWorld()->GetTimerManager().SetTimer(TH_UpdateUnitEffect, this, 
				&ThisClass::UpdateUnitEffect, GameMode->RoundTime, false);
		}


		// ------------------------- TEST -------------------------------
		DrawDebugSphere
		(
			GetWorld(),
			GetActorLocation(),
			30,
			12,
			FColor::Red,
			false,
			1.0f,
			10,
			10.f
		);
		// ------------------------- TEST -------------------------------
	};




/*
	FUnitEffectDT newUnitEffect = *_UnitEffect;

	bool isHoldingEffect = newUnitEffect.Init(this);

	if (isHoldingEffect)
	{
		CurrUnitEffects.Add(newUnitEffect);
		CurrUnitEffects.Last().IndexInUnit = CurrUnitEffects.Num() - 1;
		CurrUnitEffects.Last().ActivateUpdate();
	}
*/





	// ** Niagara visual effect
	/*
	int32 socketNum = _UnitEffect->VisualEffectSocket.Num(); 

	for (int32 i = 0; i < _UnitEffect->VisualEffect.Num(); ++i)
	{
		if (_UnitEffect->VisualEffect[i])
		{
			FName socketName = _UnitEffect->VisualEffectSocket[i];
			if(i >= socketNum)
				socketName = NAME_None;

			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
				_UnitEffect->VisualEffect[0],
				GetCapsuleComponent(),
				socketName,		// ** NAME_None,
				FVector(0.f),
				FRotator(0.f),
				EAttachLocation::Type::KeepRelativeOffset,
				true);
		}
	}
	*/
}

void AUnit::UpdateUnitEffect()
{
	for (int32 i = CurrUnitEffectSlots.Num()-1; i >= 0; --i)
	{
		CurrUnitEffectSlots[i].Continue(this);

		// ------------------------- TEST -------------------------------
		DrawDebugSphere
		(
			GetWorld(),
			GetActorLocation(),
			30,
			12,
			FColor::Red,
			false,
			1.0f,
			10,
			10.f
		);
		// ------------------------- TEST -------------------------------
	}

	// ** Redraw HUD-Element
	if (IsUnitSelected && !IsUnitInGroup())
	{
		HUD->ShowUnitEffectPanel(this);
	}
	else if (GetIsUnitMouseFocused())
	{
		HUD->ShowTargetEffectPanel(this);
	}

	// ** Effect Loop
	if (CurrUnitEffectSlots.Num() > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(TH_UpdateUnitEffect, this,
			&ThisClass::UpdateUnitEffect, GameMode->RoundTime, false);
	}
}

void AUnit::BreakUnitEffect(int32 _Index, bool _IsForseBreak)
{
	if (_Index < 0 || _Index >= CurrUnitEffectSlots.Num())
		return;

	if (_IsForseBreak)
	{
		CurrUnitEffectSlots[_Index].Finish();
		return;
	}

	if (CurrUnitEffectSlots[_Index].IsUnitEffectCanBeCanel)
	{
		CurrUnitEffectSlots[_Index].Finish();
	}
}

void AUnit::RermoveUnitEffect(FUnitEffectSlotDT& _UnitEffect)
{
	
	int32 currIndex = _UnitEffect.IndexInUnit;

	CurrUnitEffectSlots.RemoveAt(_UnitEffect.IndexInUnit);

	for (int32 i = currIndex; i < CurrUnitEffectSlots.Num(); ++i)
	{
		CurrUnitEffectSlots[i].IndexInUnit -= 1;
	}

	// ** Redraw HUD-Element
	if (IsUnitSelected && !IsUnitInGroup())
	{
		if (CurrUnitEffectSlots.Num() >= 0)
			HUD->ShowUnitEffectPanel(this);
	}
}

	



// **  ************************************************************************
// **  *************************     Unit_State     *************************** 
// **  ************************************************************************


float AUnit::GetParam(EUnitParam _Param)
{
	return UnitParam->GetParam(_Param);
}

void AUnit::SetParam(EUnitParam _Param, float _Val)
{
	UnitParam->SetParam(_Param, _Val);

	UpdateParameterPanel_HUD();
}

void AUnit::ModParam(EUnitParam _Param, float _Val)
{
	UnitParam->ModParam(_Param, _Val);

	UpdateParameterPanel_HUD();
}

void AUnit::ModParamModificator(EUnitParam _Param, float _Val)
{
	UnitParam->ModParamModificator(_Param, _Val);

	UpdateParameterPanel_HUD();
}













int32 AUnit::GetLevel() const {	return -1; }
void AUnit::SetLevel(int32 _Val) { }
void AUnit::ModLevel(int32 _Val)
{

}








int32 AUnit::GetTotalWpnLevel(bool _GetBaseValue) const
{
	return -1;
}
int32 AUnit::GetTotalGunLevel(bool _GetBaseValue) const
{
	return -1;
}
int32 AUnit::GetTotalMagikLevel(bool _GetBaseValue) const
{
	return -1;
}



void AUnit::SetTotalWpnLevel(int32 _Val, bool _GetBaseValue)
{

}
void AUnit::SetTotalGunLevel(int32 _Val, bool _GetBaseValue)
{

}
void AUnit::SetTotalMagikLevel(int32 _Val, bool _GetBaseValue)
{

}


void AUnit::ModCurrentHP(int32 _Val)
{

}
void AUnit::ModCriticalHP(int32 _Val)
{

}
void AUnit::ModMinHP(int32 _Val)
{

}
void AUnit::ModHP(int32 _Val)
{

}
void AUnit::ModTotalWpnLevel(int32 _Val)
{

}
void AUnit::ModTotalGunLevel(int32 _Val)
{

}
void AUnit::ModTotalMagikLevel(int32 _Val)
{

}


// **  ************************************************************************
// **  *************************     Skill_Depend     ************************* 
// **  ************************************************************************

int32 AUnit::GetSkillDepend_FirstAttackSeries() const
{
	// ** TEST
	return 5;   // ** Level + CurrWeaponLevel  
}




// **  ************************************************************************
// **  ***************************     Fraction     *************************** 
// **  ************************************************************************


// .....
// .....
// .....



// **  ************************************************************************
// **  **************************     Inventory     *************************** 
// **  ************************************************************************



bool AUnit::TryAddItemToMainInventory(FItemDT* ItemDT, int32 ToSlotIndex, 
							TSubclassOf<AWorldItem> WorldItem, bool ForseAdd)
{
	return Inventory->TryAddItemToMainInventory(ItemDT, ToSlotIndex, WorldItem, ForseAdd);
}

bool AUnit::IsMainInventorySlotEmpty(int32 SlotIndex)
{
	return Inventory->IsMainInventorySlotEmpty(SlotIndex);
}

FItemDT* AUnit::GetItemRefFromMainInventory(int32 SlotIndex)
{
	return Inventory->GetItemRefFromMainInventory(SlotIndex);
}

void AUnit::RemoveItemFromMainInventory(int32 SlotIndex)
{
	Inventory->RemoveItemFromMainInventory(SlotIndex);
}






int32 AUnit::GetMainInvCollNum() const
{
	return GameMode->MainInvCollNum; 
};
int32 AUnit::GetMainInvRowNum() const
{
	return GameMode->MainInvRowNum;
};
float AUnit::MainInventorSlotSize() const
{
	return GameMode->MainInventorSlotSize;
};


// **  ************************************************************************
// **  **********************     Global_Inventory     ************************ 
// **  ************************************************************************

void AUnit::AddItemToGlobalInventory(FItemDT* ItemDT, int32 ToSlotIndex) 
{
	Inventory->AddItemToGlobalInventory(ItemDT, ToSlotIndex);
}

bool AUnit::IsGlobalInventorySlotEmpty(int32 SlotIndex)
{
	return Inventory->IsGlobalInventorySlotEmpty(SlotIndex);
}

FItemDT* AUnit::GetItemRefFromGlobalInventory(int32 SlotIndex)
{
	return Inventory->GetItemRefFromGlobalInventory(SlotIndex);
}

void AUnit::RemoveItemFromGlobalInventory(int32 SlotIndex)
{
	Inventory->RemoveItemFromGlobalInventory(SlotIndex);
}


// **  ************************************************************************
// **  *************************     Fast_Panel     *************************** 
// **  ************************************************************************


void AUnit::InitFastPanel()
{
	int32 fastPanelSlotMaxNum = GameMode->FastPanelSlotNum;
	FastPanelSlots.Init(FFastPanelSlot(), fastPanelSlotMaxNum);
}


bool AUnit::SetItemToFastPanel(FItemDT* ItemDT, int32 ToSlotIndex)
{
	if (ToSlotIndex < 0 || ToSlotIndex >= FastPanelSlots.Num())
		return false;

	// ** Stack
	if (
		FastPanelSlots[ToSlotIndex].IndexInContainer != -1  &&
		FastPanelSlots[ToSlotIndex].AbilityName == FName("none") &&
		ItemDT->IsItemStackable())
	{
		FItemDT* UnderItemDT = FastPanelItem.Find(FastPanelSlots[ToSlotIndex].IndexInContainer);
		if (UnderItemDT)
			if (*ItemDT == *UnderItemDT)
			{
				int32 FreeGapeToAddStack = UnderItemDT->CountMax - UnderItemDT->Count;
				if (FreeGapeToAddStack > 0)
				{
					// ** Add to stack (contain full)
					if (ItemDT->Count <= FreeGapeToAddStack)
					{
						UnderItemDT->Count += ItemDT->Count;
						return true;
					}
					// ** Add part of skact (Has a rest)
					else
					{
						UnderItemDT->Count = UnderItemDT->CountMax;
						ItemDT->Count -= FreeGapeToAddStack;
						return false; 
					}
				}
			}
	}

	FastPanelSlots[ToSlotIndex].AbilityName == FName("none");
	FastPanelSlots[ToSlotIndex].IndexInContainer = ToSlotIndex;

	FastPanelItem.Add(ToSlotIndex, *ItemDT);
	return true;
}



bool AUnit::SetAbilityToFastPanelByIndex(int32 _AbilityIndex, int32 _ToSlotIndex)
{
	if (_ToSlotIndex >= FastPanelSlots.Num())
		return false;
	if (_AbilityIndex < 0 && _AbilityIndex >= Ability->UnitAbilityList.Num())
		return false;

	if (_ToSlotIndex == -1)
	{
		for (int32 i = 0; i < FastPanelSlots.Num(); ++i)
		{
			if (FastPanelSlots[i].IndexInContainer == -1)
			{
				_ToSlotIndex = i;
				break;
			}
		}
	}
	if (_ToSlotIndex == -1)
		return false;

	FName abilityName = Ability->GetAbilityNameByIndex(_AbilityIndex);;
	if (abilityName != FName("none"))
	{
		FastPanelSlots[_ToSlotIndex].AbilityName = abilityName;
		FastPanelSlots[_ToSlotIndex].IndexInContainer = _AbilityIndex;
		return true;
	}
	return false;
}

/* ----777------
bool AUnit::SetAbilityToFastPanelByName(FName _AbilityName, int32 _ToSlotIndex)
{
	// ** if (_ToSlotIndex < 0 || _ToSlotIndex >= FastPanelSlots.Num())
	if (_ToSlotIndex >= FastPanelSlots.Num())
		return false;

	// ** Find ability in AbilityComponent
	int32 abilityIndex = Ability->GetAbilityIndexByName(_AbilityName);
	if (abilityIndex != -1)
	{
		return SetAbilityToFastPanelByIndex(abilityIndex, _ToSlotIndex);
	}
	return false;
}
*/

// ** return "false" if slot empty 
bool AUnit::GetFastPanelSlotElement(int32 Index, FItemDT*& _ItemDTRed, UAbilityDT*& _AbilityRef_CDO) 
{
	bool isNotEmpty = false;

	if (Index < 0 || Index >= FastPanelSlots.Num())
		return isNotEmpty;

	if (-1 == FastPanelSlots[Index].IndexInContainer)
		return isNotEmpty;

	// ** if Ability in slot
	if (Ability && FastPanelSlots[Index].AbilityName != FName("none"))
	{
//++++++		TSubclassOf<UAbilityDT> abilitySubClass = Ability->GetAbilityClass_ByName(FastPanelSlots[Index].AbilityName);
//++++++		if (abilitySubClass)
		{
//+++++			_AbilityRef_CDO = abilitySubClass->GetDefaultObject<UAbilityDT>();
			isNotEmpty = true;
		}
	}

	// ** if Item in slot
	else
	{
		_ItemDTRed = FastPanelItem.Find(FastPanelSlots[Index].IndexInContainer);
		isNotEmpty = true;
	}

	return isNotEmpty;
}


void AUnit::RemoveElementFromFastPanel(int32 ToSlotIndex)
{

	if (ToSlotIndex < 0 || ToSlotIndex >= FastPanelSlots.Num())
		return;

	if (-1 == FastPanelSlots[ToSlotIndex].IndexInContainer)
		return;
/*
	// ** if Ability in slot
	if (FastPanelSlots[ToSlotIndex].AbilityType != EAbilityType::none)
	{
		FastPanelSlots[ToSlotIndex].AbilityType = EAbilityType::none;
		FastPanelSlots[ToSlotIndex].IndexInContainer = -1;
		return;
	}
*/
	// ** if Item in slot
	FItemDT* itemDT_inMap = FastPanelItem.Find(FastPanelSlots[ToSlotIndex].IndexInContainer);
	if (itemDT_inMap )
	{
		FastPanelItem.Remove(FastPanelSlots[ToSlotIndex].IndexInContainer);
		FastPanelSlots[ToSlotIndex].IndexInContainer = -1;
	}

}



void AUnit::ActivateFastPanelAbilBtn(ESlotType _ContainerType, int32 _ContainerSlotIndex, bool isLongClick)
{
	AI->ForseUpdateHolding();
	SetHoldingAbilityState(_ContainerType, _ContainerSlotIndex, isLongClick);
	

	if (_ContainerType == ESlotType::Perk_panel)
	{
		HUD->ShowPerkPanel(this);
		HUD->ShowFastPanel(this);
	}
	else if (_ContainerType == ESlotType::fast_panel)
	{
		HUD->ShowFastPanel(this);
		if (HUD->IsPerkPanelShown)
			HUD->ShowPerkPanel(this);
		//(-------777777-------)
		//if (isLongClick)
		//	HUD->SelectFastPanelSlot(_ContainerSlotIndex, true);
		//else
		//	HUD->SelectFastPanelSlot(_ContainerSlotIndex, false);
	}
}

bool AUnit::SetHoldingAbilityState(ESlotType _ContainerType, int32 _ContainerSlotIndex, bool isLongClick)
{
	// ** if (_ContainerSlotIndex < 0)  // ** Deactivate after Cast
	// **	return false;

	bool isActivate = false;
	UAbilityDT* abilityRef = nullptr;
	ESlotType slotType = ESlotType::none;

	int32 abilityIndex = -1;
	bool isAbilityItem = false;

	switch (_ContainerType)
	{

		// ** if Activate ability in Perk-Panel  (AbilityList)
	case ESlotType::Perk_panel:

		if (_ContainerSlotIndex >= Ability->UnitAbilityList.Num())
			return false;

		abilityIndex = _ContainerSlotIndex;
		Ability->GetUnitAbilityByIndex(abilityIndex, abilityRef);

		slotType = ESlotType::Perk_panel;

		break;


		// ** if Activate ability in Fast-Panel  (AbilityList or Item)
	case ESlotType::fast_panel:

		if (_ContainerSlotIndex >= FastPanelSlots.Num())
			return false;

		abilityIndex = FastPanelSlots[_ContainerSlotIndex].IndexInContainer;

		// ** if FastSlot free
		if (abilityIndex == -1)
			return false;

		// ** ability from AbilityComponent
		else if (FastPanelSlots[_ContainerSlotIndex].AbilityName != FName("none"))
		{
			Ability->GetUnitAbilityByIndex(abilityIndex, abilityRef);
			isAbilityItem = false;
		}
		// ** ITEM-Ability
		else  
		{
			isAbilityItem = true;
			//.....@@@@@@@@@@@  GetAbility from Item
		}

		slotType = ESlotType::fast_panel;
		break;

	// ** case ESlotType::none:

		// ** slotType = ESlotType::none;
		// ** abilityRef = nullptr;
		// ** _ContainerSlotIndex = -1;
	}


	// ** Set to AI->UseAbility 
	if (isLongClick)
		SetPermanentHoldingAbility(_ContainerSlotIndex, slotType, abilityRef);
	else
		SetInstantHoldingAbility(_ContainerSlotIndex, slotType, abilityRef);


	// ** target is self
	if (abilityRef && abilityRef->DefaultTargetType == ETargetType::Self)
	{
		
		if (isLongClick)
		{
			SetHoldingAbilityState(ESlotType::none, -1, false);
			//---SetPermanentHoldingAbility(_ContainerSlotIndex, slotType, abilityRef);
		}
		else
		{
			TArray<AUnit*> unitTarget;	// ** Self
			unitTarget.Add(this);

			FTaskData abilityTaskData;
			UTUseAbility::SetTaskData_UseAbilityToUnit(abilityTaskData,
				this, abilityIndex, isAbilityItem, unitTarget);

			SetUnitTask(false, ETaskType::UseAbility, abilityTaskData);
			return false;
		}

	}





	AI->UpdateLogic();

	UpdateFastPanel_HUD();

	return false;
}

void AUnit::SetPermanentHoldingAbility(int32 _NewIndex, ESlotType _NewContainerType, UAbilityDT*& _AbilityRef)
{
	UAbilityDT* abilityRef = nullptr;

	if (_NewContainerType == ESlotType::none || 
		(ContainerOfHoldingPermanent == _NewContainerType &&
		PermanentHoldingAbility == _NewIndex))
	{
		SetFastPanelButtonSelection(PermanentHoldingAbility, -1, ContainerOfHoldingPermanent, ESlotType::none);
	}
	else
	{
		SetFastPanelButtonSelection(PermanentHoldingAbility, _NewIndex, ContainerOfHoldingPermanent, _NewContainerType);
		abilityRef = _AbilityRef;
	}
	AI->SetPermanentAbilityHolding(abilityRef);
}

void AUnit::SetInstantHoldingAbility(int32 _NewIndex, ESlotType _NewContainerType, UAbilityDT*& _AbilityRef)
{
	UAbilityDT* abilityRef = nullptr;

	if (_NewContainerType == ESlotType::none ||
		(ContainerOfHoldingInstance == _NewContainerType &&	
		InstantHoldingAbility == _NewIndex))
	{
		SetFastPanelButtonSelection(InstantHoldingAbility, -1, ContainerOfHoldingInstance, ESlotType::none);
	}
	else
	{
		SetFastPanelButtonSelection(InstantHoldingAbility, _NewIndex, ContainerOfHoldingInstance, _NewContainerType);
		abilityRef = _AbilityRef;
	}
	AI->SetInstantAbilityHolding(abilityRef);
}

void AUnit::SetFastPanelButtonSelection(int32& _SelectionType, int32 _SelectionTypeVal,
	ESlotType& _ContainerType, ESlotType _ContainerTypeVal)
{
	_SelectionType = _SelectionTypeVal;
	_ContainerType = _ContainerTypeVal;
}

int32 AUnit::GetPermanentHoldingAbility()
{
	return PermanentHoldingAbility;
}

int32 AUnit::GetInstantHoldingAbility()
{
	return InstantHoldingAbility;
}




bool AUnit::IsItemInFastPanelSlot(int32 _Index)
{
	if (_Index >= 0 && _Index < FastPanelSlots.Num())
	{
		return (FastPanelSlots[_Index].AbilityName == FName("none"));
	}
	return false;  // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   7777777  if slot Empty
}
/*
FName AUnit::GetAbilityNameFromFastSlotIx(int32 _SlotIndex)
{
	if (_SlotIndex < 0 || _SlotIndex >= FastPanelSlots.Num())
		return FName("none");

	if (FastPanelSlots[_SlotIndex].AbilityName != FName("none"))
		return FastPanelSlots[_SlotIndex].AbilityName;

	return FName("none");
}
*/

// **  ************************************************************************
// **  ***************************     Ability     **************************** 
// **  ************************************************************************



// @@@@@@@@@@@@@@@@@@@@  Ability
// @@@@@@@@@@@@@@@@@@@@  Ability
// @@@@@@@@@@@@@@@@@@@@  Ability
/*
void AUnit::AddAbilityByName(FName _AbilityName)
{
	Ability->AddAbilityByName(_AbilityName); 
}
*/


void AUnit::AddAbilityByClass(TSubclassOf<UAbilityDT>& _AbilityDTClass)
{
	Ability->AddAbilityByClass(_AbilityDTClass);
}

void AUnit::RemoveAbilityByClass(TSubclassOf<UAbilityDT>& _AbilityDTClass)
{
	//+++++int32 deletedAbilityIndex = Ability->RemoveAbilityByClass(_AbilityDTClass);
	
	//+++++if (deletedAbilityIndex == -1)
		return;

	//++++++++++++++++++++++++++++
	{
		// ** @@@@@@@@   UPDATE FASRT-Panel
		// **  All indexes (--)
		// ** for (if FstPanel->Name != "none" && i >) 
		// **	if(FstPanel->Index == deletedAbilityIndex) =>  Remove from FastPanel
		// **   else if(FstPanel->Index > deletedAbilityIndex) => (--FstPanel->Index)
	}
}

ETargetType AUnit::GetAbilityTargetType(int32 _iFastPanelAbility, int32& _TargetsCount)
{
	if (_iFastPanelAbility < 0 ||
		_iFastPanelAbility >= FastPanelSlots.Num())
		return ETargetType::Self;

	// ** if Ability in slot
	if(FastPanelSlots[_iFastPanelAbility].AbilityName != FName("none"))
		return Ability->GetAbilityTargetType(
			FastPanelSlots[_iFastPanelAbility].IndexInContainer, _TargetsCount);
	//++++ else
	//++++		Get Ability Data ftom Item-Ability:  (ETargetType, _TargetsCount)


	return ETargetType::Self;
}




//bool AUnit::IsHasHoldingAbility()
bool AUnit::IsHasPermanentHoldAbility()
{
	return //-----ContainerOfHoldingInstance != ESlotType::none ||
		ContainerOfHoldingPermanent != ESlotType::none;
}

bool AUnit::IsHasInstantHoldAbility()
{
	return ContainerOfHoldingInstance != ESlotType::none;
}



/*-------------------
bool AUnit::GetHoldingPoseData(ESlotType _ContainerType, int32 &_HoldingPoseStep, 
								FAbilityStep*& _PreAbilityPoseStep)
{
	if (_HoldingPoseStep < 0)
		return false;


	if (_ContainerType == ESlotType::main_inv)
	{
		//..........................
		//..........................
		//..........................
	}
	else if (_ContainerType == ESlotType::Global_inv)
	{
		//..........................
		//..........................
		//..........................
	}
	else if (_ContainerType == ESlotType::Ability)
	{
		//..........................
		//..........................
		//..........................
	}
	else if (_ContainerType == ESlotType::Perk_panel)
	{
		UAbilityDT* _AbilityRef = nullptr;

		int32 indexInContainer = -1;
		if (InstantHoldingAbility != -1)
		{
			indexInContainer = InstantHoldingAbility;
		}
		else if(PermanentHoldingAbility != -1)
		{
			indexInContainer = PermanentHoldingAbility;
		}






		if (indexInContainer != -1 && Ability->GetUnitAbilityByIndex(indexInContainer, _AbilityRef))
		{
			if (Ability->GetPreAbilityHoldingPose(_AbilityRef, _HoldingPoseStep, _PreAbilityPoseStep))
				return true;
		}
	}
	return false;
}
*/


// **  ************************************************************************
// **  **********************     Weapon_Component     ************************ 
// **  **********************        Equip_Panel       ************************ 
// **  ************************************************************************ 


int32 AUnit::IsWeaponActive()
{
	return WeaponComponent->IsWeaponActive();
}

bool AUnit::ActivateWeapon()
{
	bool isSucces = WeaponComponent->ActivateWeapon();
	if (isSucces)
	{
		TArray<FPoseLocomotion> actualPoseLocomotion;
		GetActualPoseLocomotion(actualPoseLocomotion);
		// ** Speed By Pose (depend Weapon speed-mod)
		SetMoveSpeed(GetMoveSpeedFromPose(CurrUnitPose, &actualPoseLocomotion));
		// ** Rotate switcher (depend Weapon speed-mod)
		UpdateRotateAnimSpeedHandler(&actualPoseLocomotion);
	}
	return isSucces;
}
bool AUnit::UnactivateWeapon()
{
	bool isSucces = WeaponComponent->UnactivateWeapon();
	if (isSucces)
	{
		TArray<FPoseLocomotion> actualPoseLocomotion;
		GetActualPoseLocomotion(actualPoseLocomotion);
		// ** Speed By Pose (depend Weapon speed-mod)
		SetMoveSpeed(GetMoveSpeedFromPose(CurrUnitPose, &actualPoseLocomotion));
		// ** Rotate switcher (depend Weapon speed-mod)
		UpdateRotateAnimSpeedHandler(&actualPoseLocomotion);
	}
	return isSucces;
}

AWeaponWorldItem* AUnit::GetCurrWeaponItem()
{
	return WeaponComponent->GetCurrWeaponItem();
}

EWeaponType AUnit::GetCurrentWeaponType()
{
	return WeaponComponent->GetCurrentWeaponType();
}


bool AUnit::EquipAmunitionByItemDT(const FItemDT* _ItemDT)
{
	bool isOk = false;

	if(_ItemDT->IsItemWeapon())
		isOk = WeaponComponent->EquipWeaponByItemDT(_ItemDT);

	else // ** if(_ItemDT->IsItemArmor())
		isOk = ArmorComponent->EquipArmorByItemDT(_ItemDT);

	if (GetIsUnitSelected() && !IsUnitInGroup())
	{
		if (HUD->IsEquipPanelShown)
			HUD->ShowEquipPanel(this);	// ** update
		if (HUD->IsWpnChangePanelOpened)
			OpenChangeWeaponPanel();	// ** update
	}
	return isOk;
}

bool AUnit::SetWeaponSlotSelected(int32 _WeaponSlotIndex)
{
	bool isSucces = false;

	// ** Select other weapon (dont activate, only change index)
	if (!WeaponComponent->IsWeaponActive())
	{
		isSucces = WeaponComponent->SetWeaponSlotSelected(_WeaponSlotIndex);
	}

	// ** if unit activate weapon => Use task "Change weapon"
	else
	{
		FTaskData newTask;
		/// ** UTActivateWeapon::SetActivateWeaponTaskData_ChangeWpn(newTask, this, _WeaponSlotIndex);
		newTask.Int32Param.Add(_WeaponSlotIndex);
		
		SetUnitTask(false, // ** NO_MATTAER
			ETaskType::ActivateWeapon,
			newTask,
			ETaskCauser::CriticalTask,
			ETaskPriority::Normal);
	}
	

	if (GetIsUnitSelected() && !IsUnitInGroup())
	{
		// ** update EquipPane
		if (HUD->IsEquipPanelShown)
			HUD->ShowEquipPanel(this);	

		// ** update ShowWpn-ChangePanel-Title-icon
		{
			int32 weaponSlotIndex; 
			ESlotType weaponSlotType;
			UTexture2D* weaponSlotTexture;
			if (!WeaponComponent->GetCurrentWeaponSlotData(
				weaponSlotIndex,
				weaponSlotType, 
				weaponSlotTexture))
			{
				weaponSlotIndex = -1;
			}
			HUD->ShowWpnChangePanel(this, weaponSlotIndex,
				weaponSlotType, weaponSlotTexture);		


			HUD->CloseChangeWeaponPanel();
		}
	}
	return isSucces;
}


int32 AUnit::GetSelectedWeaponSlotIndex()
{
	return WeaponComponent->GetSelectedWeaponSlotIndex();
}

EWeaponType AUnit::GetWeaponTypeBySlotIndex(int32 _SlotIndex) const
{
	return WeaponComponent->GetWeaponTypeBySlotIndex(_SlotIndex);
}

bool AUnit::IsEquipPanelSlotEmpty(int32 SlotIndex)
{
	return WeaponComponent->IsEquipPanelSlotEmpty(SlotIndex);
}

FItemDT* AUnit::GetItemRefFromEquipPanel(int32 SlotIndex)
{
	return WeaponComponent->GetItemRefFromEquipPanel(SlotIndex);
}

void AUnit::RemoveItemFromEquipPanel(int32 SlotIndex)
{
	WeaponComponent->RemoveItemFromEquipPanel(SlotIndex);
	if (GetIsUnitSelected() && !IsUnitInGroup())
	{
		if (HUD->IsEquipPanelShown)
			HUD->ShowEquipPanel(this);	// ** update
		if (HUD->IsWpnChangePanelOpened)
			OpenChangeWeaponPanel();	// ** update
	}
}


void AUnit::OpenChangeWeaponPanel() 
{

	if (GetIsUnitSelected() && !IsUnitInGroup())
	{
		TArray<int32> weaponSlotsIndex;
		TArray<ESlotType> weaponSlotsType;
		TArray<UTexture2D*> weaponSlotsTexture;

		WeaponComponent->GetWeaponSlotsListData(weaponSlotsIndex,
			weaponSlotsType, weaponSlotsTexture);
		
		HUD->OpenChangeWeaponPanel(this, weaponSlotsIndex,
			weaponSlotsType, weaponSlotsTexture);
	}
}


// **  ************************************************************************
// **  **********************     Armor_Component      ************************ 
// **  **********************        Equip_Panel       ************************ 
// **  ************************************************************************ 


bool AUnit::EquipArmorByItemDT(const FItemDT* _ItemDT)
{
	bool isOk = ArmorComponent->EquipArmorByItemDT(_ItemDT);
	if (GetIsUnitSelected() && !IsUnitInGroup())
	{
		if (HUD->IsEquipPanelShown)
			HUD->ShowEquipPanel(this);	// ** update
	}
	return isOk;
}



// **  ************************************************************************
// **  ************************     Pose-Locomotion     ************************ 
// **  ************************************************************************

void AUnit::StopMove()
{
	GetCharacterMovement()->StopActiveMovement();
}


void AUnit::GetActualPoseLocomotion(TArray<FPoseLocomotion>& _ActualPoseLocomotion)
{
	int32 activeWpnSlot = -1;

	if (WeaponComponent &&
		(activeWpnSlot = WeaponComponent->GetSelectedWeaponSlotIndex()) != -1)
	{
		// ** link PoseLocomotion from "WeaponComponent" 
		UWeaponDT* currWeaponDT_CDO = WeaponComponent->WeaponSlot[activeWpnSlot]->
			ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();

		for (int32 i = 0; i < PoseLocomotionParam.Num(); ++i)
		{
			FPoseLocomotion defaultPoseData;
			defaultPoseData.Pose = PoseLocomotionParam[i].Pose;
			defaultPoseData.MoveSpeed = PoseLocomotionParam[i].MoveSpeed;
			defaultPoseData.RotateSpeed = PoseLocomotionParam[i].RotateSpeed;
			defaultPoseData.PoseImage = PoseLocomotionParam[i].PoseImage;

			///bool isPoseExistInWeapon = false;
			TArray<FPoseLocomotion>& dataFromWeaponRef = currWeaponDT_CDO->PoseLocomotionParamMOD;
			for (int32 n = 0; n < dataFromWeaponRef.Num(); ++n)
			{
				if (defaultPoseData.Pose == dataFromWeaponRef[n].Pose)
				{
					defaultPoseData.MoveSpeed += dataFromWeaponRef[n].MoveSpeed;
					defaultPoseData.RotateSpeed += dataFromWeaponRef[n].RotateSpeed;
					///isPoseExistInWeapon = false;
					_ActualPoseLocomotion.Add(defaultPoseData);
					break;
				}
			}
		}
		//-----return &currWeaponDT_CDO->PoseLocomotionParamMOD;
	}
	else
	{
		_ActualPoseLocomotion = PoseLocomotionParam;
	}
}


void  AUnit::SetPose(EUnitPose _UnitPose)
{

	if (CurrUnitPose != _UnitPose)
	{
		CurrUnitPose = _UnitPose;

		AnimInstance->UnitPose = _UnitPose;

		TArray<FPoseLocomotion> actualPoseLocomotion;
		GetActualPoseLocomotion(actualPoseLocomotion);
		// ** Speed By Pose (depend Weapon speed-mod)
		SetMoveSpeed(GetMoveSpeedFromPose(CurrUnitPose, &actualPoseLocomotion));
		// ** Rotate switcher (depend Weapon speed-mod)
		UpdateRotateAnimSpeedHandler(&actualPoseLocomotion);
	}
}


EUnitPose AUnit::GetCurrUnitPose() const
{
	return CurrUnitPose;
}


void AUnit::SetMoveSpeed(float _Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = _Speed;

}

void AUnit::SetMoveSpeedFromPose(EUnitPose _UnitPose, TArray<FPoseLocomotion>* _ActualPosesArray)
{
	if (!_ActualPosesArray)
		GetActualPoseLocomotion(*_ActualPosesArray);


	// ** find request pose
	for (int32 i = 0; i < _ActualPosesArray->Num(); ++i)
	{
		if (_UnitPose == (*_ActualPosesArray)[i].Pose)
		{
			SetMoveSpeed((*_ActualPosesArray)[i].MoveSpeed);
			return;
		}
	}

	// ** if not finded => Return latest pose
	if (_ActualPosesArray->Num() > 0)
		SetMoveSpeed(_ActualPosesArray->Last().MoveSpeed);

	// ** ERROR:  forgot set pose
	SetMoveSpeed(0);

}

float AUnit::GetMoveSpeedFromPose(EUnitPose _UnitPose, TArray<FPoseLocomotion>* _ActualPosesArray)
{
	if (!_ActualPosesArray)
		GetActualPoseLocomotion(*_ActualPosesArray);


	// ** find request pose
	for (int32 i = 0; i < _ActualPosesArray->Num(); ++i)
	{
		if (_UnitPose == (*_ActualPosesArray)[i].Pose)
			return  (*_ActualPosesArray)[i].MoveSpeed;
	}

	// ** if not finded => Return latest pose
	if(_ActualPosesArray->Num() > 0)
		return _ActualPosesArray->Last().MoveSpeed;

	// ** ERROR:  forgot set pose
	return 0.f;

}



void AUnit::SetRotateSpeedFromVal(float _NewSpeed)
{
	AnimInstance->SetRotateAnimSpeed(_NewSpeed);
}


float AUnit::GetRotateSpeedFromPose(EUnitPose _UnitPose)
{
	TArray<FPoseLocomotion> actualPoseLocomotion;
	GetActualPoseLocomotion(actualPoseLocomotion);

	// ** find request pose
	for (int32 i = 0; i < actualPoseLocomotion.Num(); ++i)
	{
		if (_UnitPose == actualPoseLocomotion[i].Pose)
			return actualPoseLocomotion[i].RotateSpeed;
	}

	// ** if not finded => Return latest pose
	if (actualPoseLocomotion.Num() > 0)
		return actualPoseLocomotion.Last().RotateSpeed;

	// ** ERROR:  forgot set pose
	return 0.f;
}


// **  ************************************************************************
// **  ************************     TEST_DEBUG    ************************
// **  ************************************************************************



