

// #include "Base/Ability/AbilityComponent.h"
#include "AbilityComponent.h"

#include "AbilityDT.h"

#include "../Base/BaseGameMode.h"



UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UAbilityComponent::Init()
{
	// ** AUnit* UnitOwner = Cast<AUnit>(GetOwner());
/*+++++++++++++++++++++++++
	int32 mainInvCollNum = UnitOwner->GetMainInvCollNum();
	int32 fullRowNum = UnitOwner->FullRowNum;


	for (int32 i = MainInventorySlot.Num(); i < fullRowNum; ++i)
		AddSlotsRowToMainInventor(mainInvCollNum);
*/

//	for (int32 i = 0; i < DefaultAbilities_Class.Num(); ++i)
	{
//		UAbilityDT* newAbility = NewObject<UAbilityDT>(this);

//		Abilities.Add(Ability, *Row);

	}



}


int32 UAbilityComponent::GetAbilityIndexByName(FName _AbilityName)
{
	for (int32 i = 0; i < UnitAbilityList.Num(); ++i)
	{
		UAbilityDT* abilityCDO = UnitAbilityList[i].Ability_class->GetDefaultObject<UAbilityDT>();
		if (abilityCDO)
		{
			if (abilityCDO->AbilitytName == _AbilityName)
			{
				return i;
			}
		}
	}
	return -1;
}

FName UAbilityComponent::GetAbilityNameByIndex(int32 _AbilityIndex)
{
	if (_AbilityIndex < 0 && _AbilityIndex >= UnitAbilityList.Num())
		return FName("none");

	UAbilityDT* abilityCDO = UnitAbilityList[_AbilityIndex].Ability_class->GetDefaultObject<UAbilityDT>();
	if (abilityCDO)
	{
		return abilityCDO->AbilitytName;
	}
	return FName("none");
}





void UAbilityComponent::AddAbilityByName(FName _AbilityName)
{
/*	FString path = FString("/Game/Core/Ability/AbilitieDT/");
	FString fullPath = path + _AbilityName.ToString()+ FString(".") + _AbilityName.ToString();

	UBlueprint* class_BP = LoadObject<UBlueprint>(nullptr, *fullPath);
	if (class_BP)
	{
		TSubclassOf<UAbilityDT> SubClass = (UClass*)class_BP->GeneratedClass;
		
	}
*/	
//+++++	TSubclassOf<UAbilityDT> SubClass = GetAbilityClass_ByName(_AbilityName);
//+++++	if(SubClass)
//+++++		AddAbilityByClass(SubClass);
}



void UAbilityComponent::AddAbilityByClass(TSubclassOf<UAbilityDT>& _AbilityDTClass)
{

	if (!_AbilityDTClass)
		return;

	UAbilityDT* abilityCDO = _AbilityDTClass->GetDefaultObject<UAbilityDT>();
	if (abilityCDO)
	{

		FAbilityList newAbility;
		newAbility.Ability_class = _AbilityDTClass;
		newAbility.ConsecutiveQuantity = abilityCDO->MaxConsecutiveQuantity;

		UnitAbilityList.Add(newAbility);
	}

/*++++++++++++
	UAbilityDT* AbilityCDO = _AbilityDTClass->GetDefaultObject<UAbilityDT>();
	Abilities.Add(AbilityCDO->AbilitytName,  _AbilityDTClass);
*/

//---------------------------------
/*
//	ABaseGameMode* GmMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
//	if (!GmMode)
//		return;



	for (int32 i = 0; i < DefaultAbilities_Class.Num(); ++i)
	{
		UAbilityDT* newAbility = NewObject<UAbilityDT>(this);

		Abilities.Add(Ability, *Row);

	}


	for (auto It : GmMode->GetGameAbilityArchive()->GetRowMap())
	{
		FAbilityDT* Row = reinterpret_cast<FAbilityDT*>(It.Value);
		if (Row->AbilityType == Ability)
		{
			Abilities.Add(Ability, *Row);
			break;
		}
	}
*/
}



bool UAbilityComponent::GetUnitAbilityByIndex(int32 _AbilityIndex, UAbilityDT*& _AbilityRef)
{
	if(_AbilityIndex < 0 || _AbilityIndex >= UnitAbilityList.Num())
		return false;

	_AbilityRef = UnitAbilityList[_AbilityIndex].Ability_class->GetDefaultObject<UAbilityDT>();
	if (_AbilityRef)
		return true;
	return false;
}

/*-------------------
bool UAbilityComponent::IsHasHoldingPose()
{
	return (AbilityHolding != -1 || AbilitySelected != -1) ? true : false;
}
*/
/*  ---------------------
bool UAbilityComponent::GetPreAbilityHoldingPose(UAbilityDT*& _AbilityRef, int32& _StepIndex, struct FAbilityStep*& _AbilityStep)
{
	int32 stepsNum = _AbilityRef->PreAbilityPoseStep.Num();
	while (_StepIndex >= stepsNum && _StepIndex >= 0)
	{
		--_StepIndex;
	}


	if (_StepIndex < 0 )
	{
		_AbilityStep = nullptr;
		return false;
	}


	_AbilityStep = &_AbilityRef->PreAbilityPoseStep[_StepIndex];
	return true;
}
*/


bool UAbilityComponent::FindUnitAbilityByName(FName _AbilityName, UAbilityDT*& _AbilityRef) 
{
//--------------------------
/*	TSubclassOf<UAbilityDT> *AbilityClassLink = Abilities.Find(_AbilityName);
	if (AbilityClassLink)
	{
		_AbilityRef = (*AbilityClassLink)->GetDefaultObject<UAbilityDT>();
		if (_AbilityRef)
		{
			return true;
		}
	}

	*/
	return false;
}

/*  ++++++++++++++++++++++++++++
TSubclassOf<UAbilityDT> UAbilityComponent::GetAbilityClass_ByName(FName _AbilityName)
{
	FString path = FString("/Game/Core/Ability/AbilitieDT/");
	FString fullPath = path + _AbilityName.ToString() + FString(".") + _AbilityName.ToString();

	TSubclassOf<UAbilityDT> SubClass = nullptr;

	UBlueprint* class_BP = LoadObject<UBlueprint>(nullptr, *fullPath);
	if (class_BP)
	{
		SubClass = (UClass*)class_BP->GeneratedClass;
	}
	return SubClass;
}
*/




ETargetType UAbilityComponent::GetAbilityTargetType(int32 _AbilityIndex, int32& _TargetsCount)
{
	if (_AbilityIndex < 0 || _AbilityIndex >= UnitAbilityList.Num())
		return ETargetType::Self;

	UAbilityDT* abilityRef;
	GetUnitAbilityByIndex(_AbilityIndex, abilityRef);


	if (abilityRef->DefaultTargetType == ETargetType::Units)
		_TargetsCount = abilityRef->DefaultTargetsCount;
	else
		_TargetsCount = 0;

	return abilityRef->DefaultTargetType;

}






/*
int32 UAbilityComponent::GetHoldingAbility() const
{
	return AbilityHolding;
}
int32 UAbilityComponent::GetSelectedAbility() const
{
	return AbilitySelected;
}

void UAbilityComponent::SetHoldingAbility(int32 _Index)
{
	if (AbilityHolding == _Index)
	{
		AbilityHolding = -1;
		return;
	}
	AbilityHolding = _Index;
}
void UAbilityComponent::SetSelectedAbility(int32 _Index)
{
	if (AbilitySelected == _Index)
	{
		AbilitySelected = -1;
		return;
	}
	AbilitySelected = _Index;
}	
*/


