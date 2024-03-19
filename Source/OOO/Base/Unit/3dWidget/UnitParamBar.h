

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitParamBar.generated.h"

UCLASS()
class OOO_API AUnitParamBar : public AActor
{
	GENERATED_BODY()
	
public:	

	AUnitParamBar();

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION()
		void Init(class AUnit* _UnitOwner, TSubclassOf<class UW_UnitParamBar>& _W_UnitParamBar_class);


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		USceneComponent* RootComp;

	UPROPERTY(EditAnywhere, Category = "OOO_Unit_Bar")
		class UWidgetComponent* W_UnitParamBarComponent;
	UPROPERTY()
		class UW_UnitParamBar* W_UnitParamBar;

public:

	UFUNCTION()
		void ShowUnitParamBar();
	UFUNCTION()
		void HideUnitParamBar();
	UFUNCTION()
		void UpdateUnitParamBar();
	UFUNCTION()
		void UpdateUnitParamBarEffect(int32 _EffectIndex);

/*
public:	

	virtual void Tick(float DeltaTime) override;
*/
};
