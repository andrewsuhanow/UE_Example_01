
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

//#include "../../../Controller/Task/Base/Task.h"

#include "W_TaskQueuePanel.generated.h"


class UHorizontalBox;  //#include "Components/VerticalBox.h"
//class UScrollBox;
class USizeBox;

UCLASS()
class OOO_API UW_TaskQueuePanel : public UUserWidget
{
	GENERATED_BODY()

			   

public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;



	   	 

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowTaskQueuePanel(class AUnit* _Unit,
			UTexture2D*& _CurrTaskIcon,
			TArray<UTexture2D*>& _TasksIcon,
			TArray<int32>& _TasksIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void HideTaskQueuePanel();


	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateTaskQueuePanel(class AUnit* _Unit,
			UTexture2D*& _CurrTaskIcon,
			TArray<UTexture2D*>& _TasksIcon,
			TArray<int32>& _TasksIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddCellToTaskQueue(ABaseGameMode* _GameMode, float _SlotSize, UTexture2D* SlotBackTexture);

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		USizeBox* TaskQueueSizeBox;					// ** Border size					
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		UHorizontalBox* TaskQueueHorizontalBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class UW_Slot*> SlotObj;



};

