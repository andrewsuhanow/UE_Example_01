
// #include "Base/HUD/ScreenPart/W_Inventory.h"

#include "W_Inventory.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"
#include "../../../Inventory/InventoryComponent.h"

#include "../../../Base/BaseGameMode.h"


#include "Blueprint/WidgetTree.h"

#include "Components/ScrollBox.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

#include "Components/VerticalBox.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


void UW_Inventory::NativePreConstruct()
{
	Super::NativePreConstruct();


}



void UW_Inventory::NativeConstruct()
{
	Super::NativeConstruct();



	//InventoryCanva->GetAllChildren();



/*
	// ** drug item when Mouse release
	PC = GetWorld()->GetFirstPlayerController();

	// ** ***********************    Perk Panel   
	PerkPanelOpen_Button->OnReleased.AddDynamic(this, &UW_Inventory::PerkPanelOpen);
	PerkGlobalPanels->SetVisibility(ESlateVisibility::Collapsed); // Collapsed, Visible
*/
/*	Button_SectionLocomotion->OnReleased.AddDynamic(this, &UW_Inventory::SectionLocomotion_Activate);
	Button_SectionSword->OnReleased.AddDynamic(this, &UW_Inventory::SectionSword_Activate);
	Button_SectionLongSword->OnReleased.AddDynamic(this, &UW_Inventory::SectionLongSword_Activate);
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


void UW_Inventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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



void UW_Inventory::ShowInventory(UInventoryComponent* _Inventor)
{
	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	UpdateInventory(_Inventor, gameMode);
	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}




void UW_Inventory::UpdateInventory(UInventoryComponent* _Inventor, ABaseGameMode* _GameMode)
{

	AUnit* _Unit = Cast<AUnit>(_Inventor->GetOwner());

	// ** get data
	int32 mainInvCollNum = _GameMode->MainInvCollNum;
	int32 mainInvRowNum = _GameMode->MainInvRowNum;
	float mainInventorSlotSize	= _GameMode->MainInventorSlotSize;

	bool isInventorSizeFixed = _Unit->IsInventorSizeFixed;
	int32 fullRowNum = _Unit->FullRowNum;		// ** extend of Invetrtor-panel size

	UTexture2D* SlotBackTexture = _Unit->MainInvertorySlotTexture;
	if (!SlotBackTexture)
		SlotBackTexture = _GameMode->MainInvertorySlotTexture;




	// ** Set Total invertory-panel size
	InventorySizeBox->bOverride_HeightOverride = 1;
	InventorySizeBox->SetHeightOverride((mainInventorSlotSize * mainInvRowNum));
	InventorySizeBox->bOverride_WidthOverride = 1;
	InventorySizeBox->SetWidthOverride((mainInventorSlotSize * mainInvCollNum) + mainInventorSlotSize/4);



	// ** set all Slots default   
	int32 ExistingWSlotNum = SlotObj.Num(); 
	int32 UnitSlotNum = _Inventor->MainInventorySlot.Num();
	int32 i;
	for (i = 0; i < UnitSlotNum; ++i)
	{
		// ** Add new Row 
		if (i >= ExistingWSlotNum)
		{
			AddSlotsRowOnBottom(_GameMode, i / mainInvCollNum, mainInvCollNum, mainInventorSlotSize);
			ExistingWSlotNum = SlotObj.Num();
		}

		SlotObj[i]->SelectUnit = _Unit;

		int32 indexInContainer = i;	// ** index-Container = index-W_Slot

		float theSaimSlotWidth = mainInventorSlotSize;
		float theSaimSlotHeight = mainInventorSlotSize;


		SlotObj[i]->SetSlotParam(indexInContainer, 
			nullptr, SlotBackTexture,
			theSaimSlotWidth, theSaimSlotHeight, 
			theSaimSlotWidth, theSaimSlotHeight, 
			0, 0,						// ** dont Translation;
			ESlotType::none);			// ** dont change (its MainInventorSlot here)  
		
		// ** Set slot-text (hide text)
		SlotObj[i]->SetItemCount(0, 0, 0);

		SlotObj[i]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden
	}


	// ** collapse unnecessary slot
	if (ExistingWSlotNum > UnitSlotNum)
	{
		for (i = UnitSlotNum - 1; i < ExistingWSlotNum; ++i)
		{
			SlotObj[i]->SetVisibility(ESlateVisibility::Collapsed); /// Collapsed, Visible, Hidden
		}
	}


	// ** Assign Unit-ItemDT to W-Slot
	for (const auto& It : _Inventor->MainInventoryItem)
	{
		int32 dontChangeIndex = -1;
		float slotWidth = mainInventorSlotSize * It.Value.GetItemHorizontalSize();
		float slotHeight = mainInventorSlotSize * It.Value.GetItemVerticalSize();


		// ** Hide Image of other Item-Slot (Show only first and last)
		int32 lastSlotIndex = 0;
		int32 SlotIndexForHidding = 0;
		for (int32 Hor = 0; Hor < It.Value.GetItemHorizontalSize(); ++Hor)
		{
			for (int32 Wert = 0; Wert < It.Value.GetItemVerticalSize(); ++Wert)
			{
				SlotIndexForHidding = It.Key + Hor + Wert * mainInvCollNum;

				SlotObj[SlotIndexForHidding]->SetSlotParam(dontChangeIndex,
					nullptr, nullptr,
					mainInventorSlotSize, mainInventorSlotSize,
					mainInventorSlotSize, mainInventorSlotSize,
					0, 0,
					ESlotType::none);			// ** dont change (its MainInventorSlot here)  
			}
		}

		// ** Show first Slot-Image
		SlotObj[It.Key]->SetSlotParam(dontChangeIndex,
			It.Value.GetFullImage(), SlotBackTexture, 
			mainInventorSlotSize, mainInventorSlotSize,
			slotWidth, slotHeight,
			0, 0,						// ** dont Translation;
			ESlotType::none);			// ** dont change (its MainInventorSlot here)  


		// ** Show last Slot-Image	(if item bounding more then one slot)	
		lastSlotIndex = SlotIndexForHidding;

		// ** Set slot-text (item count)
		int32 itemCount = It.Value.Count;
		int32 itemMaxCount = It.Value.CountMax;
		SlotObj[lastSlotIndex]->SetItemCount(itemCount, itemMaxCount, mainInventorSlotSize / 6.f);

		if (It.Key != lastSlotIndex)
		{
			float TranslationX = -slotWidth + mainInventorSlotSize;
			float TranslationY = -slotHeight + mainInventorSlotSize;

			SlotObj[lastSlotIndex]->SetSlotParam(dontChangeIndex,
				It.Value.GetFullImage(), SlotBackTexture,
				mainInventorSlotSize, mainInventorSlotSize,
				slotWidth, slotHeight,
				TranslationX, TranslationY,
				ESlotType::none);			// ** dont change (its MainInventorSlot here)  

							// ** Set slot-text
		}
	}
}




void UW_Inventory::AddSlotsRowOnBottom(ABaseGameMode* _GameMode, int32 _Row, int32 _CollCount, float _SlotSize)
{

	int32 LastSlotIndex = SlotObj.Num();

	int32 NewRowIndex = (LastSlotIndex / _CollCount);


	// ** Add row bottom
	for (int32 i = 0; i < _CollCount; ++i)
	{
		UW_Slot* NewSlot = WidgetTree->ConstructWidget<UW_Slot>(_GameMode->W_Slot_Class);

		if (NewSlot)
		{
			NewSlot->ImgItem->SetBrushSize(FVector2D(_SlotSize, _SlotSize));

			// ** Set CELL SIZE
			NewSlot->SzBoxImages->SetHeightOverride(_SlotSize);
			NewSlot->SzBoxImages->SetWidthOverride(_SlotSize);
			//NewSlot->SzBox->SetHeightOverride(_SlotSize);
			//NewSlot->SzBox->SetWidthOverride(_SlotSize);

			NewSlot->PanelTypeFix = ESlotType::main_inv;
			// ** NewSlot->SelectUnit = _Unit;

			NewSlot->SetBarProgress(0.f);

			//UnGrid_Inventory->AddChildToUniformGrid(NewSlot, NewRowIndex, i);  // ** Row, Cols = i     // /////////////--------------
			InventoryCanva->AddChild(NewSlot);
			// --++++++ 777777--   NewSlot->SetRenderTranslation(FVector2D(i * _SlotSize, Row * _SlotSize));
			Cast<UCanvasPanelSlot>(NewSlot->Slot)->SetPosition(FVector2D(i * _SlotSize, _Row * _SlotSize));
			SlotObj.Add(NewSlot);
		}
	}
}


