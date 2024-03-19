
#pragma once



// #include "Base/Ability/Enum/AbilityTraseForm.h"

//#include "CoreMinimal.h"




UENUM(BlueprintType, Blueprintable)
enum class EAbilityTraseForm : uint8
{
	//---ApplayEffectToUnit = 0,
	SpawnAgentAtLoc = 0,
	FlyAgentToGoal,
	ConeInFront,



	MAX
};
