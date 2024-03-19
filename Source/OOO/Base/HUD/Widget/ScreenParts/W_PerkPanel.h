
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "W_PerkPanel.generated.h"


class UScrollBox;
class USizeBox;


UCLASS()
class OOO_API UW_PerkPanel : public UUserWidget
{
	GENERATED_BODY()

			   

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;




public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowPerkPanel(class AUnit* _Unit);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdatePerkPanel(class AUnit* _Unit);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddCellToPerkPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture);

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		USizeBox* PerkPanelSizeBox;					// ** Border size					//  SzBox_Inventory
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UScrollBox* PerkPanelScroll;													//  Scroll_Inventory

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class UW_Slot*> SlotObj;
};

