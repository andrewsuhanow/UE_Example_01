
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

//#include "../gr_TEST_Item/Struct/ItemData.h"
//#include "../gr_TEST_WeaponComponent/Enum/EWeapon_Type.h"





#include "W_GlobalInventory.generated.h"


//class UVerticalBox;  //#include "Components/VerticalBox.h"
class UScrollBox;
class USizeBox;
//class UCanvasPanel;		// #include "Components/CanvasPanel.h"
//class UButton;    // #include "Components/Button.h"

UCLASS()
class OOO_API UW_GlobalInventory : public UUserWidget
{
	GENERATED_BODY()





public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;




public:


	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowInventory(class UInventoryComponent* _Inventor);



	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateInventory(class UInventoryComponent* _Inventor, class ABaseGameMode* _GameMode);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddCellToGlobalInv(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture);

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		USizeBox* InventorySizeBox;					// ** Border size					//  SzBox_Inventory
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UScrollBox* InventoryScroll;													//  Scroll_Inventory
	//------------UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UCanvasPanel* InventoryCanva;		// ** main container of slots		//  CanvaPanel_Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	
		TArray<class UW_Slot*> SlotObj;



};

