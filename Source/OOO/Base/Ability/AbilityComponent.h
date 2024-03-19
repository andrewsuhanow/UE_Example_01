
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Controller/Enum/TargetType.h"
#include "Struct/AbilityList.h"

#include "AbilityComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OOO_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;

public:

	UAbilityComponent();
public:

//----	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
//----		TArray< TSubclassOf<class UAbilityDT> > DefaultAbilities_Class;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<FAbilityList> UnitAbilityList;



//public:

	// +++++UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
	// +++++   PreferAttackAbility
	// +++++   PreferSuportAbility
	// +++++   PreferControllAbility

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void Init();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		int32 GetAbilityIndexByName(FName _AbilityName);
	UFUNCTION(BlueprintCallable, Category = "OOO")
		FName GetAbilityNameByIndex(int32 _AbilityIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddAbilityByName(FName _AbilityName);
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void AddAbilityByClass(TSubclassOf<class UAbilityDT>& _AbilityDTClass);
	//	void AddAbilityByClass(EAbilityType Ability);


	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool GetUnitAbilityByIndex(int32 _AbilityIndex, class UAbilityDT*& _AbilityRef);

	//---------UFUNCTION(BlueprintCallable, Category = "OOO")
	//------------	bool IsHasHoldingPose();

	//UFUNCTION(BlueprintCallable, Category = "OOO")
	//-------bool GetPreAbilityHoldingPose(class UAbilityDT*& _AbilityRef, int32& _StepIndex, struct FAbilityStep*& _AbilityStep);


	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool FindUnitAbilityByName(FName _AbilityName, class UAbilityDT*& _AbilityRef);

	//+++++UFUNCTION(BlueprintCallable, Category = "OOO")
	//+++++	TSubclassOf<class UAbilityDT> GetAbilityClass_ByName(FName _AbilityName);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		ETargetType GetAbilityTargetType(int32 _AbilityIndex, int32& _TargetsCount);


/*
public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 AbilityHolding = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 AbilitySelected = -1;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		int32 GetHoldingAbility() const;
	UFUNCTION(BlueprintCallable, Category = "OOO")
		int32 GetSelectedAbility() const;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetHoldingAbility(int32 _Index);
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetSelectedAbility(int32 _Index);
*/
};
