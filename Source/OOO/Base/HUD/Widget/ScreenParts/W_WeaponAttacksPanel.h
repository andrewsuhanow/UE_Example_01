
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
		void ShowAttacksWpnPanel(class AUnit* _Unit, TArray<UTexture2D*>& _AttackIcon,
									int32& _SelectIndex, int32& _PermanentIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void HideAttacksWpnPanel();
		
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateAttacksWpnPanel(class AUnit* _Unit, TArray<UTexture2D*>& _AttackIcon,
									int32& _SelectIndex, int32& _PermanentIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddCellToWeaponAttacksPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture);

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		USizeBox* WeaponAttacksPanelSizeBox;				
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UHorizontalBox* WeaponAttacksPanelGorzBox;									

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class UW_Slot*> SlotObj;
};

