
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "W_WeaponAttacksPanel.generated.h"


class UHorizontalBox;
class USizeBox;


UCLASS()
class OOO_API UW_WeaponAttacksPanel : public UUserWidget
{
	GENERATED_BODY()

			   

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;




public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowWeaponAttacksPanel(class AUnit* _Unit, ABaseGameMode* _GameMode);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void HideWeaponAttacksPanel();
		
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateWeaponAttacksPanel(class AUnit* _Unit, class ABaseGameMode* _GameMode);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddCellToWeaponAttacksPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture);

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		USizeBox* WeaponAttacksPanelSizeBox;				
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UHorizontalBox* WeaponAttacksPanelGorzBox;									

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class UW_Slot*> SlotObj;
};

