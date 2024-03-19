
// #include "Base/UnitEffect/Struct/UnitEffectDT.h"


#include "UnitEffectDT.h"

#include "../../Base/BaseGameMode.h"

#include "../UnitEffectRealizer.h"

#include "../../Unit/Base/Unit.h"



#if WITH_EDITOR 

void FUnitEffectDT::SetDescriptionText()
{

	if (UnitEffectRealizer && UnitEffectRealizer != LastUnitEffectRealizer_EDITTOR)
	{
		LastUnitEffectRealizer_EDITTOR = UnitEffectRealizer;

		if(UUnitEffectRealizer* unitEffectRealizerCDO =
			UnitEffectRealizer->GetDefaultObject<UUnitEffectRealizer>())
		{
			for (int32 i = 0; i < unitEffectRealizerCDO->HELPER__UnitEffectParamDescription.Num(); ++i)
			{
				HELPER__UnitEffectParamDescription.Add(unitEffectRealizerCDO->HELPER__UnitEffectParamDescription[i]);
			}
		}
	}
	else if(!UnitEffectRealizer)
	{
		HELPER__UnitEffectParamDescription.Reset();
		LastUnitEffectRealizer_EDITTOR = nullptr;
	}
}

#endif



FUnitEffectDT& FUnitEffectDT::operator=(const FUnitEffectDT& _Other)

{

	if(this == &_Other)
		return *this;

	this->EffectImage = _Other.EffectImage;

	this->UnitEffectRealizer = _Other.UnitEffectRealizer;
	this->IsUnitEffectCanBeCanel = _Other.IsUnitEffectCanBeCanel;

	for(int32 i = 0; i < _Other.GenertateNewTraseReselectorIndex.Num(); ++i)
		this->GenertateNewTraseReselectorIndex.Add(_Other.GenertateNewTraseReselectorIndex[i]);

	// ------------------------------------------------------------------------------

	for (int32 i = 0; i < _Other.UnitParamModifier.Num(); ++i)
		this->UnitParamModifier.Add(_Other.UnitParamModifier[i]);
	for (int32 i = 0; i < _Other.Location.Num(); ++i)
		this->Location.Add(_Other.Location[i]);
	for (int32 i = 0; i < _Other.Rotation.Num(); ++i)
		this->Rotation.Add(_Other.Rotation[i]);
	for (int32 i = 0; i < _Other.Unit.Num(); ++i)
		this->Unit.Add(_Other.Unit[i]);
	//+++for (int32 i = 0; i < _Other.Object.Num(); ++i)
		//+++this->Object.Add(_Other.Object[i]);
	//+++for (int32 i = 0; i < _Other.Item.Num(); ++i)
		//+++this->Item.Add(_Other.Item[i]);
	for (int32 i = 0; i < _Other.Float.Num(); ++i)
		this->Float.Add(_Other.Float[i]);
	for (int32 i = 0; i < _Other.StMesh.Num(); ++i)
		this->StMesh.Add(_Other.StMesh[i]);
	for (int32 i = 0; i < _Other.SkMesh.Num(); ++i)
		this->SkMesh.Add(_Other.SkMesh[i]);
	for (int32 i = 0; i < _Other.Unit_class.Num(); ++i)
		this->Unit_class.Add(_Other.Unit_class[i]);
	for (int32 i = 0; i < _Other.VisualEffect.Num(); ++i)
		this->VisualEffect.Add(_Other.VisualEffect[i]);
	for (int32 i = 0; i < _Other.VisualEffectSocket.Num(); ++i)
		this->VisualEffectSocket.Add(_Other.VisualEffectSocket[i]);
	//+++for (int32 i = 0; i < _Other.Sound.Num(); ++i)
		//+++	this->Sound.Add(_Other.Sound[i]);

	return *this;
}