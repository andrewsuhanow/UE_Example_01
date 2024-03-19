
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

	CurrTaskSlotObj->SetItemCount(0, 0, 0);

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

	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed

	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	float slotSize			= gameMode->TaskQueueSlotSize;
	int32 taskQueueSlotsNum = gameMode->TaskQueueSlotsNum;
	int32 slotObjNum		= SlotObj.Num();
	int32 currExistingTasksNum	= _TasksIcon.Num();
	UTexture2D* slotBackTexture = _Unit->MainInvertorySlotTexture;
	if (!slotBackTexture)
		slotBackTexture		= gameMode->MainInvertorySlotTexture;

	// ** Add new slot (if need)
	while(slotObjNum < taskQueueSlotsNum)
	{
		AddCellToTaskQueue(gameMode, slotSize, slotBackTexture);
		++slotObjNum;
	}


	// ** Hidde all
	for (int32 i = 0; i < slotObjNum; ++i)
	{
		CurrTaskSlotObj->SetVisibility(ESlateVisibility::Collapsed); /// Collapsed, Visible, Hidden	
		SlotObj[i]->SetVisibility(ESlateVisibility::Collapsed); 
	}



	// ** Draw Task-Slots

	// ** curr Task
	if (_CurrTaskIcon)
	{
		CurrTaskSlotObj->SetVisibility(ESlateVisibility::Visible);

		CurrTaskSlotObj->SetSlotParam(-10,		// ** link to Currunt unit Task
			_CurrTaskIcon, slotBackTexture,
			slotSize, slotSize,
			slotSize, slotSize,
			0, 0,							// ** Translation;
			ESlotType::task_queue_panel);

		CurrTaskSlotObj->SetBarProgress(0.f);
	}

	// ** curr Tasks Queue
	for (int32 i = 0; i < currExistingTasksNum; ++i)
	{
		SlotObj[i]->SetVisibility(ESlateVisibility::Visible);

		SlotObj[i]->SetSlotParam(_TasksIndex[i],// ** link to real unit-Task-Index
			_TasksIcon[i], slotBackTexture,
			slotSize, slotSize,
			slotSize, slotSize,
			0, 0,							// ** Translation;
			ESlotType::task_queue_panel);
	}
}





void UW_TaskQueuePanel::AddCellToTaskQueue(ABaseGameMode* _GameMode, 
	float _SlotSize, UTexture2D* SlotBackTexture)
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

		NewSlot->SetItemCount(0, 0, 0);
		NewSlot->SetBarProgress(0.f);

		NewSlot->SetVisibility(ESlateVisibility::Hidden); /// Collapsed, Visible, Hidden	

		TaskQueueHorizontalBox->AddChildToHorizontalBox(NewSlot);
		SlotObj.Add(NewSlot);
	}
}