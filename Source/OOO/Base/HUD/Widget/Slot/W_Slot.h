
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../../../Inventory/Enum/SlotType.h"

#include "InputCoreTypes.h"	// ** EKey
//#include "Engine/Source/Runtime/InputCore/Classes/InputCoreTypes.h"

#include "W_Slot.generated.h"

class UImage;
class UTextBlock;
class USizeBox;
class UTextBlock;
class UProgressBar;


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

	// ** Slot Size   (Set in BP-Editor OR in Sctipt<init>)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float SlotWidth = 64;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		float SlotHeight = 64;

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* DurationBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		USizeBox* SzBoxImages;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* TextItemCount;

	// ** item image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* ImgItem = nullptr;
	// ** Background Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* BackgroungImage;
	// ** SelectImage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* PermanentSelectImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* MaintSelectImg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* SelectorImage3;



	




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
	  





	// **********************    Button Click    **********************
public:

	UFUNCTION()
		void MsClickInstantRight();
	UFUNCTION()
		void MsClickInstantLeft();
	UFUNCTION()
		void MsClickInstantMiddle();
	
	
	UFUNCTION()
		void MsClickLongRight();
	UFUNCTION()
		void MsClickLongLeft();
	UFUNCTION()
		void MsClickLongMiddle();

	

	// ** Mouse long click
public:

	UPROPERTY()
		float MousClickDurationMax = 0.5f;
	UPROPERTY()
		float CurrMousClickDuration = 0;
	UPROPERTY()
		FKey CurrClickedMouseKey;
	UPROPERTY()
		FTimerHandle TH_MousClickDuration;
	UFUNCTION()
		void MousClickDurationLoop();



	// **********************     Button Set patram    **********************
public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetItemCount(int32 RealCount, int32 MaxCount, float FontSize = 15.f);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetBarProgress(float _curr = 0.f, float _max = 1.f);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetProgressVisibility(bool _IsVisible);


	UFUNCTION()
		void SetSlotSize();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetSlotParam(int32 _IndexInContainer,
			UTexture2D* _ItemImage, UTexture2D* _BackgroundImage,
			float _SlotWidth = -1.f, float _SlotHeight = -1.f,
			float _ImageWidth = -1.f, float _ImageHeight = -1.f,
			float _TranslationX = 0, float _TranslationY = 0,
			ESlotType _PanelTypeFix = ESlotType::none);

};
