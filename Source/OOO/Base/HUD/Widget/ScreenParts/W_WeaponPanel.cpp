
// #include "Base/HUD/ScreenPart/W_WeaponPanel.h"

#include "W_WeaponPanel.h"

#include "../Slot/W_Slot.h"
#include "../Slot/W_DropSlot.h"

#include "../../../Unit/Base/Unit.h"
//--------------#include "../../../Inventory/InventoryComponent.h"

//#include "../../../Ability/AbilityComponent.h"
//#include "../../../Ability/Enum/AbilityType.h"
//#include "../../../Ability/Struct/AbilityDT.h"

#include "../../../Controller/Task/Enum/TaskType.h"


#include "../../../Base/BaseGameMode.h"
#include "../../../HUD/BaseHUD.h"

#include "Blueprint/WidgetTree.h"


#include "Components/HorizontalBox.h" 
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UW_WeaponPanel::NativePreConstruct()
{
	Super::NativePreConstruct();

	//WeaponPanelScroll->SetOrientation(EOrientation::Orient_Horizontal);

}



void UW_WeaponPanel::NativeConstruct()
{
	Super::NativeConstruct();

	ActiveWeaponButton->OnReleased.AddDynamic(this, &UW_WeaponPanel::ActiveWeaponButtonCall);
	SelectWeaponButton->OnReleased.AddDynamic(this, &UW_WeaponPanel::SelectWeaponButtonCall);

	WeaponPanelGorzBox->ClearChildren();
	SlotObj.Reset();

	ActivateWeaponImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	//-----CurrWeaponImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}


void UW_WeaponPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}


void UW_WeaponPanel::ActiveWeaponButtonCall()
{

	if (Unit)
	{
		// ** Unit->ActivateWeaponTask;

		ETaskType taskType = ETaskType::ActivateWeapon;		
		ETaskInstigator taskInstigator = ETaskInstigator::Dominant;
		ETaskPriority taskPriority = ETaskPriority::Normal;

		Unit->SetUnitTask(false, // ** bAddMoreOneTask  NO_MATTAER
			taskType,
			FTaskData(),	// ** NO_MATTAER
			taskInstigator,
			taskPriority);
	}
}

void UW_WeaponPanel::SelectWeaponButtonCall()
{
	if (!Unit)
		return;

	ABaseHUD* HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (!HUD->IsWpnChangePanelOpened)
	{
		Unit->OpenChangeWeaponPanel();
	}
	else
	{
		HUD->CloseChangeWeaponPanel();
		WeaponPanelGorzBox->SetVisibility(ESlateVisibility::Hidden);  				// ** Visible,  Hidden,  Collapsed
	}
}





void UW_WeaponPanel::ShowWeaponPanel(AUnit* _Unit,
	int32& _WeaponSlotIndex,
	ESlotType& _WeaponSlotType,
	UTexture2D*& _WeaponSlotTexture)
{
	Unit = _Unit;
	IndexInContainer = _WeaponSlotIndex;

	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	float slotSize = gameMode->WeaponPanelSlotSize;
	UTexture2D* SlotBackTexture = _Unit->MainInvertorySlotTexture;
	if (!SlotBackTexture)
		SlotBackTexture = gameMode->MainInvertorySlotTexture;
	if (_WeaponSlotIndex == -1)
		_WeaponSlotTexture = nullptr;
		
	ActivateWeaponImg->SetBrushFromTexture(_WeaponSlotTexture, false);
	// ** ChangeWeaponImg->SetBrushFromTexture(_WeaponSlotTexture, false);
	
	ActivateWeaponBackImg->SetBrushFromTexture(SlotBackTexture, false);
	ChangeWeaponBackImg->SetBrushFromTexture(SlotBackTexture, false);


	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}

void UW_WeaponPanel::HideWeaponPanel()
{
	SetVisibility(ESlateVisibility::Collapsed);  				// ** Visible,  Hidden,  Collapsed
}

void UW_WeaponPanel::OpenWpnChangePanel(AUnit* _Unit,
	TArray<int32>& _WeaponSlotsIndex,
	TArray<ESlotType>& _WeaponSlotsType,
	TArray<UTexture2D*>& _WeaponSlotsTexture)
{
	Unit = _Unit;

	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	UpdateWeaponPanel(_Unit, gameMode,
		_WeaponSlotsIndex,
		_WeaponSlotsType,
		_WeaponSlotsTexture);
	WeaponPanelGorzBox->SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
}



void UW_WeaponPanel::CloseWpnChangePanel()
{
	WeaponPanelGorzBox->SetVisibility(ESlateVisibility::Hidden);  				// ** Visible,  Hidden,  Collapsed
}



void UW_WeaponPanel::UpdateWeaponPanel(AUnit* _Unit, ABaseGameMode* _GameMode,
	TArray<int32>& _WeaponSlotsIndex,
	TArray<ESlotType>& _WeaponSlotsType,
	TArray<UTexture2D*>& _WeaponSlotsTexture)
{

	Unit = _Unit;

	float slotSize = _GameMode->WeaponPanelSlotSize;
	UTexture2D* SlotBackTexture = _Unit->MainInvertorySlotTexture;
	if (!SlotBackTexture)
		SlotBackTexture = _GameMode->MainInvertorySlotTexture;


	int32 SlotObjNum = SlotObj.Num();

	// ** Hide All Slot
	for (int32 i = 0; i < SlotObjNum; ++i)
	{
		SlotObj[i]->SetVisibility(ESlateVisibility::Collapsed); /// Collapsed, Visible, Hidden
	}

	// ** Add new slots if need
	for (int32 i = SlotObjNum; i < _WeaponSlotsIndex.Num(); ++i)
	{
		AddCellToWeaponPanel(_GameMode, slotSize, SlotBackTexture);
		++SlotObjNum;
	}


	
	// ** Assign Unit-WeaponSlotDT to Slot
	int32 i = 0;
	for (; i < _WeaponSlotsIndex.Num(); ++i)
	{
		SlotObj[i]->SelectUnit = _Unit;

		SlotObj[i]->SetSlotParam(_WeaponSlotsIndex[i],
			_WeaponSlotsTexture[i], SlotBackTexture,
			slotSize, slotSize,
			slotSize, slotSize,
			0, 0,
			ESlotType::weapon_panel);	// ** Its weapon-Slot

		SlotObj[i]->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden


		// ** Set image on "Activate-Weapon-Button"
		if (_WeaponSlotsIndex[i] == _Unit->GetWeaponSlotSelected())
		{
			ActivateWeaponImg->SetBrushFromTexture(_WeaponSlotsTexture[i], false);
		}

	}

	// ** Set Total Temporare-Weapon-change-panel size
	WeaponPanelSizeBox->bOverride_HeightOverride = 1;
	WeaponPanelSizeBox->SetHeightOverride(slotSize);
	WeaponPanelSizeBox->bOverride_WidthOverride = 1;
	WeaponPanelSizeBox->SetWidthOverride(slotSize * i);

}


void UW_WeaponPanel::AddCellToWeaponPanel(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture)
{

	UW_Slot* NewSlot = WidgetTree->ConstructWidget<UW_Slot>(_GameMode->W_Slot_Class);

	if (NewSlot)
	{
		NewSlot->SetSlotParam(-1,		// ** -1: not linked with real unit Slot (is empty Slot)
			nullptr, SlotBackTexture,
			_SlotSize, _SlotSize,
			_SlotSize, _SlotSize,
			0, 0,						// ** dont Translation;
			ESlotType::weapon_panel);	// ** Its weapon-Slot

		NewSlot->SetVisibility(ESlateVisibility::Visible); /// Collapsed, Visible, Hidden	

		NewSlot->SetItemCount(0, 0, 0);

		WeaponPanelGorzBox->AddChildToHorizontalBox(NewSlot);
		SlotObj.Add(NewSlot);
	}
}