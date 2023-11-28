
// #include "Base/HUD/ScreenParts/W_TaskQueuePanel.h"

#include "W_TaskQueuePanel.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"

//-----#include "../../../Inventory/InventoryComponent.h"


#include "../../../Base/BaseGameMode.h"


#include "Blueprint/WidgetTree.h"

#include "Components/HorizontalBox.h"
//#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"


void UW_TaskQueuePanel::NativePreConstruct()
{
	Super::NativePreConstruct();


}



void UW_TaskQueuePanel::NativeConstruct()
{
	Super::NativeConstruct();



	TaskQueueHorizontalBox->ClearChildren();
	SlotObj.Reset();
}


void UW_TaskQueuePanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}







void UW_TaskQueuePanel::ShowTaskQueuePanel(AUnit* _Unit,
	UTexture2D*& _CurrTaskIcon,
	TArray<UTexture2D*>& _TasksIcon,
	TArray<int32>& _TasksIndex)
{
	UpdateTaskQueuePanel(_Unit, _CurrTaskIcon, _TasksIcon, _TasksIndex);

	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}

void UW_TaskQueuePanel::HideTaskQueuePanel()
{
	SetVisibility(ESlateVisibility::Collapsed);  				// ** Visible,  Hidden,  Collapsed
}

void UW_TaskQueuePanel::UpdateTaskQueuePanel(class AUnit* _Unit,
	UTexture2D*& _CurrTaskIcon,
	TArray<UTexture2D*>& _TasksIcon,
	TArray<int32>& _TasksIndex)
{
/*
	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	float slotSize = _GameMode->TaskQueueSlotSize;
	int32 TaskQueueSlotNum = _GameMode->TaskQueueSlotNum;
	int32 SlotObjNum = SlotObj.Num();
	UTexture2D* SlotBackTexture = _TaskQueueUnit->MainInvertorySlotTexture;
	if (!SlotBackTexture)
		SlotBackTexture = _GameMode->MainInvertorySlotTexture;

	// ** Add new slot (if need)
	while(SlotObjNum < TaskQueueSlotNum)
	{
		AddCellToTaskQueue(_GameMode, slotSize, SlotBackTexture);
		++SlotObjNum;
	}

	

	SlotObj[i]->SelectUnit = _FastPanelUnit;

	SlotObj[i]->SetSlotParam(indexInContainer,
		Image, SlotBackTexture,
		slotSize, slotSize, 
		slotSize, slotSize, 
		0, 0,					// ** dont Translation;
		ESlotType::task_queue_panel);	// ** Its Fast-Slot

*/
}





void UW_TaskQueuePanel::AddCellToTaskQueue(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture)
{

	UW_Slot* NewSlot = WidgetTree->ConstructWidget<UW_Slot>(_GameMode->W_Slot_Class);

	if (NewSlot)
	{
		NewSlot->SetSlotParam(-1,		// ** -1: not linked with real unit Slot (is empty Slot)
			nullptr, SlotBackTexture,
			_SlotSize, _SlotSize,
			_SlotSize, _SlotSize,
			0, 0,						// ** dont Translation;		
			ESlotType::task_queue_panel);

		NewSlot->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden	

		TaskQueueHorizontalBox->AddChildToHorizontalBox(NewSlot);
		SlotObj.Add(NewSlot);
	}
}