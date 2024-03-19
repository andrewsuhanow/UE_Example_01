
// #include "Base/HUD/ScreenPart/W_ParameterPanel.h"

#include "W_ParameterPanel.h"

#include "../../../Unit/Base/Unit.h"

#include "../../../Base/BaseGameMode.h"

#include "../../../UnitState/UnitParamComponent.h"
#include "../../../UnitState/Enum/UnitParam.h"

#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"


void UW_ParameterPanel::NativePreConstruct()
{
	Super::NativePreConstruct();


}



void UW_ParameterPanel::NativeConstruct()
{
	Super::NativeConstruct();

	SizeBox_FullHealthBar->bOverride_HeightOverride = 1;
	//---SizeBox_CritMinHP->bOverride_HeightOverride = 1;
	//---SizeBox_MinHP->bOverride_HeightOverride = 1;		// ---77777777777777777777777
	SizeBox_HP->bOverride_HeightOverride = 1;
	SizeBox_PotentialHP->bOverride_HeightOverride = 1;
	//XXXXXXXXXXXXXXX->bOverride_HeightOverride = 1;
	//XXXXXXXXXXXXXXX->bOverride_HeightOverride = 1;
}


void UW_ParameterPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}






void UW_ParameterPanel::ShowParameterPanel(AUnit* _Unit)
{
	SetVisibility(ESlateVisibility::Visible);  				// ** Visible,  Hidden,  Collapsed
	UpdateParameterPanel(_Unit);
}

void UW_ParameterPanel::HideParameterPanel()
{
	SetVisibility(ESlateVisibility::Collapsed);  				// ** Visible,  Hidden,  Collapsed
}


void UW_ParameterPanel::UpdateParameterPanel(AUnit* _Unit)
{
	if (!_Unit)
		return;
	if (!_Unit->UnitParam)
		return;

/*	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

	float slotSize = gameMode->FastPanelSlotSize;
	int32 fastPanelSlotMaxNum = gameMode->FastPanelSlotNum;
	int32 unitFastPanelSlotNum = _FastPanelUnit->FastPanelSlots.Num();
	int32 SlotObjNum = SlotObj.Num();
	UTexture2D* SlotBackTexture = _FastPanelUnit->MainInvertorySlotTexture;
	if (!SlotBackTexture)
		SlotBackTexture = gameMode->MainInvertorySlotTexture;
*/


	UUnitParamComponent& UnitParamComponent = *_Unit->UnitParam;

/*	+++++++
	float potentialHP = UnitParamComponent->GetPotentialHP();
	//float critHP = 0.f;
	if(HP <= 0.f)
		
*/



	FVector2D fullHealthBar_Width_UI = SizeBox_FullHealthBar->GetCachedGeometry().GetLocalSize(); // ** WidthOverride;
	float maxHP = UnitParamComponent.GetParam(EUnitParam::MaxHP);
	float HP = UnitParamComponent.GetParam(EUnitParam::HP);
	float HP_relate_UI = 0.f;

	if (HP <= 0.f)
	{
		float critHP_Max = UnitParamComponent.GetParam(EUnitParam::CritHP);
		float critHP_Curr = -1 * HP;
		HP_relate_UI = fullHealthBar_Width_UI.X * critHP_Curr / critHP_Max;
		Border_Hp->SetBrushColor(FLinearColor(1.0f, 0.984942f, 0.588542f, 1.0f));			// ** White-Yellow  (Dealy-low-HP)

	}
	else
	{
		HP_relate_UI = fullHealthBar_Width_UI.X * HP / maxHP;
		float minHP = UnitParamComponent.GetParam(EUnitParam::MinHP);

		if (HP < minHP)
			Border_Hp->SetBrushColor(FLinearColor(1.0f, 0.866329f, 0.020833f, 1.0f));		// ** Yellow  (low-HP)
		
		else
			Border_Hp->SetBrushColor(FLinearColor(1.0f, 0.f, 0.039766f, 1.0f));			// ** Red  (Normal-HP)
	}

	float potentialHP = UnitParamComponent.GetParam(EUnitParam::PotentialHP);
	float potentialHP_relate_UI = fullHealthBar_Width_UI.X * potentialHP / maxHP;;

	SizeBox_HP->SetWidthOverride(HP_relate_UI);
	SizeBox_PotentialHP->SetWidthOverride(potentialHP_relate_UI);


	//---SizeBox_MinHP->SetWidthOverride(0);   // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//---SizeBox_CritMinHP->SetWidthOverride(0);   // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//YYYYYYYYYY->SetWidthOverride(XXXXXXXXXX);
	//YYYYYYYYYY->SetWidthOverride(XXXXXXXXXX);





	
	//----InventorySizeBox->bOverride_HeightOverride = 1;
	//----InventorySizeBox->SetHeightOverride((slotSize * slotsNumShownOnScreen) + slotSize / 2);
	//----InventorySizeBox->bOverride_WidthOverride = 1;
	//----InventorySizeBox->SetWidthOverride(slotSize + slotSize / 2);

	//----SlotObj[_SlotIndex]->PermanentSelectImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

	//---DurationBar->SetPercent(val);
	//---DurationBar->SetVisibility(ESlateVisibility::Visible);

	//---ImgItem->SetBrushSize(FVector2D(PlayerPAWN->FastPanel_Cell_Size, PlayerPAWN->FastPanel_Cell_Size));
	//---BackgroungImage->SetBrushSize(FVector2D(PlayerPAWN->FastPanel_Cell_Size, PlayerPAWN->FastPanel_Cell_Size));
	//---BackgroungImage->SetBrushFromTexture(ImgBackgroundTexture, false);

	//---float Width = (PlayerPAWN->Inventory_Cell_Size * TemporareDrugingItem.SizeX / 5);
	//---Width -= 60 / Width;
	//---float Height = (PlayerPAWN->Inventory_Cell_Size * TemporareDrugingItem.SizeY / 5);
	//---Height -= 60 / Height;
	//---float X, Y;
	//---PC->GetMousePosition(X, Y);
	//---W_DROP_DragSlot->SetPositionInViewport(FVector2D(X - Width, Y - Height), true);
	//---W_DROP_DragSlot->SetPositionInViewport(FVector2D(X, Y), true);
}