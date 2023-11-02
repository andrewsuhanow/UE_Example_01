
#pragma once

#include "../Enum/DailyBhvrPointPos.h"
//----#include "Engine/DataTable.h"

#include "../../../WorldObject/WayPoint/WayPoint.h"

#include "DailyBhvrData.generated.h"

USTRUCT(Blueprintable, BlueprintType) 
struct FDailyBhvrData
{
	// ** GENERATED_BODY()
	GENERATED_USTRUCT_BODY()
	
public:

	// ** Point-Actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_DailyBehaviorTask")
		AWayPoint* PointActor;
	// ** WayPoint-Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_DailyBehaviorTask")
		FName WayPointTag = FName("none");

	// ** Time (Start-/-End)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_DailyBehaviorTask")
		int32 StartTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_DailyBehaviorTask")
		int32 EndTime = 0;

	// ** Standing-Type (with Point-Location)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_DailyBehaviorTask")
		// ** PointPosition  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
		EDailyBhvrPointPos DailyBhvrPointPos = EDailyBhvrPointPos::on_point_rotata_forward;

	// ** Offset from point (if negative number (-X), it means randon from 0 to +X)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_DailyBehaviorTask")
		float Shifting = 0;		

	// ** 0 - Transit(no Act);	 -1 - one-time;    -8 - Loop;     n - secconds-time	  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_DailyBehaviorTask")
		int32 DurationTypeAndTime = 3;				  

	// ** Action-Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_DailyBehaviorTask")
		FName ActionName = FName("none");

	// ** Anim-Montager
	UPROPERTY(EditAnywhere, Category = "OOO_DailyBehaviorTask")
		UAnimMontage* MainAnimMontage;
	UPROPERTY(EditAnywhere, Category = "OOO_DailyBehaviorTask")
		UAnimMontage* AnimMontage_Before;
	UPROPERTY(EditAnywhere, Category = "OOO_DailyBehaviorTask")
		UAnimMontage* AnimMontage_After;


};
