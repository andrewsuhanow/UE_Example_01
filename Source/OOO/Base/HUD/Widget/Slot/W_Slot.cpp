
// #include "Base/HUD/Widget/Slot/W_Slot.h"
#include "W_Slot.h"

#include "../../../Unit/Base/Unit.h"

 #include "../../../HUD/BaseHUD.h"

#include "../../../Ability/AbilityDT.h"

#include "Blueprint/WidgetBlueprintLibrary.h"   // UWidgetBlueprintLibrary::DetectDragIfPressed()

#include "Components/SizeBox.h"
#include "Components/TextBlock.h" 
#include "Components/Image.h"
#include "Components/ProgressBar.h"
//--777--#include "Components/SizeBoxSlot.h"

//#include "Kismet/GameplayStatics.h"   //   GetAllActorsOfClass




void UW_Slot::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	// ** Set Slot SIZE
	//SzBox->SetHeightOverride(20.f);
	//SzBox->SetWidthOverride(20.f);
	//SetSlotSize();

	//DurationBar->SetVisibility(ESlateVisibility::Collapsed);
	DurationBar->SetPercent(0.7f);
}



void UW_Slot::NativeConstruct()
{
	Super::NativeConstruct();

	MaintSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	
	PermanentSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	
	SelectorImage3->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	
	TextItemCount->SetFont(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 24.f));
	// ** TextItemCount->Font.Size = 24;
	//TextItemCount->SetColorAndOpacity(FSlateColor(FLinearColor(0.3f, 0.05f, 0.01f, 1.0f)));
	TextItemCount->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.9f, 0.0f, 1.0f)));
	TextItemCount->SetJustification(ETextJustify::Right);

	SetSlotSize();

}















// ****************************************************************
// **********************    Button Click    **********************
// ****************************************************************

void UW_Slot::MsClickInstantRight()
{
	UE_LOG(LogTemp, Log, TEXT("MOUSE CLICK    ___InstantRight  "));
}
void UW_Slot::MsClickInstantLeft()
{
	SelectUnit->ActivateFastPanelAbilBtn(PanelTypeFix, IndexInContainer,  false);
	//----UE_LOG(LogTemp, Log, TEXT("MOUSE CLICK    ___InstantLeft  "));
}
void UW_Slot::MsClickInstantMiddle()
{
	UE_LOG(LogTemp, Log, TEXT("MOUSE CLICK    ___InstantMiddle  "));
}


void UW_Slot::MsClickLongRight()
{
	UE_LOG(LogTemp, Log, TEXT("MOUSE CLICK    ___LongRight  "));
}
void UW_Slot::MsClickLongLeft()
{
	SelectUnit->ActivateFastPanelAbilBtn(PanelTypeFix, IndexInContainer, true);
	//---UE_LOG(LogTemp, Log, TEXT("MOUSE CLICK    ___LongLeft  "));
}
void UW_Slot::MsClickLongMiddle()
{
	UE_LOG(LogTemp, Log, TEXT("MOUSE CLICK    ___LongMiddle  "));
}





// ****************************************************************
// **********************     Button Set patram    **********************
// ****************************************************************
void UW_Slot::SetSlotParam(int32 _IndexInContainer,
	UTexture2D* _ItemImage, UTexture2D* _BackgroundImage,
	float _SlotWidth, float _SlotHeight, 
	float _ImageWidth, float _ImageHeight,
	float _TranslationX, float _TranslationY,
	ESlotType _PanelTypeFix)
{

	if (_ItemImage)
	{
		ImgItem->SetBrushFromTexture(_ItemImage, false);
		ImgItem->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		ImgItem->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	}
	if (_BackgroundImage)
	{
		BackgroungImage->SetBrushFromTexture(_BackgroundImage, false);
		BackgroungImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		BackgroungImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	}

	if (_IndexInContainer >= 0)
	{
		IndexInContainer = _IndexInContainer;
	}

	if (_SlotWidth != -1)
	{
		SlotWidth = _SlotWidth;
		SzBoxImages->SetWidthOverride(_SlotWidth);
		//SzBox->SetWidthOverride(_SlotWidth);
	}
	if (_SlotHeight != -1)
	{
		SlotHeight = _SlotHeight;
		SzBoxImages->SetHeightOverride(_SlotHeight);
		//SzBox->SetHeightOverride(_SlotHeight);
	}
	


	if (_ImageWidth != -1 || _ImageHeight != -1)
	{
		SzBoxImages->SetWidthOverride(_ImageWidth);
		SzBoxImages->SetHeightOverride(_ImageHeight);

		// ** ImgItem->SetBrushSize(FVector2D(_ImageWidth, _ImageHeight));
		// ** BackgroungImage->SetBrushSize(FVector2D(_ImageWidth, _ImageHeight));
	}
	else
	{
		SzBoxImages->SetWidthOverride(SlotWidth);
		SzBoxImages->SetHeightOverride(SlotHeight);

		// ** ImgItem->SetBrushSize(FVector2D(SlotWidth, SlotHeight));
		// ** BackgroungImage->SetBrushSize(FVector2D(SlotWidth, SlotHeight));
	}
	
	if (_TranslationX != 0 || _TranslationY != 0)
	{
		SzBoxImages->SetRenderTranslation(FVector2D(_TranslationX, _TranslationY));
	}
	else
	{
		SzBoxImages->SetRenderTranslation(FVector2D(0.f, 0.f));
	}

	if (_PanelTypeFix != ESlotType::none)
	{
		PanelTypeFix = _PanelTypeFix;
	}


}




void UW_Slot::SetItemCount(int32 RealCount, int32 MaxCount, float FontSize)
{
	FString count	 = FString("");
	FString countMax = FString("");
	FString slash = FString("");
	if (MaxCount > 1)
	{
		countMax = FString::FromInt(MaxCount);
		slash = FString("/");
		count = RealCount > 0 ? FString::FromInt(RealCount) : FString("");
	}

	

	TextItemCount->SetText(FText::FromString(count + slash + countMax));
	//TextItemCount->Font.Size = FontSize;
	TextItemCount->SetFont(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), FontSize));
}

void UW_Slot::SetBarProgress(float _curr, float _max)
{
	if (_max == 0.f)
		return;

	float val = _curr / _max;

	if (val <= 0.f)
		SetProgressVisibility(false);
	else
	{
		DurationBar->SetPercent(val);
		SetProgressVisibility(true);
	}
}

void UW_Slot::SetProgressVisibility(bool _IsVisible)
{
	if (_IsVisible)
	{
		DurationBar->SetVisibility(ESlateVisibility::Visible);	// ** Visible,  Hidden,  Collapsed
	}
	else
	{
		DurationBar->SetVisibility(ESlateVisibility::Hidden);
	}
}
/*
void UW_Slot::SelectButton(int32 SelectingType, bool deselect)
{
	if (deselect == false)
	{
		switch (SelectingType)
		{
			case 1:
				SelectImage1->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
				break;
			case 2:
				SelectImage2->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
				break;
			case 3:
				SelectImage3->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
				break;
		}
	}
	else
	{
		// .............SHOW
	}
}
*/


void UW_Slot::SetSlotSize()
{
	SzBoxImages->SetHeightOverride(SlotWidth);
	SzBoxImages->SetWidthOverride(SlotWidth);
	//SzBox->SetHeightOverride(SlotWidth);
	//SzBox->SetWidthOverride(SlotWidth);

}


// ***************************************************************************
// ******************************    Dg & Dp    ******************************

FReply UW_Slot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	UE_LOG(LogTemp, Log, TEXT("WWWWWWWWWWWWWW  Mouse Up:   %i"), IndexInContainer);


	// ** Check long click checking
	GetWorld()->GetTimerManager().ClearTimer(TH_MousClickDuration);
	if (CurrMousClickDuration > MousClickDurationMax)
	{
		return FReply::Handled();
	}
	else
	{
		// ** Init Instant click
		if (CurrClickedMouseKey == EKeys::LeftMouseButton)
		{
			MsClickInstantLeft();
		}
		else if (CurrClickedMouseKey == EKeys::RightMouseButton)
		{
			MsClickInstantRight();
		}
		else if(CurrClickedMouseKey == EKeys::MiddleMouseButton)
		{
			MsClickInstantMiddle();
		}
	}
	CurrMousClickDuration = 0.f;




	//////////////	bool IsInvertoryShown = false;
	//////////////	bool IsLootInvertoryShown = false;
	//////////////	bool IsGlobalInvertoryShown = false;
	//////////////	bool IsEquipPaneShown = false;
	//////////////	bool IsLootEquipPanelShown = false;
	//////////////	bool IsFastPanelShown = false;
	//////////////	bool IsPerkPanelShown = false;


	// ++++
	if (PanelTypeFix == ESlotType::unit_effect)
	{
		SelectUnit->BreakUnitEffect(IndexInContainer);
	}



/*
// *** TEST --------------
	if (PanelTypeFix == ESlotType::main_inv)
	{
		bool is = SelectUnit->IsMainInventorySlotEmpty(IndexInContainer);
		FItemDT *itm = SelectUnit->GetItemRefFromMainInventory(IndexInContainer);
		SelectUnit->RemoveItemFromMainInventory(IndexInContainer);
		IndexInContainer = -1;
		is = true;
		is = true;

		ABaseHUD* HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			if (HUD->IsInvertoryShown)
			{
				HUD->ShowInventory(SelectUnit->Inventory);
			}
		}

	}
	if (PanelTypeFix == ESlotType::global_inv)
	{
		bool is = SelectUnit->IsGlobalInventorySlotEmpty(IndexInContainer);
		FItemDT* itm = SelectUnit->GetItemRefFromGlobalInventory(IndexInContainer);
		SelectUnit->RemoveItemFromGlobalInventory(IndexInContainer);
		IndexInContainer = -1;
		is = true;
		is = true;

		ABaseHUD* HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			if (HUD->IsGlobalInvertoryShown)
			{
				HUD->ShowGlobalInventory(SelectUnit->Inventory);
			}
		}
	}
	if (PanelTypeFix == ESlotType::fast_panel)
	{
		FItemDT *RefItemDT = nullptr;
		UAbilityDT* RefAbilityType;

		bool is = SelectUnit->GetFastPanelSlotElement(IndexInContainer, RefItemDT, RefAbilityType);
		SelectUnit->RemoveElementFromFastPanel(IndexInContainer);
		//IndexInContainer = -1;
		//is = true;
		//is = true;


		SelectUnit->ActivateFastPanelAbilBtn(IndexInContainer);




		ABaseHUD* HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			if (HUD->IsFastPanelShown)
			{
				HUD->ShowFastPanel(SelectUnit);
			}
		}
	}
	if (PanelTypeFix == ESlotType::Perk_panel)
	{
		FItemDT* RefItemDT = nullptr;
		UAbilityDT* RefAbilityType;

		bool is = SelectUnit->GetFastPanelSlotElement(IndexInContainer, RefItemDT, RefAbilityType);
		SelectUnit->RemoveElementFromFastPanel(IndexInContainer);
		IndexInContainer = -1;
		is = true;
		is = true;

		ABaseHUD* HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD)
		{
			if (HUD->IsFastPanelShown)
			{
				HUD->ShowFastPanel(SelectUnit);
			}
		}
	}
	if (PanelTypeFix == ESlotType::heavy_amunition)
	{

	}
	if (PanelTypeFix == ESlotType::World)
	{

	}
	if (PanelTypeFix == ESlotType::weapon_panel)
	{

		SelectUnit->SetWeaponSlotSelected(IndexInContainer);
	}


	if (PanelTypeFix > ESlotType::weapon_equip && PanelTypeFix < ESlotType::armor_equip) 
	{
		if (PanelTypeFix == ESlotType::contact_wpn_big)
		{
			bool is = SelectUnit->IsEquipPanelSlotEmpty(IndexInContainer);
			FItemDT* itm = SelectUnit->GetItemRefFromEquipPanel(IndexInContainer);
			SelectUnit->RemoveItemFromEquipPanel(IndexInContainer);
			IndexInContainer = -1;
			
		}
		if (PanelTypeFix == ESlotType::contact_wpn_small)
		{
			bool is = SelectUnit->IsEquipPanelSlotEmpty(IndexInContainer);
			FItemDT* itm = SelectUnit->GetItemRefFromEquipPanel(IndexInContainer);
			SelectUnit->RemoveItemFromEquipPanel(IndexInContainer);
			IndexInContainer = -1;
		}
		if (PanelTypeFix == ESlotType::range_wpn)
		{
			bool is = SelectUnit->IsEquipPanelSlotEmpty(IndexInContainer);
			FItemDT* itm = SelectUnit->GetItemRefFromEquipPanel(IndexInContainer);
			SelectUnit->RemoveItemFromEquipPanel(IndexInContainer);
			IndexInContainer = -1;
		}
		if (PanelTypeFix == ESlotType::pistol)
		{
			bool is = SelectUnit->IsEquipPanelSlotEmpty(IndexInContainer);
			FItemDT* itm = SelectUnit->GetItemRefFromEquipPanel(IndexInContainer);
			SelectUnit->RemoveItemFromEquipPanel(IndexInContainer);
			IndexInContainer = -1;
		}

	}
	if (PanelTypeFix > ESlotType::armor_equip)
	{
		if (PanelTypeFix == ESlotType::cup)
		{

		}
		if (PanelTypeFix == ESlotType::armour)
		{

		}
	}
*/


																// @@@@@@@@@@@@@@@@@@@@@@@   TEST  
																ABaseHUD* HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
																if (HUD)
																{
																	if (HUD->IsEquipPanelShown)
																	{
																		HUD->ShowEquipPanel(SelectUnit);
																	}
																}





	// ** Set ButtonFocus
	//Reply.NativeReply = FReply::Handled();
	//++++FReply Reply = FReply::Unhandled();
	//++++Reply = FReply::Handled();
	//++++Reply.ReleaseMouseCapture();
	//++++return Reply;
	bIsFocusable = true;
	SetFocus();
	TSharedPtr<SWidget> SharedWidget = TakeWidget();
	return FReply::Handled().SetUserFocus(SharedWidget.ToSharedRef());

	// ** FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	// ** return reply.NativeReply;
}


// ** FFFFFFFFFF  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
FReply UW_Slot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) 
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);


	UE_LOG(LogTemp, Log, TEXT("WWWWWWWWWWWWWW  Mouse Dn:   %i"), IndexInContainer);
	


	// ** Init long click checking
	CurrMousClickDuration = 0;
	GetWorld()->GetTimerManager().SetTimer(TH_MousClickDuration, this, &UW_Slot::MousClickDurationLoop, GetWorld()->GetDeltaSeconds(), true);





	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		CurrClickedMouseKey = EKeys::LeftMouseButton;
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		CurrClickedMouseKey = EKeys::RightMouseButton;
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::MiddleMouseButton))
	{
		CurrClickedMouseKey = EKeys::MiddleMouseButton;
	}


	
	// ** Set ButtonFocus
	//TSharedPtr<UW_Slot> SharedWidget = MakeShared<UW_Slot>();		// ** for Slate
	//TSharedRef<SWidget> SharedWidget = AsShared();				// ** for Slate
	//return FReply::Handled().SetUserFocus(SharedThis(this));		// ** for Slate
	//return FReply::Unhandled();
	//return FReply::Handled();
	bIsFocusable = true;
	SetFocus();
	TSharedPtr<SWidget> SharedWidget = TakeWidget();
	return FReply::Handled().SetUserFocus(SharedWidget.ToSharedRef());


	//FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton); 
	//return reply.NativeReply;
}
 
void UW_Slot::MousClickDurationLoop()
{
	CurrMousClickDuration += GetWorld()->GetDeltaSeconds();
	if (CurrMousClickDuration > MousClickDurationMax)
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_MousClickDuration);

		// ** Init Long click
		if (CurrClickedMouseKey == EKeys::LeftMouseButton)
		{
			MsClickLongLeft();
		}
		else if (CurrClickedMouseKey == EKeys::RightMouseButton)
		{
			MsClickLongRight();
		}
		else if (CurrClickedMouseKey == EKeys::MiddleMouseButton)
		{
			MsClickLongMiddle();
		}
	}
}



void UW_Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

		
}


bool UW_Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	

	return true;
}
 
void UW_Slot::InventoryDropPerformance(const UW_Slot* ItemSlotUnder, UW_DropSlot* ItemSlotDragg)
{ 
	
}
  

void UW_Slot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
																			UDragDropOperation* InOperation)
{
	//UE_LOG(LogTemp, Log, TEXT("WWWWWWWWWWWWWW            OnDragEnter"));

	
}

void UW_Slot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	
	
}



int32 UW_Slot::CheckPlaceUnder(const UW_Slot* ItemSlotUnder, const UW_DropSlot* ItemSlotDraging)
{
	

	return 0;
}