// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../../../Item/Struct/ItemDT.h"
#include "../../../Inventory/Enum/SlotType.h"

#include "W_DropSlot.generated.h"

class UImage;
class UTextBlock;
class USizeBox;


UCLASS()
class OOO_API UW_DropSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:


	//UPROPERTY()
	//	class UW_Inventory* W_Parent;

	UPROPERTY()
		class AUnit* SelectUnit;

	// ** MainPanel, GlobalPanel, EquipPanel, FastPanel
	UPROPERTY()
		ESlotType PanelTypeFrom = ESlotType::none;

	UPROPERTY()
		int32 IndexInPanel = -1;



	// ** Temporare Item
	UPROPERTY()
		FItemDT ItemData;
	
	//+++	FAbilityDT* AbilityData;



	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))	
		USizeBox* SzBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))	
		UImage* Image;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* BackgroundImage;

	

};
