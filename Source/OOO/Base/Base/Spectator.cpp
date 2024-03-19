

//#include "../Base/Spectator.h"
#include "Spectator.h"

#include "BaseGameMode.h"
#include "BaseGameState.h"
#include "../HUD/BaseHUD.h"
//--77--#include "../HUD/Widget/W_Screen.h"
//--77--#include "../HUD/Widget/Slot/W_Slot.h"

#include "../Unit/Base/Unit.h"
#include "../Controller/UnitAI.h"

#include "../Fraction/FractionSystem.h"

#include "../WorldObject/GameObject/StaticObject.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerInput.h"   

#include "../Controller/Task/TMoveTo.h"
#include "../Controller/Task/TUseAbility.h"

//-----#include "Components/CapsuleComponent.h"



ASpectator::ASpectator()
{
	PrimaryActorTick.bCanEverTick = true;


	
	AutoPossessPlayer = EAutoReceiveInput::Player0;     // ** Auto Posses



	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	//USpringArmComponent* SpringArm;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 2500.0f;
	SpringArm->SetWorldRotation(FRotator(-50.0f, 0.0f, 0.0f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritPitch = false;

	//UCameraComponent* Camera;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	//Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);   

	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}



void ASpectator::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASpectator::SetDefaultGameParam(ABaseGameMode* _GameMode,
	ABaseHUD* _HUD, ABaseGameState* _GameState)
{
	if (!_GameMode)		return;
	if (!_GameState)	return;
	if (!_HUD)			return;


	GameMode = _GameMode;
	HUD = _HUD;
	GameState = _GameState;

	// ** Store Screen-Size
	GetWorld()->GetFirstPlayerController()->GetViewportSize(ViewportSize_X, ViewportSize_Y);

	



	// ** init RayCast Param
	//++++ECollisionChannel CollisionChannel;        /// ** ECollisionChannel::ECC_WorldStatic, ECC_WorldDynamic, ECC_Pawn, ECC_Visibility, ECC_Camera
	//++++FCollisionResponseParams ResponseParams;   // ** ECollisionResponse::ECR_Block
	//++++bool bTraceChanelIsOk, bCanTrace = false;
	//+++bTraceChanelIsOk = UCollisionProfile::GetChannelAndResponseParams(FName("MyTerrain"), CollisionChannel, ResponseParams);
	//+++bCanTrace = bTraceChanelIsOk ? ObjectTypesQuery.Add(UEngineTypes::ConvertToObjectType(CollisionChannel)), true : false;
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_Pawn));
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldStatic));
	ObjectTypesQuery.Add(EObjectTypeQuery(ECC_WorldDynamic));

}


void ASpectator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	/*
	// **** Detect Ground      (Vertical Camera Move)
	{
		FHitResult CameraTraceHit;
		FCollisionQueryParams TraceParams(FName("Ray Cast"), true, this);

		ECollisionChannel CollisionChannel;        // ECollisionChannel::ECC_WorldStatic, ECC_WorldDynamic, ECC_Pawn, ECC_Visibility, ECC_Camera
		FCollisionResponseParams ResponseParams;   // ECollisionResponse::ECR_Block
		bool bTraceChanelIsOk, bCanTrace = false;

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesQuery;
		bTraceChanelIsOk = UCollisionProfile::GetChannelAndResponseParams(FName("MyTerrain"), CollisionChannel, ResponseParams);
		bCanTrace = bTraceChanelIsOk ? ObjectTypesQuery.Add(UEngineTypes::ConvertToObjectType(CollisionChannel)), true : false;
		//bTraceChanelIsOk = UCollisionProfile::GetChannelAndResponseParams(FName("MyHouse"), CollisionChannel, ResponseParams);
		//	bCanTrace = bTraceChanelIsOk ? ObjectTypesQuery.Add(UEngineTypes::ConvertToObjectType(CollisionChannel)), true : false;
		// +++++ ObjectTypesQuery.Add(EObjectTypeQuery(ECC_Pawn));
		FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);

		FVector StartLocation = GetActorLocation();
		FVector EndLocation = GetActorLocation() + FVector(0, 0, -1) * 500000;
		GetWorld()->LineTraceSingleByObjectType(CameraTraceHit, StartLocation, EndLocation, ObjectQueryParams, TraceParams);
					
		if (CameraTraceHit.bBlockingHit)
		{
			float DistantToGround = FVector::Distance(StartLocation, CameraTraceHit.Location);
			if (DistantToGround > 200.f)
			{
				FVector CameraActorDir = FVector(0.f, 0.f, -DeltaTime);
				AddActorLocalOffset(CameraActorDir * FreeCameraSpeed, false);
			}
		} 
		else
		{
			FVector CameraActorDir = FVector(0.f, 0.f, DeltaTime);
			AddActorLocalOffset(CameraActorDir  * FreeCameraSpeed, false);
		}
		  
		//if (CameraTraceHit.bBlockingHit)
		//{
		//	DrawDebugLine(
		//		GetWorld(),
		//		GetActorLocation(),  //GetActorLocation(),
		//		EndLocation,//TraceEnd,
		//		FColor::Green,
		//		false,	// is visible always
		//		0.5f,	// visible time
		//		0,
		//		5.0f);	// siknes
		//	DrawDebugSphere(
		//		GetWorld(),
		//		CameraTraceHit.Location,  // center
		//		50.f,	// radius
		//		20,		// Segments
		//		FColor(FColor::Blue),
		//		false, // bPersistLine
		//		0.5f, //GetWorld()->GetDeltaSeconds() * 3,
		//		5,	// DepthPriority
		//		5);	// Thick
		//}
	}
	*/
}




// ***************************************************************************
// **************************    Unit_Operation    **************************
// ***************************************************************************









// ***************************************************************************
// ****************************    Move_Rotate    ****************************
// ***************************************************************************







// ** Move
void ASpectator::MoveForward(float val)
{
	if (val != 0)
	{
		FVector CameraActorDir = FVector(val, 0.f, 0.f);
		AddActorLocalOffset(CameraActorDir * SpringArm->TargetArmLength * FreeCameraSpeed * GetWorld()->GetDeltaSeconds(), false);
	}
}
void ASpectator::MoveRight(float val)
{
	if (val != 0)
	{
		FVector CameraActorDir = FVector(0.f, val, 0.f);
		AddActorLocalOffset(CameraActorDir * SpringArm->TargetArmLength * FreeCameraSpeed * GetWorld()->GetDeltaSeconds(), false);
	}
}


// ** Rotate / Cursor-move

void ASpectator::CursorMoveX(float val)
{
	//  ================ Mouse Rotate X ================
	if (val != 0)
	{
		// ** Is any move
		MouseStopHoldingTime = GameMode->MouseStopHoldingTime;
		if (IsMouseWaitingContextActive)
		{
			IsMouseWaitingContextActive = false;
			GameState->SelectUnitMouseFocused(nullptr);
			HUD->HideTargetEffectPanel();
		}

		MouseDeltaPos.X = val * GetWorld()->GetDeltaSeconds() * 75.f;

		if (Mouse_R_Click)
		{
			FRotator newYaw = GetActorRotation();
			newYaw.Yaw += MouseDeltaPos.X;
			SetActorRotation(newYaw);
			GetWorld()->GetFirstPlayerController()->SetMouseLocation(R_LustMouseClickPos.X, R_LustMouseClickPos.Y);
		}
	}
	else
	{
		StopCursorMove();
	}
		
}
void ASpectator::CursorMoveY(float val)
{
	//  ================ Mouse Rotate Y ================
	if (val != 0)
	{
		// ** Is any move
		MouseStopHoldingTime = GameMode->MouseStopHoldingTime;
		if (IsMouseWaitingContextActive)
		{
			IsMouseWaitingContextActive = false;
			GameState->SelectUnitMouseFocused(nullptr);
			HUD->HideTargetEffectPanel();
		}

		MouseDeltaPos.Y = val * GetWorld()->GetDeltaSeconds() * 75.f;

		if (Mouse_R_Click)
		{
			FRotator newPitch = SpringArm->GetComponentRotation();
			newPitch.Pitch = FMath::Clamp(newPitch.Pitch + MouseDeltaPos.Y, -85.f, 58.f);
			SpringArm->SetWorldRotation(newPitch);
			GetWorld()->GetFirstPlayerController()->SetMouseLocation(R_LustMouseClickPos.X, R_LustMouseClickPos.Y);
			//++77++FRotator newPitch = SpringArm->GetRelativeRotation();
			//++77++newPitch.Pitch += val;
			//++77++SpringArm->SetRelativeRotation(newPitch);
		}
	}
	else
	{
		StopCursorMove();
	}
}

void ASpectator::StopCursorMove()
{

	MouseDeltaPos = FVector2D(0, 0);

	MouseStopHoldingTime -= GetWorld()->GetDeltaSeconds();

	// ** Draw Mouse-Context
	if (MouseStopHoldingTime <= 0.f && !IsMouseWaitingContextActive)
	{
		IsMouseWaitingContextActive = true;
		MouseStopHolding_ReyCast();
	}
}


void ASpectator::ScrollZoom(float val)
{
	if (val != 0)
	{
		//ZoomFactor += val / 5.25f;
		//ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 10.0f);
		//Camera->FieldOfView = FMath::Lerp<float>(90.f, 60.f, ZoomFactor);
		//SpringArm->TargetArmLength = FMath::Lerp<float>(400.f, 300.f, ZoomFactor);
		//SpringArm->TargetArmLength = FMath::Lerp<float>(400.f, 300.f, val);

		//  ==============================          Mouse Scroll        ===============================	
		SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, SpringArm->TargetArmLength - val * 70.f, GetWorld()->GetDeltaSeconds(), 1200.f);
		//FMath::Clamp()
	}
}






// ***************************************************************************
// ****************************    Mouse_Press    ****************************
// ***************************************************************************



// ** Press mouse
void ASpectator::Mouse_L_Press()
{
	if (!HUD) return;


	Mouse_L_Click = true;

/*
	// ** Draw Arrow Direction
	if (bShift_Left && SelectGroup.Num() > 0)
	{
		IsDirrectionArrowDrawing = true;

		if (DirrectionArrow)
		{
			FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);
			GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorForObjects(ObjectTypesQuery, true, LineTraceHit);
			if (LineTraceHit.bBlockingHit)
			{
				DirrectionArrow->MeshBase->SetWorldLocation(LineTraceHit.Location);
				MouseLocationPos_Click_L = LineTraceHit.Location;
			}

			GetWorld()->GetTimerManager().SetTimer(TH_LeftMouseClick, this, &ThisClass::LeftMouseClick_Handle, GetWorld()->GetDeltaSeconds(), true);
		}
		return;
	}

	// ** Start Draw Rectangle-Selection
	else
	{
		mHUD->SetStartPointRect();

		IsSelectionRectangleDrawing = true;
	}
*/
}

void ASpectator::Mouse_L_Release()
{

	Mouse_L_Click = false;
	GetWorld()->GetTimerManager().ClearTimer(TH_LeftMouseClick);
	LeftMouseClick_CheckTime = 0.f;


	// ** Check "Clicking-Position"
	FVector2D l_crrMouseClickPos;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(l_crrMouseClickPos.X, l_crrMouseClickPos.Y);


/*
	// ** Single Click
	float MouseMoveDist = FVector2D::Distance(l_crrMouseClickPos, L_LustMouseClickPos);
	if (MouseMoveDist < 20.f)
		//if (l_crrMouseClickPos == L_LustMouseClickPos)
	{
		L_MouseRelase_ReyCast();

		mHUD->SetCancelPointRect();
	}
	else
	{
		// **  DRAW DIRRECTION-ARROW mode
		if (IsDirrectionArrowDrawing)
		{
			if (DirrectionArrow)
			{
				for (int32 i = 0; i < SelectGroup.Num(); ++i)
				{
					FVector Pos = DirrectionArrow->MeshBase->GetComponentLocation();

					FVector dir = DirrectionArrow->MeshMiddle->GetForwardVector();
					//dir.Y = 0.f;
					//SelectGroup[i]->ActionTask_Set(EActionState::Move, true, nullptr, Pos, dir, true);
					if (bShift_Left)
					{
						SelectGroup[i]->ActionTask_Add(EActionState::Move_to_Point, true, nullptr, Pos, dir, true);
					}
					else
					{
						SelectGroup[i]->ActionTask_Set(EActionState::Move_to_Point, true, nullptr, Pos, dir, true);
					}

					//DirrectionArrow
				}


				DirrectionArrow->SetActorHiddenInGame(true);
			}
		}


		// ** Do Draw Rectangle-Selection
		if (IsSelectionRectangleDrawing)
		{
				mHUD->DoRectSelect(this);
		}
	}
	//++++++IsDirrectionArrowDrawing = false;
	//++++++IsSelectionRectangleDrawing = false;
*/




	// ** TEST Click L
	L_MouseRelase_ReyCast();


	// *** After all
	L_LustMouseClickPos = l_crrMouseClickPos;
}


void ASpectator::LeftMouseClick_Handle()
{
/*
	// **  DRAW DIRRECTION-ARROW  (TICK)
	FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorForObjects(ObjectTypesQuery, true, LineTraceHit);
	if (LineTraceHit.bBlockingHit)
	{
		float dist = FVector::Dist(MouseLocationPos_Click_L, LineTraceHit.Location);
		FVector dir_unNormal = LineTraceHit.Location - MouseLocationPos_Click_L;
		FRotator rot = dir_unNormal.Rotation();

		FVector middlePoint = MouseLocationPos_Click_L + dir_unNormal.GetSafeNormal() * dist / 2.f;

		FVector deltaScale = FVector(dist / 300.f, dist / 300.f, dist / 600.f);

		if (dist > 70.f)
		{
			if (dist < 900.f)
			{
				DirrectionArrow->MeshBase->SetWorldScale3D(deltaScale);
			}
			DirrectionArrow->MeshMiddle->SetWorldLocation(middlePoint);
			DirrectionArrow->MeshMiddle->SetWorldRotation(rot);
			DirrectionArrow->MeshMiddle->SetWorldScale3D(deltaScale);

			DirrectionArrow->MeshEnd->SetWorldLocation(LineTraceHit.Location);
			DirrectionArrow->MeshEnd->SetWorldRotation(rot);
			DirrectionArrow->MeshEnd->SetWorldScale3D(deltaScale);

			DirrectionArrow->SetActorHiddenInGame(false);
		}
	}
*/
}







//-------------------------------------------------

// ********** Mouse--R--Click

void ASpectator::Mouse_R_Press()
{
	// ** can be "Rotate-Screen"
	Mouse_R_Click = true;
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

	// ** Check if R_Mouse-Button is HOLDING
	GetWorld()->GetTimerManager().SetTimer(TH_RightMouseClick, this, &ThisClass::RightMouseClick_Handle, GetWorld()->GetDeltaSeconds(), true);
	RightMouseClick_CheckTime = 0.f;

	// ** Save "Clicking-Position"
	GetWorld()->GetFirstPlayerController()->GetMousePosition(R_LustMouseClickPos.X, R_LustMouseClickPos.Y);


	// ** "Daily-Behavior" Spawn-/-Select "Way-Point"  (CANCEL Button)
	//+++++++IsActivateButton_Select_WayPoint = false;
	//+++++++IsActivateButton_Add_WayPoint = false;
}


// ********** Mouse--R--Release
void ASpectator::Mouse_R_Release()
{
	// ** Stop "Rotate-Screen"
	Mouse_R_Click = false;
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	// ** Restore clicking 2D position 
	GetWorld()->GetFirstPlayerController()->SetMouseLocation(R_LustMouseClickPos.X, R_LustMouseClickPos.Y);


	// ** Save "Clicking-Position"
	//---7777---GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePos2D_Release_R.X, MousePos2D_Release_R.Y);
}

// ********** Check Mouse--R--HOLDING
void ASpectator::RightMouseClick_Handle()
{
	/*
	RightMouseClick_CheckTime += GetWorld()->GetDeltaSeconds();
	if (RightMouseClick_CheckTime >= 0.2f)
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_RightMouseClick);
		RightMouseClick_CheckTime = 0.f;

		FVector2D r_crrMouseClickPos;
		GetWorld()->GetFirstPlayerController()->GetMousePosition(r_crrMouseClickPos.X, r_crrMouseClickPos.Y);
		if (r_crrMouseClickPos == R_LustMouseClickPos)
		{
			Mouse_R_Click = false;
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

			// ** Delselect-All-Units
			DeselectAllUnits();

			RightMouseClick_CheckTime = 0.f;
		}
	}
	*/
}




//-------------------------------------------------

// ********** Mouse--Middle--Click

void ASpectator::Mouse_M_Press()
{

}
void ASpectator::Mouse_M_Release()
{

}





// ***************************************************************************
// ****************************    Ray_Cast    ****************************
// ***************************************************************************


void ASpectator::L_MousePress_ReyCast()
{

}
void ASpectator::R_MousePress_ReyCast()
{

}


void ASpectator::L_MouseRelase_ReyCast()
{
	if (!GameMode) return;
	if (!GameState) return;


	// ** Hide NavPath markers (in all selected units)
	if (GameState->GetCountOfSelectUnits() >= 1)
	{
		for (int32 i = 0; i < GameState->GetCountOfSelectUnits(); ++i)
		{
			GameState->GetSelectedUnit(0)->HideNavPathMarkers();
		}
	}


	// REY CAST
	FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorForObjects(ObjectTypesQuery, true, LineTraceHit);


	// ** Draw-Arrow
	//+++++++++++++if (LineTraceHit.bBlockingHit && bDrawArrowUse)
	//{
	//	if (LineTraceHit.GetActor())
	//	{
	//		/// ** TArray<FVector> eachLocation;
	//		/// ** TArray <FRotator> eachLocation;
	//		/// ** UnitAI::GeneratePlaceRows(&SelectUnits[xx], StartLocation, Rotation, eachLocation, eachLocation);
	//	}
	//}



	// @@@@@@@@@@@@@@@@@@@@  Ability
	// @@@@@@@@@@@@@@@@@@@@  Ability
	// @@@@@@@@@@@@@@@@@@@@  Ability
	// ** if Ability(Fast panel button) activated
	ETargetType abilityTargetType = ETargetType::Self;
	int32 abilityIndex = -1;
	bool isAbilityItem = false;
	int32 abilTargetsCount = 0;
	//-----FName abilityName = FName("none");

	if (GameState->GetCountOfSelectUnits() == 1)
	{
		if (GameState->GetSelectedUnit(0)->IsHasInstantHoldAbility())
			abilityIndex = GameState->GetSelectedUnit(0)->GetInstantHoldingAbility();
		else if (GameState->GetSelectedUnit(0)->IsHasPermanentHoldAbility())
			abilityIndex = GameState->GetSelectedUnit(0)->GetPermanentHoldingAbility();

		isAbilityItem = GameState->GetSelectedUnit(0)->IsItemInFastPanelSlot(abilityIndex);
		abilityTargetType = GameState->GetSelectedUnit(0)->GetAbilityTargetType(abilityIndex, abilTargetsCount);
	}
	//---abilityIndex = GameState->GetSelectedUnit(0)->GetAbilityNameFromFastSlotIx(abilityIndex);





	// ** 
	// ** Check target type
	// ** 


	if (LineTraceHit.GetActor())
	{
		
		// ** 
		// ** if "Unit"
		// ** 

		AUnit* clickUnit = Cast<AUnit>(LineTraceHit.GetActor());
		if (clickUnit)
		{


			// @@@@@@@@@@@@@@@@@@@@  Ability
			// @@@@@@@@@@@@@@@@@@@@  Ability
			// @@@@@@@@@@@@@@@@@@@@  Ability
			// ** if ability use
			if (abilityIndex != -1)
			{
				if (abilityTargetType == ETargetType::Unit)
				{
					CollectionTargetUnits.Add(clickUnit);

					FTaskData abilityTaskData;
					UTUseAbility::SetTaskData_UseAbilityToUnit(abilityTaskData, 
						GameState->GetSelectedUnit(0), abilityIndex, isAbilityItem, CollectionTargetUnits);

					GameState->GetSelectedUnit(0)->SetUnitTask(bShift_Left, ETaskType::UseAbility, abilityTaskData);
					
					CollectionTargetUnits.Reset();
					
					HUD->ShowFastPanel(GameState->GetSelectedUnit(0));
				}
/*				else if (abilityTargetType == ETargetType::Units)
				{
					if (UnitAsAbilityTarget.Num() == AbilityTargetsCount-1)
					{
						UnitAsAbilityTarget.Add(clickUnit);

						FTaskData abilityTaskData;
						UTUseAbility::SetTaskData_UseAbilityToUnit(abilityTaskData,
							GameState->GetSelectedUnit(0), abilityIndex, isAbilityItem, UnitAsAbilityTarget);
						GameState->GetSelectedUnit(0)->SetUnitTask(bShift_Left, ETaskType::UseAbility, abilityTaskData);
						UnitAsAbilityTarget.Reset();

						bool isPermanent = false;
						HUD->DeselectFastPanelSlot(iFastPanelButtonActicated, isPermanent);

						iFastPanelButtonActicated = -1;
					}
					else // ** if (UnitAsAbilityTarget.Num() < AbilityTargetsCount)
					{
						UnitAsAbilityTarget.Add(clickUnit);
						return;
					}
				}
*/				else if (abilityTargetType == ETargetType::Location)
				{
					CollectionTargetPoints.Add(LineTraceHit.ImpactPoint);

					FTaskData abilityTaskData;
					UTUseAbility::SetTaskData_UseAbilityToLocation(abilityTaskData, 
						GameState->GetSelectedUnit(0), abilityIndex, isAbilityItem, CollectionTargetPoints);

					GameState->GetSelectedUnit(0)->SetUnitTask(bShift_Left, ETaskType::UseAbility, abilityTaskData);

					CollectionTargetPoints.Reset();

					HUD->ShowFastPanel(GameState->GetSelectedUnit(0));
				}
				return;
			}






			// ** Recognize unit fraction
			uint8 unitFraction = clickUnit->GetFraction();
			EUnitAttitudeStatus attitude = GameMode->GetFractionAttitude(0, unitFraction); // ** 0 - Self fraction	(Friend, Neutral, Enemy)


			if (attitude == EUnitAttitudeStatus::Friend)
			{
				if (GameState->GetCountOfSelectUnits() > 1)
				{
					GameState->SelectOneUnit(clickUnit);
				}
				if (GameState->GetCountOfSelectUnits() == 1)
				{
					////	if Comand Move 
					////			//+++++++++++++++++++
					////	if Comand Attack
					////		//+++++++++++++++++++
					////	else
					GameState->SelectOneUnit(clickUnit);
				}
				if (GameState->GetCountOfSelectUnits() == 0)
				{
					GameState->SelectOneUnit(clickUnit);
				}
			}
			else if (attitude == EUnitAttitudeStatus::Enemy)
			{
				////	if Has SelectGroup

				////		//+++++++++++++++++++++++++

				////	if Has Select

				////		//+++++++++++++++++++++++++

				////	if No Select

				////		//-------------------------
			}


		}

		// ** 
		// ** if "Object"
		// ** 

		else if (false)
		{

		}


		// **
		// ** if "Terrain"
		// **
		AStaticObject* clickedStaticObject = Cast<AStaticObject>(LineTraceHit.GetActor());
		if (clickedStaticObject)
		{



			// @@@@@@@@@@@@@@@@@@@@  Ability
			// @@@@@@@@@@@@@@@@@@@@  Ability
			// @@@@@@@@@@@@@@@@@@@@  Ability
			// ** if ability use
/*			if (iFastPanelButtonActicated != -1 && GameState->GetCountOfSelectUnits() == 1)
			{
				if (abilityTargetType == ETargetType::Location)
				{
					FTaskData abilityTaskData;
					UTUseAbility::SetTaskData_UseAbilityToLocation(abilityTaskData,
						GameState->GetSelectedUnit(0), abilityIndex, LineTraceHit.ImpactPoint);
					GameState->GetSelectedUnit(0)->SetUnitTask(bShift_Left, ETaskType::UseAbility, abilityTaskData);					

					bool isPermanent = false;
					HUD->DeselectFastPanelSlot(iFastPanelButtonActicated, isPermanent);

					iFastPanelButtonActicated = -1;
					return;
				}
			}
*/




			int32 countOfSelectUnits = GameState->GetCountOfSelectUnits();

			if (countOfSelectUnits >= 1)
			{
				for (int32 i = 0; i < countOfSelectUnits; ++i)
				{
					AUnit& selectUnit = *GameState->GetSelectedUnit(i);

					// ** First draw then Move (Check: if again click in this location) 
					FVector2D l_crrMouseClickPos;
					GetWorld()->GetFirstPlayerController()->GetMousePosition(l_crrMouseClickPos.X, l_crrMouseClickPos.Y);
					float mouseMoveDist = FVector2D::Distance(l_crrMouseClickPos, L_LustMouseClickPos);

					if (selectUnit.IsNavPathGenerate() && mouseMoveDist < 20.f)
					{
						// ** move Task
						FTaskData taskData;
						float stopDist = 0;
						UTMoveTo::SetMoveData_MoveToPoint(taskData, GameState->GetSelectedUnit(i), 
							LineTraceHit.Location, stopDist, EUnitPose::none);

						GameState->GetSelectedUnit(i)->SetUnitTask(false, ETaskType::MoveTo, taskData);
						return;
					}

					// ** First draw then Move (Check: if again click in this location) 
					bool isDrawPath = true;
					selectUnit.GenerateNavPath(isDrawPath, true, LineTraceHit.Location);

				}
			}
		}



	}
}

void ASpectator::R_MouseRelase_ReyCast()
{

}

void ASpectator::MouseStopHolding_ReyCast()
{
	// REY CAST
	FCollisionObjectQueryParams ObjectQueryParams(ObjectTypesQuery);
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorForObjects(ObjectTypesQuery, true, LineTraceHit);


	// ** Draw Mouse-Context  (Unit)
	AUnit* mouseFocusUnit = Cast<AUnit>(LineTraceHit.GetActor());
	if (mouseFocusUnit)
	{
		if (!GameState)
			return;

		GameState->SelectUnitMouseFocused(mouseFocusUnit);
		HUD->ShowTargetEffectPanel(mouseFocusUnit);
	}

	// ...
	// ...
	// ...
	// ...
}




// ***************************************************************************
// ****************************    Key_1    ****************************
// ***************************************************************************





void ASpectator::Shift_Left_Press()
{
	bShift_Left = true;
}

void ASpectator::Shift_Left_Release()
{
	bShift_Left = false;
}

void ASpectator::TAB_Press()
{

}
void ASpectator::TAB_Release()
{

}

void ASpectator::Enter_Press()
{

}
void ASpectator::Enter_Release()
{

}

void ASpectator::Space_Press()
{
	bSpaceBar = true;
}
void ASpectator::Space_Release()
{
	bSpaceBar = false;
	//+++++++++GameState->SetTacticPause();				// **  GameState
}







// ***************************************************************************
// ****************************    Key_2    ****************************
// ***************************************************************************






// ** Posses: KEY
void ASpectator::Key_0_Press()
{
	/* +++++++++++++++++++++++

	//if (IsChangeUnitAgent_InProgress == 0 && SelectGroup.Num() == 1)
	if (SelectGroup.Num() == 1)
	{
		PossesUnit(SelectGroup[0]);
	}
	*/
}



void ASpectator::Key_Q_Press()
{

}
void ASpectator::Key_E_Press()
{

}
void ASpectator::Key_F_Press()
{

}
void ASpectator::Key_G_Press()
{

}
void ASpectator::Key_Z_Press()
{

}
void ASpectator::Key_X_Press()
{

}
void ASpectator::Key_C_Press()
{

}
void ASpectator::Key_V_Press()
{

}
void ASpectator::Key_R_Press()
{

}
void ASpectator::Key_T_Press()
{

}







// ***************************************************************************
// ****************************    Input    ****************************
// ***************************************************************************






void ASpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;



	// ** Posses
	FInputActionKeyMapping Key0("Key0", EKeys::Zero, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(Key0);

	// ** 777777
	FInputActionKeyMapping LeftShift("LeftShift", EKeys::LeftShift, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(LeftShift);

	// ** 777777
	FInputActionKeyMapping TAB("KeyTAB", EKeys::Tab, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(TAB);

	// ** 777777
	FInputActionKeyMapping Enter("KeyEnter", EKeys::Enter, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(Enter);
	FInputActionKeyMapping Space("KeySpace", EKeys::SpaceBar, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(Space);

	FInputActionKeyMapping Mouse_L("Mouse_L", EKeys::LeftMouseButton, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(Mouse_L);
	FInputActionKeyMapping Mouse_R("Mouse_R", EKeys::RightMouseButton, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(Mouse_R);
	FInputActionKeyMapping Mouse_M("Mouse_M", EKeys::MiddleMouseButton, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(Mouse_M);

	FInputActionKeyMapping E("KeyE", EKeys::E, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(E);
	FInputActionKeyMapping Q("KeyQ", EKeys::Q, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(Q);
	FInputActionKeyMapping F("KeyF", EKeys::F, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(F);
	FInputActionKeyMapping Z("KeyZ", EKeys::Z, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(Z);
	FInputActionKeyMapping X("KeyX", EKeys::X, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(X);
	FInputActionKeyMapping C("KeyC", EKeys::C, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(C);
	FInputActionKeyMapping V("KeyV", EKeys::V, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(V);
	FInputActionKeyMapping T("KeyT", EKeys::T, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(T);
	FInputActionKeyMapping R("KeyR", EKeys::R, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(R);
	FInputActionKeyMapping G("KeyG", EKeys::G, false);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(G);





	// Add Mapping button W, S.  (Move Forward)
	FInputAxisKeyMapping W_Axis("KeyWS", EKeys::W, 1.0f);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(W_Axis);
	FInputAxisKeyMapping S_Axis("KeyWS", EKeys::S, -1.0f);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(S_Axis);
	// Add Mapping button A, D.  (Move Right)
	FInputAxisKeyMapping A_Axis("KeyAD", EKeys::A, -1.0f);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(A_Axis);
	FInputAxisKeyMapping D_Axis("KeyAD", EKeys::D, 1.0f);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(D_Axis);
	// Add Mapping Mouse X, Y.   (Rotate)
	FInputAxisKeyMapping MouseX("MouseX", EKeys::MouseX, 1.0f);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(MouseX);
	FInputAxisKeyMapping MouseY("MouseY", EKeys::MouseY, 1.0f);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(MouseY);

	// **  Scroll Zoom         
	FInputAxisKeyMapping ScrollZoom("ScrollZoom", EKeys::MouseWheelAxis, 1.0f);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(ScrollZoom);




	// ******  Set Function  ******

	PlayerInputComponent->BindAction("Key0", IE_Pressed, this, &ThisClass::Key_0_Press);					// ** Posses 
	PlayerInputComponent->BindAction("KeyQ", IE_Pressed, this, &ThisClass::Key_Q_Press);
	PlayerInputComponent->BindAction("KeyE", IE_Pressed, this, &ThisClass::Key_E_Press);
	PlayerInputComponent->BindAction("KeyF", IE_Pressed, this, &ThisClass::Key_F_Press);
	PlayerInputComponent->BindAction("KeyZ", IE_Pressed, this, &ThisClass::Key_Z_Press);
	PlayerInputComponent->BindAction("KeyX", IE_Pressed, this, &ThisClass::Key_X_Press);
	PlayerInputComponent->BindAction("KeyC", IE_Pressed, this, &ThisClass::Key_C_Press);
	PlayerInputComponent->BindAction("KeyV", IE_Pressed, this, &ThisClass::Key_V_Press);
	PlayerInputComponent->BindAction("KeyR", IE_Pressed, this, &ThisClass::Key_R_Press);
	PlayerInputComponent->BindAction("KeyT", IE_Pressed, this, &ThisClass::Key_T_Press);
	PlayerInputComponent->BindAction("KeyG", IE_Pressed, this, &ThisClass::Key_G_Press);



	PlayerInputComponent->BindAction("LeftShift", IE_Pressed, this, &ThisClass::Shift_Left_Press);
	PlayerInputComponent->BindAction("LeftShift", IE_Released, this, &ThisClass::Shift_Left_Release);

	PlayerInputComponent->BindAction("KeyTAB", IE_Pressed, this, &ThisClass::TAB_Press);
	PlayerInputComponent->BindAction("KeyTAB", IE_Released, this, &ThisClass::TAB_Release);

	PlayerInputComponent->BindAction("KeyEnter", IE_Pressed, this, &ThisClass::Enter_Press);
	PlayerInputComponent->BindAction("KeyEnter", IE_Released, this, &ThisClass::Enter_Release);
	PlayerInputComponent->BindAction("KeySpace", IE_Pressed, this, &ThisClass::Space_Press);
	PlayerInputComponent->BindAction("KeySpace", IE_Released, this, &ThisClass::Space_Release);

	PlayerInputComponent->BindAction("Mouse_L", IE_Pressed, this, &ThisClass::Mouse_L_Press);
	PlayerInputComponent->BindAction("Mouse_L", IE_Released, this, &ThisClass::Mouse_L_Release);
	PlayerInputComponent->BindAction("Mouse_R", IE_Pressed, this, &ThisClass::Mouse_R_Press);
	PlayerInputComponent->BindAction("Mouse_R", IE_Released, this, &ThisClass::Mouse_R_Release);
	PlayerInputComponent->BindAction("Mouse_M", IE_Pressed, this, &ThisClass::Mouse_M_Press);
	PlayerInputComponent->BindAction("Mouse_M", IE_Released, this, &ThisClass::Mouse_M_Release);


	PlayerInputComponent->BindAxis("KeyWS", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("KeyAD", this, &ThisClass::MoveRight);

	PlayerInputComponent->BindAxis("MouseX", this, &ThisClass::CursorMoveX);
	PlayerInputComponent->BindAxis("MouseY", this, &ThisClass::CursorMoveY);

	// ** ScroolZoom
	PlayerInputComponent->BindAxis("ScrollZoom", this, &ThisClass::ScrollZoom);
}