
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_UnitParamBar.generated.h"

class USizeBox;
class UProgressBar;
class UScrollBox;
class UBorder; 



UCLASS()
class OOO_API UW_UnitParamBar : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//---UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//---	UProgressBar* HealthBar;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))		
		USizeBox* SizeBox_FullHealth;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))		
		USizeBox* SizeBox_CritMinHP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))		
		USizeBox* SizeBox_MinHP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))		
		USizeBox* SizeBox_RealHP;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UBorder* CritMinHP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UBorder* MinHP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UBorder* RealHP;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* ArmorBar;



public:

	//UEntityBarWidget();
	virtual void NativeConstruct() override;


	UFUNCTION(BlueprintCallable)
		void UpdateBar(AUnit* _Unit);
	UFUNCTION(BlueprintCallable)
		void UpdateHealthBar(float CurrVal, float MaxVal);
	UFUNCTION(BlueprintCallable)
		void UpdateArmorBar(float CurrVal, float MaxVal);


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))		
		UScrollBox* EffectSlotScroll;
//----	UPROPERTY()
//----		TArray<class UW_EffectSlot*> W_EffectSlot;


	UFUNCTION(BlueprintCallable)
		void ShowhBar(bool isVisible);


	
};
