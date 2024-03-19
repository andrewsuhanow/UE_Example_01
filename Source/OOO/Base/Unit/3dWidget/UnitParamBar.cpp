

// #include "Base/Unit/3dWidget/UnitParamBar.h"
#include "UnitParamBar.h"

#include "../Base/Unit.h"

#include "W_UnitParamBar.h"

#include "Components/WidgetComponent.h"   // ** EWidgetSpace



AUnitParamBar::AUnitParamBar()
{

	PrimaryActorTick.bCanEverTick = true;


	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

}


void AUnitParamBar::BeginPlay()
{
	Super::BeginPlay();
	
}


void AUnitParamBar::Init(AUnit* _UnitOwner, TSubclassOf<UW_UnitParamBar>& _W_UnitParamBar_class)
{
	if (!_UnitOwner)
		return;
	if (!_W_UnitParamBar_class)
		return;
	


	///W3dBar_UnitParamComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetBar"));
	W_UnitParamBarComponent = NewObject<UWidgetComponent>(this, TEXT("WUnitParamBar"));
	if (W_UnitParamBarComponent)
	{
		W_UnitParamBarComponent->RegisterComponent();
		W_UnitParamBarComponent->AttachToComponent(RootComp, FAttachmentTransformRules::KeepRelativeTransform);
		W_UnitParamBarComponent->SetVisibility(true);
		W_UnitParamBarComponent->SetCollisionProfileName(TEXT("NoCollision"));
		W_UnitParamBarComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		W_UnitParamBarComponent->SetWidgetSpace(EWidgetSpace::Screen);	// ** World,  Screen
		//W_UnitParamBarComponent->SetWidgetClass(UEntityBarWidget::StaticClass());

		//this->AttachToActor(_UnitOwner, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("UnitBarSocket"));
		this->AttachToComponent(_UnitOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("UnitBarSocket"));

		//float CapsuleRadius, CapsuleHalfHaight;
		//GetComponentsBoundingCylinder(CapsuleRadius, CapsuleHalfHaight, false, false);
		////GetCapsuleComponent()->GetScaledCapsuleSize(CapsuleRadius, CapsuleHalfHaight);
		//W_UnitParamBarComponent->SetRelativeLocation(FVector(0, 0, CapsuleHalfHaight * 2));



		W_UnitParamBar = CreateWidget<UW_UnitParamBar>(GetWorld(), _W_UnitParamBar_class);
		// ** BarWidget = Cast<UEntityBarWidget>(W_UnitParamBarComponent->GetUserWidgetObject());
		if (W_UnitParamBar)
			W_UnitParamBarComponent->SetWidget(W_UnitParamBar);

	}
	
}

void AUnitParamBar::ShowUnitParamBar()
{

}
void AUnitParamBar::HideUnitParamBar()
{

}
void AUnitParamBar::UpdateUnitParamBar()
{

}
void AUnitParamBar::UpdateUnitParamBarEffect(int32 _EffectIndex)
{

}

/*
void AUnitParamBar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//  =====================    Calculate HealhBAR  Position Every Frame    ======================

	//if(GameInstance->ControllerType == )
	if ( BarWidgetComponent && BarWidgetComponent->IsVisible())        //       if  COMPONENT  'EXIST'  and if it 'VISIBLE'
	{
		APlayerController* PC;
		FVector CameraLocation;
		//++if (GameInstance->ControllerType == EControllerType::FreeCameraController)
		{
			PC = GameInstance->CameraPC;
			CameraLocation = GameInstance->CameraPC->PlayerCameraManager->GetCameraLocation();
		}
		//++else //  EControllerType::UnitController
		{
			//+++PC = GameInstance->UnitPC;
			//+++CameraLocation = GameInstance->UnitPC->PlayerCameraManager->GetCameraLocation();
		}
		FVector SelfLocation = GetActorLocation();

		if (PC)
		{

			//   Dist to Camera
			float distToCamera = FVector::Distance(GetActorLocation(), CameraLocation);

			//   Get Capsule Weight and HalfHaight
			float CapsuleRadius, CapsuleHalfHaight;
			GetCapsuleComponent()->GetScaledCapsuleSize(CapsuleRadius, CapsuleHalfHaight);    //++++7777
			//GetComponentsBoundingCylinder(CapsuleRadius, CapsuleHalfHaight, true, true);    //++++7777   If ComponentPerception 777777

			//   Calculane HealhBAR Every Frame
			float UpDist = CapsuleHalfHaight * 1.3f + distToCamera / 35.f;


			// if cameera upper then unit -> healthBar drawn more forward
			if (CameraLocation.Z - SelfLocation.Z > 1000.f)
			{
				FVector PawnFreeCameraForvardVector = PC->GetPawn()->GetActorForwardVector();
				FVector NewLocation = SelfLocation + PawnFreeCameraForvardVector * 70.f;

				// (when unit approching up-close to monitor-Border -> HalthBar is offseting)  here is offseting it back
				FVector PawnFreeCameraLocation = PC->GetPawn()->GetActorLocation();
				float X_Offset = PawnFreeCameraLocation.X - SelfLocation.X;
				NewLocation.X += X_Offset / 15.f;
				float Y_Offset = PawnFreeCameraLocation.Y - SelfLocation.Y;
				NewLocation.Y += Y_Offset / 15.f;

				//  Applay position to HalthBar
				BarWidgetComponent->SetWorldLocation(FVector(NewLocation.X, NewLocation.Y, SelfLocation.Z + UpDist));
				WorldTextWidgetComponent->SetWorldLocation(FVector(NewLocation.X, NewLocation.Y, SelfLocation.Z + UpDist + 50.f));
			}
			else
			{	//  Applay position to HalthBar
				BarWidgetComponent->SetRelativeLocation(FVector(0, 0, UpDist));
				WorldTextWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, UpDist + 50.f));
			}

		}
	}
	//----------------------------------------------------------------------


}
*/
