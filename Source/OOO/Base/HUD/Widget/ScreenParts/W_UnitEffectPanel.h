
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "W_UnitEffectPanel.generated.h"


//class UHorizontalBox;  
class UScrollBox;
class USizeBox;

UCLASS()
class OOO_API UW_UnitEffectPanel : public UUserWidget
{
	GENERATED_BODY()

			   

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;



	   	 

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowEffectPanel(class AUnit* _Unit);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void HideEffectPanel();




	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateEffectPanel(class AUnit* _Unit);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddCellToEffectPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture);

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		USizeBox* SizeBox_EffectPanel;										
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget))	UHorizontalBox* FastPanelHorizontalBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UScrollBox* ScrollBox_EffectPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class UW_Slot*> SlotObj;



};

