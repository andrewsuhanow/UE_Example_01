// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "../TEST_Fraction/FractionSystem.h"

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"

#include "UnitAttitudeStatus.h"

#include "FractionSystem.generated.h"




USTRUCT(BlueprintType, Blueprintable)
struct FFractionUnit
{
	GENERATED_USTRUCT_BODY()

//public:
	UPROPERTY(EditAnywhere, Category = "AAA_Fraction")		uint8 GroupSubjectA;
	UPROPERTY(EditAnywhere, Category = "AAA_Fraction")		uint8 GroupSubjectB;
	UPROPERTY(EditAnywhere, Category = "AAA_Fraction")		EUnitAttitudeStatus Attitude;

	FFractionUnit() {};
	FFractionUnit(uint8 A, uint8 B, EUnitAttitudeStatus _Attitude);
};




UCLASS(Blueprintable, BlueprintType)
class OOO_API UFractionSystem : public UObject
{
	GENERATED_BODY()


public:

	UFUNCTION()					void Init(TArray<FFractionUnit>& _FractionsAttitude);

	UFUNCTION()					EUnitAttitudeStatus GetAttitude(TArray<FFractionUnit>& _FractionsAttitude, uint8 A, uint8 B);

	// **MEED +++ UFUNCTION()
	// **NEED +++	void SetAttitude(int32 from, int32 to, int32 Attitude);
	 
	UFUNCTION()
		void U_LogFraction();


};
 