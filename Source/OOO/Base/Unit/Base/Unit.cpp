
//#include "Base/Unit/Base/Unit.h"
#include "Unit.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "../../Controller/UnitAI.h"

#include "../../Animation/AnimInstance/HumanAnimInst.h"

#include "../../WorldObject/WayPoint/WayPoint.h"

// --------------------------------------------

#include "Kismet/GameplayStatics.h"   // ** GetAllActorsOfClass()



AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = true;


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

	// ** "Game-Delay" 
	GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::Start, 1.f, false);
}


void AUnit::Start()
{
	UE_LOG(LogTemp, Warning, TEXT("ERROR:_______________AUnitAI::Start()_______________Init Continue"));



	if (!AI)
	{
		AI = Cast<AUnitAI>(GetController());
		if (!AI)
		{
			GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::Start, 1.f, false);
			return;
		}
		else
		{
			AI->Init();
		}
	}


	if (!AnimInstance)
	{
		AnimInstance = Cast<UHumanAnimInst>(GetMesh()->GetAnimInstance());	}



	// +++ SetPose(EUnitPose::Stand, false);		// ** bool _IsUseGroupSpeed

	// +++  ** Bind to delegate for End-Animation-EVENT   (ABaseUnit::    FOnMontageEnded OnAnimationFinish;)
	// +++ FinishAnimationDELEGATE.BindUObject(AIController, &AUnitAI::OnAnimationFinish);

	return;
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
// **  ************************     XXXX001     ************************ 
// **  ************************************************************************


void AUnit::SetUnitTask(bool _bAddMoreOne, ETaskType _TaskType, FTaskData _TaskData)
{
	AI->SetTask(_bAddMoreOne, _TaskType, _TaskData);
}







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


