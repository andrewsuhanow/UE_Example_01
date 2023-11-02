
// #include "Base/HUD/ScreenPart/W_Inventory.h"

#include "W_Inventory.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"

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




void  UW_Inventory::ShowInventory(AUnit* _Unit, ABaseGameMode* _GameMode)
{
	UpdateInventory(_Unit, _GameMode);
}



void  UW_Inventory::UpdateInventory(AUnit* _Unit, ABaseGameMode* _GameMode)
{

	// ** get size data
	bool isInventorSizeFixed = _Unit->IsInventorSizeFixed;
	int32 mainInvCollCountBOUND = _Unit->MainInvCollCountBOUND;
	int32 mainInvRowCountBOUND = _Unit->MainInvRowCountBOUND;
	int32 fullRowCount = _Unit->FullRowCount;
	float mainInventorSlotSize = _Unit->MainInventorSlotSize;
	if (mainInvCollCountBOUND == 0 || fullRowCount == 0 || mainInventorSlotSize == 0)
	{
		isInventorSizeFixed = _GameMode->IsInventorSizeFixed;
		mainInvCollCountBOUND = _GameMode->MainInvCollCountBOUND;	// ** CellCount_Col
		mainInvRowCountBOUND = _GameMode->MainInvRowCountBOUND;
		fullRowCount = _GameMode->FullRowCount;						// ** CellCount_Row
		mainInventorSlotSize = _GameMode->MainInventorSlotSize;
	}


	// ** Set Total invertory size
	InventorySizeBox->bOverride_HeightOverride = 1;
	InventorySizeBox->SetHeightOverride(mainInventorSlotSize * mainInvRowCountBOUND);
	InventorySizeBox->bOverride_WidthOverride = 1;
	InventorySizeBox->SetWidthOverride(mainInventorSlotSize * mainInvCollCountBOUND);
	/// ** InventorySizeBox->SetMaxDesiredWidth(mainInventorSlotSize * mainInvCollCountBOUND);
	/// ** InventorySizeBox->SetMinDesiredWidth(mainInventorSlotSize * mainInvCollCountBOUND);
	/// ** InventorySizeBox->SetMaxDesiredHeight(mainInventorSlotSize * fullRowCount);
	/// ** InventorySizeBox->SetMinDesiredHeight(mainInventorSlotSize * fullRowCount);


	// ** set all Slots default   
	int32 SlotsNum = fullRowCount * mainInvCollCountBOUND;
	int32 OlredyExistingSlotCount = SlotObj.Num(); 
	int32 i;
	for (i = 0; i < SlotsNum; ++i)
	{
		// ** Add Main-Inventory-Slots new Row 
		if (i >= OlredyExistingSlotCount)
		{
			AddSlotsRowAtOnBottom(_Unit, _GameMode, i / mainInvCollCountBOUND, mainInvCollCountBOUND, mainInventorSlotSize);
			OlredyExistingSlotCount = SlotObj.Num();
		}
		
		SlotObj[i]->SelectUnit = _Unit;
		SlotObj[i]->IndexInContainer = i;	// ** index-Container = index-W_Slot
		UTexture2D* texture = _Unit->MainInvertorySlotTexture;
		if(!texture) 
			_GameMode->MainInvertorySlotTexture;
		SlotObj[i]->BackgroungImage->SetBrushFromTexture(texture, false);				// ** nullptr - noImage
		SlotObj[i]->ImgItem->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));	// ** hite item icon 
		SlotObj[i]->SetVisibility(ESlateVisibility::Visible); // Collapsed,

		// ** set slot size
		///SlotObj[i]->SzBox->SetHeightOverride(mainInventorSlotSize);
		///SlotObj[i]->SzBox->SetWidthOverride(mainInventorSlotSize);
		SlotObj[i]->SzBox->SetMinDesiredWidth(mainInventorSlotSize);
		SlotObj[i]->SzBox->SetMaxDesiredWidth(mainInventorSlotSize);
		SlotObj[i]->SzBox->SetMinDesiredHeight(mainInventorSlotSize);
		SlotObj[i]->SzBox->SetMaxDesiredHeight(mainInventorSlotSize);
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

				if (ItemsList[i].SlotUI_Index < SlotsNum)
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
							SlotObj[Index]->SetVisibility(ESlateVisibility::Collapsed); // Hidden
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




void UW_Inventory::AddSlotsRowAtOnBottom(AUnit* _Unit, ABaseGameMode* _GameMode, int32 _Row, int32 _CollCount, float _SlotSize)
{
	//if (!PlayerPAWN) return;
	//if (PlayerPAWN->SelectGroup.Num() != 1) return;

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
			NewSlot->SzBox->SetMaxDesiredHeight(_SlotSize);
			NewSlot->SzBox->SetMinDesiredHeight(_SlotSize);
			NewSlot->SzBox->SetMaxDesiredWidth(_SlotSize);
			NewSlot->SzBox->SetMinDesiredWidth(_SlotSize);
			///NewSlot->SzBox->bOverride_HeightOverride = 1;
			///NewSlot->SzBox->SetHeightOverride(_SlotSize);
			///NewSlot->SzBox->bOverride_WidthOverride = 1;
			///NewSlot->SzBox->SetWidthOverride(_SlotSize);
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


