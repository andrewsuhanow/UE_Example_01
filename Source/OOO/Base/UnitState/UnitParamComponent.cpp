


// #include "Base/UnitState/UnitParamComponent.h"

#include "UnitParamComponent.h"

#include "../Unit/Base/Unit.h"

#include "../Base/BaseGameMode.h"



UUnitParamComponent::UUnitParamComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UUnitParamComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UUnitParamComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UUnitParamComponent::Init()
{
	//AUnit* UnitOwner = Cast<AUnit>(GetOwner());

	int32 arrayCount = 0;

	auto initial = [this, &arrayCount](float _Value, EUnitParam _Type)
	{
		FUnitParamModifier unitParamTMP;
		unitParamTMP.UnitParam = _Type;
		unitParamTMP.ModifierType = ONCE;
		unitParamTMP.Value = _Value;
		UnitParam.Add(unitParamTMP);

		FUnitParamModifier unitParamModificatorTMP;
		unitParamModificatorTMP.UnitParam = _Type;
		unitParamModificatorTMP.ModifierType = ONCE;
		unitParamModificatorTMP.Value = 0.f;
		ParamModificator.Add(unitParamModificatorTMP);

		return arrayCount++;
	};

	iHP = initial(80.f, EUnitParam::HP);

	iCritHP = initial(40.f, EUnitParam::CritHP);

	iMinHP = initial(40.f, EUnitParam::MinHP);

	iMaxHP = initial(120.f, EUnitParam::MaxHP);

	iRegHP = initial(0.1f, EUnitParam::RegHP);

	iPotentialHP = initial(0.1f, EUnitParam::PotentialHP);

	//------------------

	iSP = initial(50.f, EUnitParam::SP);


	// ...............
	// ...............
	// ...............
	// ...............
	// ...............
	// ...............
	// ...............
}




float UUnitParamComponent::GetParam(EUnitParam _Param)
{

	// @@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@			Do Like Map-Imitator
	// @@@@@@@@@@@@@@@@@@
	for (int32 i = 0; i < UnitParam.Num(); ++i)
	{
		if (UnitParam[i].UnitParam == _Param)
		{
			return UnitParam[i].Value + ParamModificator[i].Value;
		}
	}
	return -9999.9f;
}

void UUnitParamComponent::SetParam(EUnitParam _Param, float _Val)
{
	// @@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@			Do Like Map-Imitator
	// @@@@@@@@@@@@@@@@@@
	for (int32 i = 0; i < UnitParam.Num(); ++i)
	{
		if (UnitParam[i].UnitParam == _Param)
		{
			UnitParam[i].Value= _Val;
			return;
		}
	}
}


void UUnitParamComponent::ModParam(EUnitParam _Param, float _Val)
{
	// @@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@			Do Like Map-Imitator
	// @@@@@@@@@@@@@@@@@@
	for (int32 i = 0; i < UnitParam.Num(); ++i)
	{
		if (UnitParam[i].UnitParam == _Param)
		{
			UnitParam[i].Value += _Val;
			return;
		}
	}
}


void UUnitParamComponent::ModParamModificator(EUnitParam _Param, float _Val)
{
	// @@@@@@@@@@@@@@@@@@
	// @@@@@@@@@@@@@@@@@@			Do Like Map-Imitator
	// @@@@@@@@@@@@@@@@@@
	for (int32 i = 0; i < UnitParam.Num(); ++i)
	{
		if (UnitParam[i].UnitParam == _Param)
		{
			ParamModificator[i].Value += _Val;
			return;
		}
	}
}




/*+++++++++++++++++++++++++
float UUnitParamComponent::GetUnitParamByIndex(int32 _Index)
{
	if (_Index < 0 || _Index >= UnitParam.Num())
		return -9999.9f;

	return UnitParam[_Index].Value;
}
*/












