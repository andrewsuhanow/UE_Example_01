
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "W_WeaponPanel.generated.h"

class UW_Slot;

class UHorizontalBox;
class USizeBox;
class UButton;
class UImage;

UCLASS()
class OOO_API UW_WeaponPanel : public UUserWidget
{
	GENERATED_BODY()

			   

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;


public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowWeaponPanel(class AUnit* _Unit,
			int32& _WeaponSlotIndex,
			ESlotType& _WeaponSlotType,
			UTexture2D*& _WeaponSlotTexture);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void HideWeaponPanel();
		
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void OpenWpnChangePanel(class AUnit* _Unit,
			TArray<int32>& _WeaponSlotsIndex,
			TArray<ESlotType>& _WeaponSlotsType,
			TArray<UTexture2D*>& _WeaponSlotsTexture);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void CloseWpnChangePanel();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateWeaponPanel(class AUnit* _Unit, class ABaseGameMode* _GameMode,
			TArray<int32>& _WeaponSlotsIndex,
			TArray<ESlotType>& _WeaponSlotsType,
			TArray<UTexture2D*>& _WeaponSlotsTexture);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddCellToWeaponPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture);

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		USizeBox* WeaponPanelSizeBox;					
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UHorizontalBox* WeaponPanelGorzBox;	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<UW_Slot*> SlotObj;


	// ** Button Activate Weapon
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UButton* ActiveWeaponButton;
	UFUNCTION()												void ActiveWeaponButtonCall();
	UPROPERTY(EditAnywhere, meta = (BindWidget))			UImage* ActivateWeaponImg = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))			UImage* ActivateWeaponBackImg = nullptr;

	// ** Button Select Weapon
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UButton* SelectWeaponButton;
	UFUNCTION()												void SelectWeaponButtonCall();
	UPROPERTY(EditAnywhere, meta = (BindWidget))			UImage* ChangeWeaponImg = nullptr;
	UPROPERTY(EditAnywhere, meta = (BindWidget))			UImage* ChangeWeaponBackImg = nullptr;

	// ** indexIn-Weapon-Container
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		int32 IndexInContainer = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class AUnit* Unit;
	
	
};

