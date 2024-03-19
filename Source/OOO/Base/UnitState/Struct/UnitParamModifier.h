
// #include "Base/UnitState/Struct/UnitParamModifier.h"

#pragma once

#include "../Enum/UnitParam.h"

#include "UnitParamModifier.generated.h"


#define ONCE -1
#define ONGOING 0

USTRUCT(Blueprintable, BlueprintType)
struct FUnitParamModifier
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()

public:
	
	// ** ONCE:		-1 (Once action)
	// ** ONGOING: 0 (Using modifier while requirement active)
	// ** 1...x:	  (Using modifier while time (rounds count))
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		int32 ModifierType = ONCE;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		EUnitParam UnitParam = EUnitParam::none;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		float Value = 10.f;

	// ** Set or Mod
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
		bool IsParamSet = false;



	
};