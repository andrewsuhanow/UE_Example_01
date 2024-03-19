
// #include "Base/UnitEffect/Struct/UnitEffectSlotDT.h"

#pragma once

#include "UnitEffectDT.h"

//-----#include "../Enum/UnitEffectType.h"

#include "UnitEffectSlotDT.generated.h"



//#define SLOT_IS_EMPTY FName("SLOT_IS_EMPTY");

USTRUCT(Blueprintable, BlueprintType)
struct FUnitEffectSlotDT : public FUnitEffectDT
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()


public:

	FUnitEffectSlotDT& CastSlotEffectFromUnitEffect(const FUnitEffectDT& _Other);

public:
	
	UPROPERTY()
		int32 IndexInUnit = -1;

	UPROPERTY()
		int32 FullRoundDuration = 0;

	UPROPERTY()
		bool IsSpentFirstRound = true;

	UPROPERTY()
		bool IsFirstTime = true;

	bool Init(class AUnit* _UnitOwner);

	void Continue(class AUnit* _UnitOwner);

	void Finish();

	void Cancel();





	//FUnitEffectDT& operator=(const FUnitEffectDT& _Other);
	
	
};