
// #include "Base/UnitEffect/UnitEffectRealizer.h"

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Struct/UnitEffectSlotDT.h"

#include "UnitEffectRealizer.generated.h"


UCLASS()
class OOO_API UUnitEffectRealizer : public UObject
{
	GENERATED_BODY()
	
public:

#if WITH_EDITORONLY_DATA  // #if WITH_EDITOR 

	// ** Desctiption "UAbilityDT.AbilityStep.UnitEffectDT"
	// ** UAbilityDT->PostEditChangeChainProperty()
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<FString> HELPER__UnitEffectParamDescription;
	// ** UUnitEffectRealizer::UUnitEffectRealizer()
	// ** {
	// ** 	HELPER__UnitEffectParamDescription.Add(FString("Requitr: xxxxxxPARAM[0]"));
	// ** 	HELPER__UnitEffectParamDescription.Add(FString("Requitr: xxxxxxPARAM[1]"));
	// ** }


#endif

public:

	UFUNCTION()		virtual bool InitEffect(FUnitEffectSlotDT& _UnitEffectSlotDT,
										class AUnit* _UnitOwner) { return false; };

	UFUNCTION()		virtual bool ContinueEffect(FUnitEffectSlotDT& _UnitEffectSlotDT,
										class AUnit* _UnitOwner) { return false; };

	UFUNCTION()		virtual void FinishEffect(FUnitEffectSlotDT& _UnitEffectSlotDT,
										class AUnit* _UnitOwner) {};

	UFUNCTION()		virtual void CancelEffect(FUnitEffectSlotDT& _UnitEffectSlotDT,
										class AUnit* _UnitOwner) {};
};
