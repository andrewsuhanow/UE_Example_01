
#pragma once

//#include "Base/Unit/Struct/PoseLocomotion.h"
//#include "Enum/EPose_Locomotion.h"

//#include "CoreMinimal.h"

#include "PoseLocomotion.generated.h"

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
 
USTRUCT(Blueprintable, BlueprintType)
struct FPoseLocomotion
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_LocomotPoseButton")
		EPose Pose = EPose::Stand;

	// ** if "-1" =>> pose exist bun don't move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_LocomotPoseButton")
		float Speed = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_LocomotPoseButton")
		UTexture2D* PoseImage;

};