
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../Struct/DailyBhvrData.h"

#include "DailyBhvrQueue.generated.h"


UCLASS(BlueprintType, Blueprintable)
class OOO_API UDailyBhvrQueue : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		TArray<FDailyBhvrData> DailyBhvrTaskDT;
 
	UFUNCTION()		
		void Init();

};
