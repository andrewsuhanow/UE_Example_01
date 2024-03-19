
// #include "Base/HUD/ScreenPart/W_GlobalInventory.h"

#include "W_GlobalInventory.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"
#include "../../../Inventory/InventoryComponent.h"

#include "../../../Base/BaseGameMode.h"


#include "Blueprint/WidgetTree.h"

#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"


//#include "Components/VerticalBox.h"
//#include "Components/CanvasPanel.h"
//#include "Components/CanvasPanelSlot.h"


void UW_GlobalInventory::NativePreConstruct()
{
	Super::NativePreConstruct();


}



void UW_GlobalInventory::NativeConstruct()
{
	Super::NativeConstruct();





	InventoryScroll->ClearChildren();
	SlotObj.Reset();




/*
	// ** drug item when Mouse release
	PC = GetWorld()->GetFirstPlayerController();

	// ** ***********************    Perk Panel   
	PerkPanelOpen_Button->OnReleased.AddDynamic(this, &UW_GlobalInventory::PerkPanelOpen);
	PerkGlobalPanels->SetVisibility(ESlateVisibility::Collapsed); // Collapsed, Visible
*/
/*	Button_SectionLocomotion->OnReleased.AddDynamic(this, &UW_GlobalInventory::SectionLocomotion_Activate);
	Button_SectionSword->OnReleased.AddDynamic(this, &UW_GlobalInventory::SectionSword_Activate);
	Button_SectionLongSword->OnReleased.AddDynamic(this, &UW_GlobalInventory::SectionLongSword_Activate);
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  other button of ability Category
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/




/*
++++++++++++++++++++++++++++++++++++++++++


// ** ***********************    Fast Panel   (set size)
	if (PlayerPAWN)
		for (int32 i = 0; i < FastPanel_Slots.Num(); ++i)
		{
			//SzBox_Inventory->bOverride_HeightOverride = 1;
			//SzBox_Inventory->SetHeightOverride(PlayerPAWN->Inventory_Cell_Size * draw_main_inv->Fixed_RowCount);

			//int32 NewSlotIndex = Global_Cells.Num();
			FastPanel_Slots[i]->ImgItem->SetBrushSize(FVector2D(PlayerPAWN->FastPanel_Cell_Size, PlayerPAWN->FastPanel_Cell_Size));
			FastPanel_Slots[i]->BackgroungImage->SetBrushSize(FVector2D(PlayerPAWN->FastPanel_Cell_Size, PlayerPAWN->FastPanel_Cell_Size));
			FastPanel_Slots[i]->SzBox->SetMaxDesiredHeight(PlayerPAWN->FastPanel_Cell_Size);
			FastPanel_Slots[i]->SzBox->SetMinDesiredHeight(PlayerPAWN->FastPanel_Cell_Size);
			FastPanel_Slots[i]->SzBox->SetMaxDesiredWidth(PlayerPAWN->FastPanel_Cell_Size);
			FastPanel_Slots[i]->SzBox->SetMinDesiredWidth(PlayerPAWN->FastPanel_Cell_Size);
			FastPanel_Slots[i]->ImgItem->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
			FastPanel_Slots[i]->BackgroungImage->SetBrushFromTexture(ImgBackgroundTexture, false);
		}
*/

}


void UW_GlobalInventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


/*
	if (W_DROP_DragSlot && PC && PlayerPAWN)
	{
		float Width = (PlayerPAWN->Inventory_Cell_Size * TemporareDrugingItem.SizeX / 5);
		Width -= 60 / Width;
		float Height = (PlayerPAWN->Inventory_Cell_Size * TemporareDrugingItem.SizeY / 5);
		Height -= 60 / Height;
		float X, Y;
		PC->GetMousePosition(X, Y);
		W_DROP_DragSlot->SetPositionInViewport(FVector2D(X - Width, Y - Height), true);
		//W_DROP_DragSlot->SetPositionInViewport(FVector2D(X, Y), true);
	}
*/

}



void UW_GlobalInventory::ShowInventory(UInventoryComponent* _Inventor)
{
	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	UpdateInventory(_Inventor, gameMode);
	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}




void UW_GlobalInventory::UpdateInventory(UInventoryComponent* _Inventor, ABaseGameMode* _GameMode)
{
	AUnit* _Unit = Cast<AUnit>(_Inventor->GetOwner());

	
	float slotSize	= 2.f * _GameMode->MainInventorSlotSize;
	int32 slotsNumShownOnScreen = _GameMode->MainInvRowNum / 2;		
	ESlotType globalInveType = ESlotType::global_inv;	// ** its Global-Inventor-Slot here
	UTexture2D* SlotBackTexture = _Unit->MainInvertorySlotTexture;
		if (!SlotBackTexture)
			SlotBackTexture = _GameMode->MainInvertorySlotTexture;

	int32 SlotObjNum = SlotObj.Num();
	int32 UnitSlotNum = _Inventor->GlobalInvItemSlot.Num();


	// ** Set Total Global-Invertory size
	InventorySizeBox->bOverride_HeightOverride = 1;
	InventorySizeBox->SetHeightOverride((slotSize * slotsNumShownOnScreen) + slotSize / 2);
	InventorySizeBox->bOverride_WidthOverride = 1;
	InventorySizeBox->SetWidthOverride(slotSize + slotSize / 2);


	// ** Add new slots (if its les then unit Item)
	for (int32 i = SlotObjNum; i < UnitSlotNum; ++i)
	{
		AddCellToGlobalInv(_GameMode, slotSize, SlotBackTexture);
		++SlotObjNum;
	}


	// ** Assign Unit-ItemDT to Slot
	int32 indexInContainer;
	for (indexInContainer = 0; indexInContainer < UnitSlotNum; ++indexInContainer)
	{
		SlotObj[indexInContainer]->SelectUnit = _Unit;

		UTexture2D* itemImage = _Inventor->GlobalInvItemSlot[indexInContainer].GetOneSlotImage();

		// ** Set slot-item-Param
		SlotObj[indexInContainer]->SetSlotParam(indexInContainer, 
			itemImage, SlotBackTexture,
			slotSize, slotSize,
			slotSize, slotSize,
			0, 0,						// ** dont Translation;
			globalInveType);

		// ** Set slot-text
		int32 itemCount = _Inventor->GlobalInvItemSlot[indexInContainer].Count;
		int32 itemMaxCount = _Inventor->GlobalInvItemSlot[indexInContainer].CountMax;
		SlotObj[indexInContainer]->SetItemCount(itemCount, itemMaxCount, slotSize/ 6.f);

		SlotObj[indexInContainer]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden		
	}



	// ** Hide all other Slots but first-slotsNumShownOnScreen
	if (indexInContainer <= slotsNumShownOnScreen)
	{
		// ** Add new slots (if les then "slotsNumShownOnScreen")
		for (int32 i = SlotObjNum; i < slotsNumShownOnScreen; ++i)
		{
			AddCellToGlobalInv(_GameMode, slotSize, SlotBackTexture);
			++SlotObjNum;
		}

		// ** draw first (if no one items(or not fill full screen) 
		// ** draw empty slot with no-links with Real-Inventar)
		for (; indexInContainer < slotsNumShownOnScreen; ++indexInContainer)
		{
			SlotObj[indexInContainer]->SelectUnit = _Unit;

			SlotObj[indexInContainer]->SetSlotParam(-1,		// ** -1: not linked with real unit Slot (is empty Slot)
				nullptr, SlotBackTexture,
				slotSize, slotSize, 
				slotSize, slotSize, 
				0, 0,										// ** dont Translation;	
				globalInveType);

			// ** Set slot-text (hide text)
			SlotObj[indexInContainer]->SetItemCount(0, 0, 0);

			SlotObj[indexInContainer]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden	
		}


	}

	// ** hide all rest
	for (; indexInContainer < SlotObjNum; ++indexInContainer)
	{
		SlotObj[indexInContainer]->SetVisibility(ESlateVisibility::Collapsed); /// Collapsed, Visible, Hidden
	}
}





void UW_GlobalInventory::AddCellToGlobalInv(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture)
{

	UW_Slot* NewSlot = WidgetTree->ConstructWidget<UW_Slot>(_GameMode->W_Slot_Class);

	if (NewSlot)
	{
		NewSlot->SetSlotParam(-1,		// ** -1: not linked with real unit Slot (is empty Slot)
			nullptr, SlotBackTexture,
			_SlotSize, _SlotSize, 
			_SlotSize, _SlotSize, 
			0, 0,						// ** dont Translation;	
			ESlotType::global_inv);


		NewSlot->SetBarProgress(0.f);

		NewSlot->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden	

		InventoryScroll->AddChild(NewSlot);
		SlotObj.Add(NewSlot);
	}
}