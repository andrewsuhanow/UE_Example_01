
#pragma once

// #include "Base/Controller/Fraction/Struct/PointTaskAgent.h"

//#include "CoreMinimal.h"



#include "PointTaskAgent.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FPointTaskAgent
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()


	FPointTaskAgent() {};


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class AUnit*> TaskResolutionUnits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		FVector TaskPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float LastListenTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float NoisLoud = 0.f;
};
