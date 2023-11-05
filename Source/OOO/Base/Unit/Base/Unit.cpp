
// #include "Base/Unit/Base/Unit.h"
#include "Unit.h"


#include "../../Base/BaseGameMode.h"
#include "../../Base/BaseGameState.h"
#include "../../HUD/BaseHUD.h"

#include "../../Controller/UnitAI.h"

#include "../../Animation/AnimInstance/HumanAnimInst.h"

#include "../../WorldObject/WayPoint/WayPoint.h"

#include "../../Controller/Task/Base/DailyBhvrQueue.h"		// ** 7777777777777777777

#include "../../Fraction/FractionSystem.h"

#include "../../Inventory/InventoryComponent.h"

#include "../../Ability/AbilityComponent.h"

#include "../../Item/WorldItem.h"
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



	// **  Inventory   
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));


	// **  Ability   
	Ability = CreateDefaultSubobject<UAbilityComponent>(TEXT("Ability"));

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

		Inventory->Init();

		// ** Add default items
		for(int32 i = 0; i < InitInvertorItems.Num(); ++i)
			TryAddItemToInventory(nullptr, -1, InitInvertorItems[i]);
		
	}

	// +++ SetPose(EUnitPose::Stand, false);		// ** bool _IsUseGroupSpeed

	// +++  ** Bind to delegate for End-Animation-EVENT   (ABaseUnit::    FOnMontageEnded OnAnimationFinish;)
	// +++ FinishAnimationDELEGATE.BindUObject(AIController, &AUnitAI::OnAnimationFinish);

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


void AUnit::SetUnitTask(bool _bAddMoreOne, ETaskType _TaskType, FTaskData _TaskData)
{
	AI->SetTask(_bAddMoreOne, _TaskType, _TaskData);
}



// **  ************************************************************************
// **  ************************     PERCEPTION     ************************* 
// **  ************************************************************************

void AUnit::TargetPerceptionUpdated(AActor* _ActorActivator, FAIStimulus _Stimulus)
{

	if (_Stimulus.Type.Name == FName("Default__AISense_Sight"))
	{
		AI->UpdateLogic();
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
		AI->UpdateLogic();
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

void AUnit::PlayAnimate(UAnimMontage* _AnimMontage, bool _isPlayTOP, float _fromTime)
{
	AnimInstance->CurrentMontage = _AnimMontage;
	AnimInstance->IsPlayTOP = _isPlayTOP;
	AnimInstance->MontageStartTime = _fromTime;

	AnimInstance->Montage_Play(_AnimMontage, 1.f, EMontagePlayReturnType::MontageLength, _fromTime);
	AnimInstance->Montage_SetEndDelegate(FinishAnimationDELEGATE, _AnimMontage);
}





// **  ************************************************************************
// **  ************************     Pose-Locomotion     ************************ 
// **  ************************************************************************



void AUnit::SetMoveSpeed(float _Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = _Speed;
}

void AUnit::StopMove()
{
	GetCharacterMovement()->StopActiveMovement();
}



void AUnit::SetRotateSpeed(uint8 _RotSpeedIndex)
{
	if(_RotSpeedIndex == 0)
		AnimInstance->RotateSpeedSide = 0;
	else
	if(_RotSpeedIndex == 1)
		AnimInstance->RotateSpeedSide = SlowRotateSpeed;
	else
	if (_RotSpeedIndex == 2)
		AnimInstance->RotateSpeedSide = NormalRotateSpeed;
	else
		AnimInstance->RotateSpeedSide = FastRotateSpeed;
}





// **  ************************************************************************
// **  ***************************     Ability     **************************** 
// **  ************************************************************************



void AUnit::AddAbility(EAbilityType _Ability)
{
	Ability->AddAbility(_Ability);
}


// **  ************************************************************************
// **  **************************     Inventory     *************************** 
// **  ************************************************************************



bool AUnit::TryAddItemToInventory(FItemDT* ItemDT, int32 ToSlotIndex, TSubclassOf<AWorldItem> WorldItem)  
{
	return Inventory->TryAddItemToInventory(ItemDT, ToSlotIndex, WorldItem);
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
// **  ************************     TEST_DEBUG    ************************
// **  ************************************************************************


#define WAY_POINT_NAME_TEST0001(A) PointNameForMove ## (A)
//#define IS_POINT_NAME_ROTATE_TEST0001(a) IsRotateByPoint##a
void AUnit::MoveToPointName()
{
	TArray<AActor*> AllWayPointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoint::StaticClass(), AllWayPointActors);
//	int j = 0;
//	WAY_POINT_NAME_TEST0001(j);

//	for(; j <= 10; ++j)
	{
//		if((WAY_POINT_NAME_TEST0001(j)) != FName("none"))
		for (int32 i = 0; i < AllWayPointActors.Num(); i++)
		{
			AWayPoint* wayPoint = Cast<AWayPoint>(AllWayPointActors[i]);
			if (wayPoint->WayPointName == PointNameForMove1)
			{
				FTaskData taskData;
				taskData.Location = wayPoint->GetActorLocation();	// ** or Unit
				if (IsRotateByPoint1)
				{
					taskData.Rotation = wayPoint->GetActorRotation();
					taskData.TaskDislocation = ETaskDislocation::PointRotate;
				}
				else
				{
					taskData.TaskDislocation = ETaskDislocation::PointNoRotate;
				}
				bool bAddMoreOne = true;
				SetUnitTask(bAddMoreOne, ETaskType::MoveToPoint, taskData);
			}
		}
	}








}


