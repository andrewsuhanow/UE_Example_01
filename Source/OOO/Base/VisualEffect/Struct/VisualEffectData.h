
#pragma once

// #include "Base/VisualEffect/Struct/VisualEffectData.h"

//#include "CoreMinimal.h"

#include "VisualEffectData.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FVisualEffectData
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class UNiagaraSystem* NiagaraEffect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		FName Socket = FName("none");

	//---UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
	//---	bool UseOnAnimNotifyHit = false;

	//--UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
	//--	bool IsPlayingOnlyOneStep = false;
};
