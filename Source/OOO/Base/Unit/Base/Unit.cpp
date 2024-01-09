
// #include "Base/Unit/Base/Unit.h"
#include "Unit.h"


#include "../../Base/BaseGameMode.h"
#include "../../Base/BaseGameState.h"
#include "../../HUD/BaseHUD.h"

#include "../../UnitState/UnitStateComponent.h"

#include "../../Controller/UnitAI.h"

#include "../../Animation/AnimInstance/HumanAnimInst.h"

#include "../../WorldObject/WayPoint/WayPoint.h"

#include "../../Controller/Task/Base/DailyBhvrQueue.h"		// ** 7777777777777777777

#include "../../Fraction/FractionSystem.h"

#include "../../Inventory/InventoryComponent.h"

#include "../../Amunition/WeaponComponent.h"
#include "../../Amunition/ArmorComponent.h"

#include "../../Ability/AbilityComponent.h"

//#include "../../Item/WorldItem.h"
#include "../../Amunition/WeaponWorldItem.h"

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



	// **  UnitState  
	UnitState = CreateDefaultSubobject<UUnitStateComponent>(TEXT("UnitState"));

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

		InitFastPanel();

		// ** Ability Component
		// -----
		// ----- @@@@@@
		// -----

		// ** Weapon Component
		WeaponComponent->InitWeapons(this);
		ArmorComponent->InitArmor(this);

		// ** Armor Component
		// ++++++++ ArmorComponent->InitArmour(this);

		SetPose(EUnitPose::RelaxMove);

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
	return (GameState->GetUnitGroupNum() > 1);
}




// **  ************************************************************************
// **  *************************     Unit_State     *************************** 
// **  ************************************************************************



int32 AUnit::GetLevel() const
{
	return -1;
}
void AUnit::SetLevel(int32 _Val)
{

}
void AUnit::ModLevel(int32 _Val)
{

}




int32 AUnit::GetCurrentHP() const
{
	return -1;
}

int32 AUnit::GetCriticalHP(bool _GetBaseValue) const
{
	return -1;
}
int32 AUnit::GetMinHP(bool _GetBaseValue) const
{
	return -1;
}
int32 AUnit::GetHP(bool _GetBaseValue) const
{
	return -1;
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



void AUnit::SetCurrentHP(int32 _Val)
{

}
void AUnit::SetCriticalHP(int32 _Val, bool _GetBaseValue)
{

}
void AUnit::SetMinHP(int32 _Val, bool _GetBaseValue)
{

}
void AUnit::SetHP(int32 _Val, bool _GetBaseValue)
{

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
		FastPanelSlots[ToSlotIndex].AbilityType == EAbilityType::none &&
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

	FastPanelSlots[ToSlotIndex].AbilityType = EAbilityType::none;
	FastPanelSlots[ToSlotIndex].IndexInContainer = ToSlotIndex;

	FastPanelItem.Add(ToSlotIndex, *ItemDT);
	return true;
}


bool AUnit::SetAbilityToFastPanel(EAbilityType _Ability, int32 ToSlotIndex)
{
	// ** if (ToSlotIndex < 0 || ToSlotIndex >= FastPanelSlots.Num())
	if (ToSlotIndex >= FastPanelSlots.Num())
		return false;

	if (ToSlotIndex == -1)
	{
		for (int32 i = 0; i < FastPanelSlots.Num(); ++i)
		{
			if (FastPanelSlots[i].IndexInContainer == -1)
			{
				ToSlotIndex = i;
				break;
			}
		}
	}
	if (ToSlotIndex == -1)
		return false;

	if (FastPanelSlots[ToSlotIndex].IndexInContainer != -1 &&
		FastPanelSlots[ToSlotIndex].AbilityType == EAbilityType::none)
		return false;


	FastPanelSlots[ToSlotIndex].AbilityType = _Ability;
	FastPanelSlots[ToSlotIndex].IndexInContainer = 999;	// ** mo matter but -1;

	return true;
}


// ** return "false" if slot empty 
bool AUnit::GetFastPanelSlotElement(int32 Index, FItemDT*& GetItemDT, EAbilityType*& GetAbilityType)
{
	bool isNotEmpty = false;

	if (Index < 0 || Index >= FastPanelSlots.Num())
		return isNotEmpty;

	if (-1 == FastPanelSlots[Index].IndexInContainer)
		return isNotEmpty;

	// ** if Ability in slot
	if (GetAbilityType && FastPanelSlots[Index].AbilityType != EAbilityType::none)
	{
		GetAbilityType = &FastPanelSlots[Index].AbilityType;
		isNotEmpty = true;
	}

	// ** if Item in slot
	GetItemDT = FastPanelItem.Find(FastPanelSlots[Index].IndexInContainer);
	isNotEmpty = true;


	return isNotEmpty;
}


void AUnit::RemoveElementFromFastPanel(int32 ToSlotIndex)
{

	if (ToSlotIndex < 0 || ToSlotIndex >= FastPanelSlots.Num())
		return;

	if (-1 == FastPanelSlots[ToSlotIndex].IndexInContainer)
		return;

	// ** if Ability in slot
	if (FastPanelSlots[ToSlotIndex].AbilityType != EAbilityType::none)
	{
		FastPanelSlots[ToSlotIndex].AbilityType = EAbilityType::none;
		FastPanelSlots[ToSlotIndex].IndexInContainer = -1;
		return;
	}

	// ** if Item in slot
	FItemDT* itemDT_inMap = FastPanelItem.Find(FastPanelSlots[ToSlotIndex].IndexInContainer);
	if (itemDT_inMap )
	{
		FastPanelItem.Remove(FastPanelSlots[ToSlotIndex].IndexInContainer);
		FastPanelSlots[ToSlotIndex].IndexInContainer = -1;
	}

}






// **  ************************************************************************
// **  ***************************     Ability     **************************** 
// **  ************************************************************************



void AUnit::AddAbility(EAbilityType _Ability)
{
	Ability->AddAbility(_Ability);
}




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



