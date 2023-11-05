
//#include "Base/HUD/Widget/Slot/W_Slot.h"
#include "W_Slot.h"

#include "../../../Unit/Base/Unit.h"



#include "Components/Image.h"


#include "Blueprint/WidgetBlueprintLibrary.h"   // UWidgetBlueprintLibrary::DetectDragIfPressed()

/*
#include "W_DropSlot.h" // Drop Cell
#include "Components/SizeBox.h"
*/

//#include "Kismet/GameplayStatics.h"   //   GetAllActorsOfClass




void UW_Slot::NativePreConstruct()
{
	Super::NativePreConstruct();
	

}

void UW_Slot::NativeConstruct()
{
	Super::NativeConstruct();

	SelectImage1->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	SelectImage2->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	SelectImage3->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	
	
}



void UW_Slot::SetImage(UTexture2D* ItemImage)
{

	ImgItem->SetBrushFromTexture(ItemImage, false);
	ImgItem->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

	if (!ItemImage)
	{
		ImgItem->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	}
}

void UW_Slot::SetBackgroundImage(UTexture2D* _BackgroundImage)
{
	BackgroungImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	BackgroungImage->SetBrushFromTexture(_BackgroundImage, false);
}


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




// ***************************************************************************
// ******************************    Dg & Dp    ******************************

FReply UW_Slot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	//UE_LOG(LogTemp, Log, TEXT("WWWWWWWWWWWWWW  Mouse Down"));



	
	//Reply.NativeReply = FReply::Handled();
	//return FReply::Unhandled();
	FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return reply.NativeReply;
}


// ** FFFFFFFFFF  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
FReply UW_Slot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) 
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);





	//Reply.NativeReply = FReply::Handled();
	//return FReply::Unhandled();
	FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton); 
	return reply.NativeReply;
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