
#pragma once

//#include "Base/Unit/Struct/PoseLocomotion.h"


//#include "CoreMinimal.h"

#include "../Enum/UnitPose.h"

#include "PoseLocomotion.generated.h"

// (---------------------------------)
/*
UENUM(BlueprintType, Blueprintable)
enum class EPose : uint8
{	
	Crawl,
	Crouch,
	StandRelax, // slow walk
	Stand, // walk
	run,  
	Sprint,
	Fly
};
 */



USTRUCT(Blueprintable, BlueprintType)
struct FPoseLocomotion
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_LocomotPoseButton")
		EUnitPose Pose = EUnitPose::RelaxMove;

	// ** if "-1" =>> pose exist but don't move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_LocomotPoseButton")
		float MoveSpeed = 0;

	// ** 150.f, 300.f, 600.f
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_LocomotPoseButton")
		float RotateSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_LocomotPoseButton")
		UTexture2D* PoseImage;

	EUnitPose GetPoseType() const { return Pose; };

	float GetPoseMoveSpeed() const { return MoveSpeed; };

	void SetPoseMoveSpeed(float _MoveSpeed) { MoveSpeed = _MoveSpeed; };

	float GetPoseRotateSpeed() const { return RotateSpeed; };

	void SetPoseRotateSpeed(float _RotateSpeed) { RotateSpeed = _RotateSpeed; };
};