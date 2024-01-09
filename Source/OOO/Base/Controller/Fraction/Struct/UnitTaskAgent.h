
#pragma once

// #include "Base/Controller/Fraction/Struct/UnitTaskAgent.h"

//#include "CoreMinimal.h"



#include "UnitTaskAgent.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FUnitTaskAgent
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()


	FUnitTaskAgent() {};


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class AUnit*> TaskResolutionUnits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class AUnit* TaskUnit;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		//UnitStatusByParam

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		//UnitRangetOrContact

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float LastSeenLocation = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float LastSeenTime = 0.f;

};
