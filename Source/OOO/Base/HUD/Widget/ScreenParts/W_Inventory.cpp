
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



	InventoryCanva->GetAllChildren();



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



void UW_Inventory::ShowInventory(UInventoryComponent* _Inventor, ABaseGameMode* _GameMode)
{
	UpdateInventory(_Inventor, _GameMode);
}




void UW_Inventory::UpdateInventory(UInventoryComponent* _Inventor, ABaseGameMode* _GameMode)
{

	AUnit* _Unit = Cast<AUnit>(_Inventor->GetOwner());

	// ** get size data
	int32 mainInvCollNum = _GameMode->MainInvCollNum;
	int32 mainInvRowNum = _GameMode->MainInvRowNum;
	float mainInventorSlotSize	= _GameMode->MainInventorSlotSize;

	bool isInventorSizeFixed = _Unit->IsInventorSizeFixed;
	int32 fullRowNum = _Unit->FullRowNum;
	UTexture2D* MainInvertorySlotTexture = _Unit->MainInvertorySlotTexture;






	// ** Set Total invertory size
	InventorySizeBox->bOverride_HeightOverride = 1;
	InventorySizeBox->SetHeightOverride(mainInventorSlotSize * mainInvRowNum);
	InventorySizeBox->bOverride_WidthOverride = 1;
	InventorySizeBox->SetWidthOverride(mainInventorSlotSize * mainInvCollNum);



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
		SlotObj[i]->IndexInContainer = i;	// ** index-Container = index-W_Slot
		UTexture2D* texture = _Unit->MainInvertorySlotTexture;
		if(!texture) 
			_GameMode->MainInvertorySlotTexture;
		SlotObj[i]->BackgroungImage->SetBrushFromTexture(texture, false);				// ** nullptr - noImage
		SlotObj[i]->ImgItem->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));	// ** hite item icon 
		SlotObj[i]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden

		// ** set slot size
		SlotObj[i]->SzBox->SetHeightOverride(mainInventorSlotSize);
		SlotObj[i]->SzBox->SetWidthOverride(mainInventorSlotSize);
	}

	// ** collapsed unnecessary slot
	if (ExistingWSlotNum > UnitSlotNum)
	{
		for (i = UnitSlotNum - 1; i < ExistingWSlotNum; ++i)
		{
			SlotObj[i]->SetVisibility(ESlateVisibility::Collapsed); /// Collapsed, Visible, Hidden
		}
	}


	// ** Assign Unit-ItemDT to Slot
	for (const auto& It : _Inventor->MainInventoryItem)
	{
		// SlotObj[It.Key]->IndexInContainer = i;

		SlotObj[It.Key]->SetImage(It.Value.GetFullImage());
		SlotObj[It.Key]->SetBackgroundImage(MainInvertorySlotTexture);  

		// ** Hide other Item Slot (Show only first)
		for (int32 Hor = 0; Hor < It.Value.GetItemHorizontalSize(); ++Hor)
		{
			for (int32 Wert = 0; Wert < It.Value.GetItemVerticalSize(); ++Wert)
			{
				int32 SlotIndexForHidding = It.Key + Hor + Wert * mainInvCollNum;
				SlotObj[SlotIndexForHidding]->SetVisibility(ESlateVisibility::Collapsed); /// Collapsed, Visible, Hidden;
			}
		}
		SlotObj[It.Key]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden;


		// ** Set Slot SIZE
		SlotObj[It.Key]->SzBox->SetHeightOverride(mainInventorSlotSize * It.Value.GetItemVerticalSize());
		SlotObj[It.Key]->SzBox->SetWidthOverride(mainInventorSlotSize * It.Value.GetItemHorizontalSize());

	}
//---------------------------------------------
/*
///////////////////////////
///////////////////////////
///////////////////////////
///////////////////////////
///////////////////////////
///////////////////////////
			// ** Assign ITEM to W_CELL
			TArray<FItemData>& ItemsList = draw_main_inv->Item_Inventory;
			int32 Item_Count = ItemsList.Num();
			for (i = 0; i < Item_Count; ++i)
			{

				if (ItemsList[i].SlotUI_Index < UnitSlotNum)
				{
					SlotObj[ItemsList[i].SlotUI_Index]->ImgItem->SetBrushFromTexture(ItemsList[i].Texture, false);
					SlotObj[ItemsList[i].SlotUI_Index]->ImgItem->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
					SlotObj[ItemsList[i].SlotUI_Index]->InventorLink = draw_main_inv;
					SlotObj[ItemsList[i].SlotUI_Index]->IndexInMainContainer = i;
					// ** Hide W_Cell nearby (Item-Winth-&-Height)
					for (int W = 0; W < ItemsList[i].SizeX; ++W)
					{
						for (int H = 0; H < ItemsList[i].SizeY; ++H)
						{
							if (W == 0 && H == 0) continue;
							int32 Index = ItemsList[i].SlotUI_Index + W + (H * CellCount_Col);
							SlotObj[Index]->SetVisibility(ESlateVisibility::Collapsed); /// Collapsed, Visible, Hidden
						}
					}
					// ** size
					SlotObj[ItemsList[i].SlotUI_Index]->SzBox->SetMinDesiredWidth(PlayerPAWN->Inventory_Cell_Size * ItemsList[i].SizeX);
					SlotObj[ItemsList[i].SlotUI_Index]->SzBox->SetMaxDesiredWidth(PlayerPAWN->Inventory_Cell_Size * ItemsList[i].SizeX);
					SlotObj[ItemsList[i].SlotUI_Index]->SzBox->SetMinDesiredHeight(PlayerPAWN->Inventory_Cell_Size * ItemsList[i].SizeY);
					SlotObj[ItemsList[i].SlotUI_Index]->SzBox->SetMaxDesiredHeight(PlayerPAWN->Inventory_Cell_Size * ItemsList[i].SizeY);
					//////SlotObj[ItemsList[i].SlotUI_Index]->SzBox->SetHeightOverride(PlayerPAWN->Inventory_Cell_Size * ItemsList[i].SizeY);
					//////SlotObj[ItemsList[i].SlotUI_Index]->SzBox->SetWidthOverride(PlayerPAWN->Inventory_Cell_Size * ItemsList[i].SizeX);
					// ** SlotObj[ItemsList[i].SlotUI_Index]->W_Parent = this;
					// ** SlotObj[ItemsList[i].SlotUI_Index]->ThisSlotIndex = i;
					// ** SlotObj[i]->ThisSlotType = ItemsList[i].InvCell_Type;			 // ** NOT NEED Change
				}
			}
*/
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
			NewSlot->SzBox->SetHeightOverride(_SlotSize);
			NewSlot->SzBox->SetWidthOverride(_SlotSize);

			NewSlot->PanelTypeFix = ESlotType::main_inv;
			// ** NewSlot->SelectUnit = _Unit;

			//UnGrid_Inventory->AddChildToUniformGrid(NewSlot, NewRowIndex, i);  // ** Row, Cols = i     // /////////////--------------
			InventoryCanva->AddChild(NewSlot);
			// --++++++ 777777--   NewSlot->SetRenderTranslation(FVector2D(i * _SlotSize, Row * _SlotSize));
			Cast<UCanvasPanelSlot>(NewSlot->Slot)->SetPosition(FVector2D(i * _SlotSize, _Row * _SlotSize));
			SlotObj.Add(NewSlot);
		}
	}
}


