
//#include "Base/Unit/3DWidget/W_UnitParamBar.h"

#include "W_UnitParamBar.h"

#include "../Base/Unit.h"

//#include "../../HUD/Widget/Slot/W_EffectSlot.h"

#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
//---#include "Components/ScrollBox.h"


void UW_UnitParamBar::NativeConstruct()
{
	Super::NativeConstruct();

	//HealthBar->SetPercent(1.f);
	ArmorBar->SetPercent(1.f);

}


// ** Set

void UW_UnitParamBar::UpdateBar(AUnit* _Unit)
{

}

void UW_UnitParamBar::UpdateHealthBar(float CurrVal, float MaxVal)
{
	//HealthBar->SetPercent(CurrVal / MaxVal);
}

void UW_UnitParamBar::UpdateArmorBar(float CurrVal, float MaxVal)
{
	ArmorBar->SetPercent(CurrVal / MaxVal);
}




// ** Show

void UW_UnitParamBar::ShowhBar(bool isVisible)
{



	if (isVisible)
	{
		//HealthBar->SetVisibility(ESlateVisibility::Visible);
		ArmorBar->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		//HealthBar->SetVisibility(ESlateVisibility::Collapsed);
		ArmorBar->SetVisibility(ESlateVisibility::Collapsed);
	}
}





