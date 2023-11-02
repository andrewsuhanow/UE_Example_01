
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

//#include "../gr_TEST_Item/Struct/ItemData.h"
//#include "../gr_TEST_WeaponComponent/Enum/EWeapon_Type.h"





#include "W_Inventory.generated.h"


class UVerticalBox;  //#include "Components/VerticalBox.h"
class UScrollBox;
class USizeBox;
class UCanvasPanel;		// #include "Components/CanvasPanel.h"
//class UButton;    // #include "Components/Button.h"

UCLASS()
class OOO_API UW_Inventory : public UUserWidget
{
	GENERATED_BODY()





public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;




public:


	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowInventory(class AUnit* _Unit, ABaseGameMode* BGameMode);



	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateInventory(class AUnit* _Unit, ABaseGameMode* BGameMode);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddSlotsRowAtOnBottom(class AUnit* _Unit, ABaseGameMode* _GameMode, int32 _Row, int32 _CollCount, float _SlotSize);



public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		USizeBox* InventorySizeBox;			// ** Border size					//  SzBox_Inventory
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UScrollBox* InventoryScroll;											//  Scroll_Inventory
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UCanvasPanel* InventoryCanva;		// ** main container of slots		//  CanvaPanel_Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	
		TArray<class UW_Slot*> SlotObj;



};

