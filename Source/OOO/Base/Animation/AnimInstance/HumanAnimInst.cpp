

//#include "Base/Animation/AnimInstance/HumanAnimInst.h"
#include "HumanAnimInst.h"


#include "../../Unit/Base/Unit.h"




UHumanAnimInst::UHumanAnimInst()   // const FObjectInitializer& ObjectInitializer
{

}



void UHumanAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	UnitOwner = Cast<AUnit>(TryGetPawnOwner());
	if (UnitOwner)
		UnitOwner->AnimInstance = this;

}



void UHumanAnimInst::GetOwner()
{
	UnitOwner = Cast<AUnit>(TryGetPawnOwner());
}



void UHumanAnimInst::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);


	if (!UnitOwner)
	{
		//** Check UsingCharacter,  try Get again
		GetOwner();
		if (!UnitOwner)
		{
			UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>>>> ERROR  \"UHumanAnimInst\": Can't get Character reference"));
			return;
		}
		UnitOwner->AnimInstance = this;
		//OnAnimationFinish.BindUFunction(UnitOwner, FName("OnAnimationFinish"));
	}



	//** Get Param from Using Character
	FVector VSpeed = UnitOwner->GetVelocity();
	VelocitySpeed = VSpeed.Size();
	Direction = CalculateDirection(VSpeed, UnitOwner->GetActorRotation());

	//VelocitySpeed = UnitOwner->GetVelocity().Size();;
	//Direction = CalculateDirection(UnitOwner->GetVelocity(), UnitOwner->GetActorRotation());

	// ** LocomotionPose = UnitOwner->PoseLocomotion;	

	// +++ RotateTOP_Yaw = +++++++++++++++++;
	// +++ RotateTOP_Pich = ++++++++++++++++++;
	// +++ RotateTOP.X = 
	// +++ RotateTOP.Y = 
	// +++ RotateTOP_Last.X
	// +++ RotateTOP_Last.Y


	


}






void UHumanAnimInst::SetWeaponAnimType(EWeaponType _NewWeaponAnim)
{
	WeaponAnimType = _NewWeaponAnim;
}




void UHumanAnimInst::SetRotateSpeedHandle(TArray<float>& _RotateSpeedSwetcher)
{
	if (_RotateSpeedSwetcher.Num() < 7)
		return;
	HandlerRotateSpeed_Crawl = _RotateSpeedSwetcher[6];
	HandlerRotateSpeed_Crouch = _RotateSpeedSwetcher[5];
	HandlerRotateSpeed_RelaxMove = _RotateSpeedSwetcher[4];
	HandlerRotateSpeed_NormalMove = _RotateSpeedSwetcher[3];
	HandlerRotateSpeed_Run = _RotateSpeedSwetcher[2];
	HandlerRotateSpeed_Sprint = _RotateSpeedSwetcher[1];
	HandlerRotateSpeed_Fly = _RotateSpeedSwetcher[0];
}

void UHumanAnimInst::SetRotateAnimSpeed(float _NewSpeed)
{
	RotateAnimSpeedSide = _NewSpeed;
}


void UHumanAnimInst::TopRotateAngle(float DeltaTime)
{

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!        NEED Optimosation code
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//if (bDoRotate)
	//{
		//  =====================    TOP Body Rotate    ======================
		//if (UnitsTarget[0])
		//if (Target_Unit)
		//if (LOD == 0 && UnitsTarget[0])
	//if (ControlMode != EControlMode::PlayerPossed)
		////////||
		////////ControlMode == EControlMode::Player)
	//{
		// ** Calculate Point/Target for rotate     (Need "Task" or "Target_actor" or "Target_point")
		FVector LookPoint;
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		////if (IsPointToRotate)
		////{
		////	LookPoint = PointToRotate;
		////}
		////			else if (CurrentTask.AbilityIndex != -100)
		////			{
		////				if (CurrentTask.Target_actor)
		////					LookPoint = CurrentTask.Target_actor->GetActorLocation();
		////				else
		////					LookPoint = CurrentTask.Target_point;
		////			}
		////
		//else 
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		//////{
		//////	//if (IsTarget_Point)
		//////	if (PerformanceTask.Num() > 0)
		//////		LookPoint = PerformanceTask[0].Target_Point;
		//////	else if (Target_Unit)
		//////		LookPoint = PerformanceTask[0].Target_actor->GetActorLocation();
		//////	else
		//////		return;
		//////}








// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++





/*
		//  *******************************************************************
		//  ********************  Calculate rotate Angle  *********************
		//FRotator RotateToTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target_Unit->GetActorLocation());
		FRotator RotateToTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LookPoint);
		FRotator DeltaRotate = FRotator::MakeFromEuler(GetActorRotation().Euler() - RotateToTarget.Euler());//++FRotator DeltaRotate = GetActorRotation() - RotateToTarget; 
		if (DeltaRotate.Yaw < -180.f) DeltaRotate.Yaw = 360 + DeltaRotate.Yaw;//FMath::Abs();
		if (DeltaRotate.Yaw > 180.f) DeltaRotate.Yaw = -360 + DeltaRotate.Yaw;//FMath::Abs();



		if (RotateType_Locomotion == ERotateType_Locomotion::Rotate_FastFull)
		{
			if (DeltaRotate.Yaw < 5 && DeltaRotate.Yaw > -5)   //  Rotate
			//if (FMath::Abs(DeltaRotate.Yaw) < 5)   //  Rotate
			{
				RotateSide = 0;
			}
			else
			{
				if (DeltaRotate.Yaw > 5)    //  Rotate
				{
					RotateSide = -500.f;  // speed
				}
				else if (DeltaRotate.Yaw < -5)  //  Rotate
				{
					RotateSide = 500.f;  // speed
				}
			}
			AddActorWorldRotation(FRotator(0.f, RotateSide * DeltaTime, 0.f));
			return;
		}

		//  *******************************************************************
		//  *******************  Separt Calculate for TOP  ********************
		FRotator OldRotator = FRotator(TOP_RotatePich, TOP_RotateYaw, 5.5f);          //  5.5  -  Aim rotate speed
		FRotator Rot = FMath::RInterpTo(OldRotator, DeltaRotate, DeltaTime, 5.5f);

		// ************* Body and TOP rotate to target ***************
		if (RotateType_Locomotion == ERotateType_Locomotion::Rotate_Full)
		{

			//TOP_RotateYaw = FMath::Clamp(Rot.Yaw, -85.f, 85.f);
			//TOP_RotatePich = FMath::Clamp(Rot.Pitch, -85.f, 85.f);
			TOP_RotateYaw = 0; // Rot.Yaw;
			TOP_RotatePich = Rot.Pitch;

			if (DeltaRotate.Yaw < 5 && DeltaRotate.Yaw > -5)   //  Rotate
			//if (FMath::Abs(DeltaRotate.Yaw) < 5)   //  Rotate
			{
				RotateSide = 0;
			}
			else
			{
				if (DeltaRotate.Yaw > 90)    //  Rotate
				{
					RotateSide = -600.f;  // speed
				}
				else if (DeltaRotate.Yaw < -90)  //  Rotate
				{
					RotateSide = 600.f;  // speed
				}
				else if (DeltaRotate.Yaw > 50)  //  Rotate
				{
					RotateSide = -500.f;  // speed
				}
				else if (DeltaRotate.Yaw < -50)  //  Rotate
				{
					RotateSide = 500.f;  // speed
				}
				else if (DeltaRotate.Yaw >= 5)  //  Rotate
				{
					RotateSide = -400.f;  // speed
				}
				else if (DeltaRotate.Yaw <= -5)  //  Rotate
				{
					RotateSide = 400.f;  // speed
				}
				AddActorWorldRotation(FRotator(0.f, RotateSide * DeltaTime, 0.f));
			}

		}

		// ************* Rotate to corner angle-position and Hold thet(corner-angle-position) ***************

		else if (RotateType_Locomotion == ERotateType_Locomotion::Hold_IfMore)
		{
			//TOP_RotateYaw = FMath::Clamp(Rot.Yaw, -150.f, 150.f);
			//TOP_RotatePich = FMath::Clamp(Rot.Pitch, -150.f, 150.f);
			TOP_RotateYaw = Rot.Yaw;
			TOP_RotatePich = Rot.Pitch;

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!            Slow rotate to other side
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}

		// ************* rotate if angle more (onle nesesory rotate)  ***************

		else if (RotateType_Locomotion == ERotateType_Locomotion::Rotate_IfMore)
		{
			TOP_RotateYaw = Rot.Yaw;
			TOP_RotatePich = Rot.Pitch;

			if (TOP_RotateYaw > 90)  //  Rotate
			{
				RotateSide = -400.f;  // speed
				AddActorWorldRotation(FRotator(0.f, RotateSide * DeltaTime, 0.f));
			}
			else if (TOP_RotateYaw < -90)  //  Rotate
			{
				RotateSide = 400.f;  // speed
				AddActorWorldRotation(FRotator(0.f, RotateSide * DeltaTime, 0.f));
			}
			else
			{
				RotateSide = 0;
			}
		}

		// ************* rotate if angle more (Full rotate, straight to target)  ***************

		else if (RotateType_Locomotion == ERotateType_Locomotion::FullRotate_IfMore)
		{

			TOP_RotateYaw = Rot.Yaw;
			TOP_RotatePich = Rot.Pitch;

			// +++++++++++++++++++++++++++++++++++++++++++++++++++
		////////////////////	if (TOP_RotateYaw > 90 || TOP_RotateYaw < -90) bRotateAngleControl = true;
		////////////////////	if (bRotateAngleControl)
		////////////////////	{
		////////////////////		if (DeltaRotate.Yaw < 5 && DeltaRotate.Yaw > -5)
		////////////////////		{
		////////////////////			RotateSide = 0;
		////////////////////			bRotateAngleControl = false;
		////////////////////		}
		////////////////////		else
		////////////////////		{
		////////////////////			if (DeltaRotate.Yaw > 90)    //  Rotate
		////////////////////			{
		////////////////////				RotateSide = -600.f;  // speed  //-800 - slow hor fight
		////////////////////			}
		////////////////////			else if (DeltaRotate.Yaw < -90)  //  Rotate
		////////////////////			{
		////////////////////				RotateSide = 600.f;  // speed   // 800 - slow hor fight
		////////////////////			}
		////////////////////			else if (DeltaRotate.Yaw > 50)  //  Rotate
		////////////////////			{
		////////////////////				RotateSide = -500.f;  // speed  // -300 - slow hor fight
		////////////////////			}
		////////////////////			else if (DeltaRotate.Yaw < -50)  //  Rotate
		////////////////////			{
		////////////////////				RotateSide = 500.f;  // speed  // 300 - slow hor fight
		////////////////////			}
		////////////////////			else if (DeltaRotate.Yaw >= 5)  //  Rotate
		////////////////////			{
		////////////////////				RotateSide = -400.f;  // speed  //-150 - slow hor fight
		////////////////////			}
		////////////////////			else if (DeltaRotate.Yaw <= -5)  //  Rotate
		////////////////////			{
		////////////////////				RotateSide = 400;  // speed //150 - slow hor fight
		////////////////////			}
		////////////////////			AddActorWorldRotation(FRotator(0.f, RotateSide * DeltaTime, 0.f));
		////////////////////		}
		////////////////////	}
		////////////////////}

		////////////////////// ************* Rotate to corner angle-position but return to default when angle more ***************

		////////////////////else if (RotateType_Locomotion == ERotateType_Locomotion::Zero_IfMore)
		////////////////////{
		////////////////////	//////FRotator RotateToTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UnitsTarget[0]->GetActorLocation());
		////////////////////	//////FRotator DeltaRotate = FRotator::MakeFromEuler(GetActorRotation().Euler() - RotateToTarget.Euler());
		////////////////////	OldRotator = FRotator(TOP_RotatePich, TOP_RotateYaw_Last, 5.5f);          //  5.5  -  Aim rotate speed
		////////////////////	Rot = FMath::RInterpTo(OldRotator, DeltaRotate, DeltaTime, 5.5f);

		////////////////////	//TOP_RotateYaw = FMath::Clamp(Rot.Yaw, -85.f, 85.f);
		////////////////////	//TOP_RotatePich = FMath::Clamp(Rot.Pitch, -85.f, 85.f);

		////////////////////	TOP_RotateYaw_Last = Rot.Yaw;
		////////////////////	TOP_RotatePich = Rot.Pitch;

		////////////////////	if (Rot.Yaw > 110 || Rot.Yaw < -110)   //  Rotate
		////////////////////	{
		////////////////////		//TOP_RotateYaw = 0;
		////////////////////		TOP_RotateYaw = FMath::FInterpTo(TOP_RotateYaw, 0, DeltaTime, 5.5f);
		////////////////////	}
		////////////////////	else if (TOP_RotateYaw_Last > 5 || TOP_RotateYaw_Last < -5)   //  Rotate
		////////////////////	{
		////////////////////		//TOP_RotateYaw = TOP_RotateYaw_Last;
		////////////////////		TOP_RotateYaw = FMath::FInterpTo(TOP_RotateYaw, TOP_RotateYaw_Last, DeltaTime, 5.5f);
		////////////////////	}
		////////////////////	else TOP_RotateYaw = TOP_RotateYaw_Last;
		////////////////////}

		////////////////////// ************* don't rotate no bady, no TOP ***************

		////////////////////else if (RotateType_Locomotion == ERotateType_Locomotion::Not_Full)
		////////////////////{
		////////////////////	TOP_RotateYaw = 0.f;
		////////////////////	TOP_RotatePich = 0.f;
		////////////////////}
		}
*/
		// **********************************************************************************
		// *****************************  player half-rotate  *******************************
		// **********************************************************************************
		////////else // if (IsPOSSED)
		////////{
			////////if (!PlayerPAWN) return;

			// +++++++++++++++++++++++++++++++++++++++++++++++++++
			// **  TOP-rotate only. rotate just in cone, otherview TOP-rotate = 0  (Unit not ritate)  

			////////if (!bRotateAngleControl)
			////////{
			////////	FRotator RotateToTarget = PlayerPAWN->SpringArm->GetComponentRotation();//UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UnitsTarget[0]->GetActorLocation());
			////////	//FRotator RotateToTarget = PlayerPAWN->GetActorRotation();//UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UnitsTarget[0]->GetActorLocation());
			////////	FRotator DeltaRotate = FRotator::MakeFromEuler(GetActorRotation().Euler() - RotateToTarget.Euler());
			////////	if (DeltaRotate.Yaw < -180.f) DeltaRotate.Yaw = 360 + DeltaRotate.Yaw;//FMath::Abs();
			////////	if (DeltaRotate.Yaw > 180.f) DeltaRotate.Yaw = -360 + DeltaRotate.Yaw;//FMath::Abs();

			////////	FRotator OldRotator = FRotator(TOP_RotatePich, TOP_RotateYaw_Last, 9.5f);          //  5.5  -  Aim rotate speed
			////////	FRotator Rot = FMath::RInterpTo(OldRotator, DeltaRotate, DeltaTime, 9.5f);

			////////	//TOP_RotateYaw = FMath::Clamp(Rot.Yaw, -85.f, 85.f);
			////////	//TOP_RotatePich = FMath::Clamp(Rot.Pitch, -85.f, 85.f);

			////////	TOP_RotateYaw_Last = Rot.Yaw;
			////////	TOP_RotatePich = Rot.Pitch;

			////////	if (Rot.Yaw > 50 || Rot.Yaw < -50)   //  Rotate
			////////	{
			////////		//TOP_RotateYaw = 0;
			////////		TOP_RotateYaw = FMath::FInterpTo(TOP_RotateYaw, 0, DeltaTime, 7.5f);
			////////		// ** if player blockung
			////////		if (PlayerPAWN->RBM_Click)
			////////		{
			////////			// Rotate forward
			////////			bRotateAngleControl = true;
			////////		}
			////////	}
			////////	else if (TOP_RotateYaw_Last > 5 || TOP_RotateYaw_Last < -5)   //  Rotate
			////////	{
			////////		//TOP_RotateYaw = TOP_RotateYaw_Last;
			////////		TOP_RotateYaw = FMath::FInterpTo(TOP_RotateYaw, TOP_RotateYaw_Last, DeltaTime, 9.5f);
			////////	}
			////////	else TOP_RotateYaw = TOP_RotateYaw_Last;

			////////}

			////////else  // if (bRotateAngleControl == true)    // **    rotate to PAWN Direction
			////////{
			////////	TOP_RotateYaw = 0;
			////////	FRotator TargetRotate = PlayerPAWN->GetActorRotation();//FRotator RotateToTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UnitsTarget[0]->GetActorLocation());
			////////	//++FRotator DeltaRotate = FRotator::MakeFromEuler(GetActorRotation().Euler() - RotateToTarget.Euler());
			////////	FRotator DeltaRotate = GetActorRotation() - TargetRotate;
			////////	//UE_LOG(LogTemp, Warning, TEXT("ROT___ROT___ROT:     %f "), DeltaRotate.Yaw);
			////////	if (DeltaRotate.Yaw < -180.f) DeltaRotate.Yaw = 360 + DeltaRotate.Yaw;//FMath::Abs();
			////////	if (DeltaRotate.Yaw > 180.f) DeltaRotate.Yaw = -360 + DeltaRotate.Yaw;//FMath::Abs();
			////////	DeltaRotate.Normalize();

			////////	//FRotator OldRotator = FRotator(TOP_RotatePich, TOP_RotateYaw_Last, 9.5f);          //  5.5  -  Aim rotate speed
			////////	//FRotator Rot = FMath::RInterpTo(OldRotator, DeltaRotate, DeltaTime, 9.5f);

			////////	TOP_RotateYaw = 0.f;// Rot.Yaw;
			////////	//TOP_RotatePich = Rot.Pitch;
			////////	TOP_RotatePich = PlayerPAWN->SpringArm->GetComponentRotation().Pitch * (-1);


			////////	if (DeltaRotate.Yaw < 10 && DeltaRotate.Yaw > -10)
			////////	{
			////////		RotateSide = 0;
			////////		bRotateAngleControl = false;
			////////	}
			////////	else
			////////	{
			////////		if (DeltaRotate.Yaw > 90)    //  Rotate
			////////		{
			////////			RotateSide = -600.f;  // speed  //-600 - slow hor fight
			////////		}
			////////		else if (DeltaRotate.Yaw < -90)  //  Rotate
			////////		{
			////////			RotateSide = 600.f;  // speed   // 600 - slow hor fight
			////////		}

			////////		// ** Fast rotate
			////////		if (Moving_Side == ECombat_Side::none)// && !PlayerPAWN->AttachdUnitRotateToCamera)
			////////		{

			////////			if (DeltaRotate.Yaw > 50)  //  Rotate
			////////			{
			////////				RotateSide = -500.f;  // speed  // -300 - slow hor fight
			////////			}
			////////			else if (DeltaRotate.Yaw < -50)  //  Rotate
			////////			{
			////////				RotateSide = 500.f;  // speed  // 300 - slow hor fight
			////////			}
			////////			else if (DeltaRotate.Yaw >= 10)  //  Rotate
			////////			{
			////////				RotateSide = -400.f;  // speed  //-150
			////////			}
			////////			else if (DeltaRotate.Yaw <= -10)  //  Rotate
			////////			{
			////////				RotateSide = 400;  // speed //150
			////////			}
			////////		}
			////////		// ** Slow Rotate
			////////		else
			////////		{
			////////			if (DeltaRotate.Yaw > 90)    //  Rotate
			////////			{
			////////				RotateSide = -500.f;  // speed  //-600 - slow hor fight
			////////			}
			////////			else if (DeltaRotate.Yaw < -90)  //  Rotate
			////////			{
			////////				RotateSide = 500.f;  // speed   // 600 - slow hor fight
			////////			}
			////////			if (DeltaRotate.Yaw > 50)  //  Rotate
			////////			{
			////////				RotateSide = -300.f;  // speed  // -300 - slow hor fight
			////////			}
			////////			else if (DeltaRotate.Yaw < -50)  //  Rotate
			////////			{
			////////				RotateSide = 300.f;  // speed  // 300 - slow hor fight
			////////			}
			////////			else if (DeltaRotate.Yaw >= 10)  //  Rotate
			////////			{
			////////				RotateSide = -150.f;  // speed  //-150
			////////			}
			////////			else if (DeltaRotate.Yaw <= -10)  //  Rotate
			////////			{
			////////				RotateSide = 150;  // speed //150
			////////			}
			////////		}
			////////		AddActorWorldRotation(FRotator(0.f, RotateSide * DeltaTime, 0.f));
			////////	}

		////////}

	//}
	//}
}