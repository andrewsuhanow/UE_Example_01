
//#include "Base/Unit/Base/Unit.h"
#include "Unit.h"

#include "../../Controller/UnitAI.h"

AUnit::AUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	// **  AI Controller 
	static ConstructorHelpers::FObjectFinder<UBlueprint> AI_Res(TEXT("/Game/Core/Controller/Base/UnitAi_BP.UnitAi_BP")); 
	if (AI_Res.Object) AIController_Class = (UClass*)AI_Res.Object->GeneratedClass;
	if (AIController_Class)	AIControllerClass = AIController_Class;
}


void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
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

