
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "../../../Inventory/Enum/SlotType.h"

#include "W_Slot.generated.h"

//class UButton;
class UImage;
class UTextBlock;
class USizeBox;


UCLASS()
class OOO_API UW_Slot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY()
		bool IsFree = true;

	///+++UPROPERTY()
	///+++	class UW_Inventory* W_Parent;

	UPROPERTY()
		class AUnit* SelectUnit;


public:

	// ** MainPanel, GlobalPanel, EquipPanel, FastPanel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		ESlotType PanelTypeFix = ESlotType::none;

	// ** index-Container = index-W_Slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		int32 IndexInContainer = -1;


public:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, 
																		UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, 
																		  UDragDropOperation* InOperation) override;
	  
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
																		UDragDropOperation* InOperation)  override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)  override;

	UFUNCTION()
		void InventoryDropPerformance(const UW_Slot* ItemSlotUnder, UW_DropSlot* ItemSlotDragg);
	UFUNCTION()
		int32 CheckPlaceUnder(const class UW_Slot* ItemSlotUnder, const class UW_DropSlot* ItemSlotDraging);
	  

	 
public:
	   	  	  

	// ** item image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* ImgItem = nullptr;
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetImage(UTexture2D* ItemImage = nullptr);


	// ** Background Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* BackgroungImage;
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetBackgroundImage(UTexture2D* _BackgroundImage = nullptr);





	


	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
		USizeBox* SzBox;
	
	// ** SelectImage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* SelectImage1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* SelectImage2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* SelectImage3;
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SelectButton(int32 SelectingType, bool deselect = true);


	// ** Slot Size   (Set in BP-Editor OR in Sctipt<init>)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float slotWidth = 128;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float slotheight = 128;
	
};
