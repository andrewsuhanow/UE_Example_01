
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../../../Item/Struct/ItemDT.h"

#include "W_EquipPanel.generated.h"


class USizeBox;
class UCanvasPanel;		// #include "Components/CanvasPanel.h"
class UW_Slot;



UCLASS()
class OOO_API UW_EquipPanel : public UUserWidget
{
	GENERATED_BODY()

			   

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UCanvasPanel* EquipPanelCanva;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* contact_wpn_big_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* contact_wpn_small_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* range_wpn_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* pistol_slot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* heavy_amunition_slot;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* cup_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* armour_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* clothes_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* collar_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* braslet1_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* braslet2_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* ring1_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* ring2_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* ring3_slot;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UW_Slot* ring4_slot;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")		//  @@@@@@@@@@@@@777777777777777777777777777  FStruct*
		TArray<class UW_Slot*> WeaponSlotsArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class UW_Slot*> ArmorSlotsArray;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_BigContactWpn = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_SmallContactWpn = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_RangeWpn = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_Pistol = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_Cup = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_Armor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_Clothes = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_Collar = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_Braslet = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_Ring = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_HeavyStuff = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<UTexture2D*> EquipSlotsDefaultTextureArray;

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowEquipPanel(class AUnit* _Unit);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateEquipPanel(class AUnit* _Unit);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetEquipSlotParam(class AUnit* _Unit,
			ESlotType ToEquipSlotType, int32 unitSlotIndex,
			UTexture2D* _MainInvertorySlotTexture,
			UTexture2D* _ItemSlotTexture);

};

