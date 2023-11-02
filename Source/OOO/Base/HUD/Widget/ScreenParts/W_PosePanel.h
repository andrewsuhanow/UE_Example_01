
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "W_PosePanel.generated.h"




UCLASS()
class OOO_API UW_PosePanel : public UUserWidget
{
	GENERATED_BODY()

			   

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	   	 



	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowInventory(class AUnit* _Unit, ABaseGameMode* BGameMode);
};

