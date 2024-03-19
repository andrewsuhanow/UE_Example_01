
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "W_FastPanel.generated.h"


class UHorizontalBox;  //#include "Components/VerticalBox.h"
//class UScrollBox;
class USizeBox;

UCLASS()
class OOO_API UW_FastPanel : public UUserWidget
{
	GENERATED_BODY()

			   

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;



	   	 

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowFastPanel(class AUnit* _FastPanelUnit);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void HideFastPanel();

/*
	UFUNCTION(BlueprintCallable, Category = "OOO")		
		void SelectFastPanelSlot(int32 _SlotIndex, bool _IsPermanent);

	UFUNCTION(BlueprintCallable, Category = "OOO")		
		void DeselectFastPanelSlot(int32 _SlotIndex, bool _IsPermanent);
*/

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateFastPanel(class AUnit* _FastPanelUnit);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddCellToFastPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture);

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		USizeBox* FastPanelSizeBox;					// ** Border size					
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UHorizontalBox* FastPanelHorizontalBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class UW_Slot*> SlotObj;



};

