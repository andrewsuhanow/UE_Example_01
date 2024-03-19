
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "W_ParameterPanel.generated.h"

class USizeBox;
class UProgressBar;
class UBorder;


UCLASS()
class OOO_API UW_ParameterPanel : public UUserWidget
{
	GENERATED_BODY()

			   

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	USizeBox* SizeBox_Armor;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	UBorder*  Border_Armor;

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	UProgressBar* ManaBar;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	UProgressBar* Stamina;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	UProgressBar* MagikShieldBar;

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	USizeBox* SizeBox_FullHealthBar;

	//---UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	USizeBox* SizeBox_CritMinHP;
	//---UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	USizeBox* SizeBox_MinHP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	USizeBox* SizeBox_HP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	USizeBox* SizeBox_PotentialHP;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	UBorder* Border_Hp;


	//---UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	UBorder*  Border_RestHP;
	//---UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	UBorder* CritMinHP;
	//---UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	UBorder* MinHP;
	//---UPROPERTY(BlueprintReadOnly, meta = (BindWidget))	UBorder* RealHP;








public:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	   	



	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ShowParameterPanel(class AUnit* _Unit);
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void HideParameterPanel();
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateParameterPanel(class AUnit* _Unit);



};

