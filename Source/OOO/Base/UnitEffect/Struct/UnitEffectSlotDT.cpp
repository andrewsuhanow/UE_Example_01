
// #include "Base/UnitEffect/Struct/UnitEffectSlotDT.h"


#include "UnitEffectSlotDT.h"

#include "../../Base/BaseGameMode.h"

#include "../UnitEffectRealizer.h"

#include "../../Unit/Base/Unit.h"



bool FUnitEffectSlotDT::Init(AUnit* _UnitOwner)
{
	if(!UnitEffectRealizer)
		return false;

	UnitOwner = _UnitOwner;

	UUnitEffectRealizer* unitEffectRealizerCDO =
		UnitEffectRealizer->GetDefaultObject<UUnitEffectRealizer>();

	if (unitEffectRealizerCDO)
		return unitEffectRealizerCDO->InitEffect(*this, _UnitOwner);

	return false;
}


void FUnitEffectSlotDT::Continue(AUnit* _UnitOwner)
{
	if (!UnitOwner)
		return;

	UUnitEffectRealizer* unitEffectRealizerCDO =
		UnitEffectRealizer->GetDefaultObject<UUnitEffectRealizer>();
	if (unitEffectRealizerCDO)
		unitEffectRealizerCDO->ContinueEffect(*this, _UnitOwner);
}



void FUnitEffectSlotDT::Finish()
{

	if (!UnitOwner)
		return;

	UUnitEffectRealizer* unitEffectRealizerCDO =
		UnitEffectRealizer->GetDefaultObject<UUnitEffectRealizer>();
	if (unitEffectRealizerCDO)
		return unitEffectRealizerCDO->FinishEffect(*this, UnitOwner);
}

void FUnitEffectSlotDT::Cancel()
{

}






/*
void FUnitEffectSlotDT::ActivateUpdate()
{
	if (!UnitOwner)
		return;

	ABaseGameMode* GameMode = Cast<ABaseGameMode>(UnitOwner->GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		float roundTime = GameMode->GetRoundTime();// ** *_UnitOwner->GetWorld()->GetDeltaSeconds();
		UpdateDelegate.BindRaw(this, &FUnitEffectDT::Update);
		UnitOwner->GetWorld()->GetTimerManager().SetTimer(TH_Update, UpdateDelegate, roundTime, false);
	}

}
*/
/*
void FUnitEffectSlotDT::Update()
{
	if (!UnitOwner)
		return;


	if (UnitParamModifier.Num() > 0)
	{
		if (UnitParamModifier[0].ModifierType > 0)
		{
			--UnitParamModifier[0].ModifierType;

			UUnitEffectRealizer* unitEffectRealizerCDO =
				UnitEffectRealizer->GetDefaultObject<UUnitEffectRealizer>();
			if (unitEffectRealizerCDO)
				unitEffectRealizerCDO->UpdateEffect(*this, UnitOwner);


			ActivateUpdate();
			return;
		}
	}

	UnitOwner->GetWorld()->GetTimerManager().ClearTimer(TH_Update);
	Finish();
}
*/




//FUnitEffectDT& FUnitEffectDT::operator=(const FUnitEffectDT& _Other)
FUnitEffectSlotDT& FUnitEffectSlotDT::CastSlotEffectFromUnitEffect(const FUnitEffectDT& _Other)
{

	//*this = _Other;
	//static_cast<FUnitEffectDT>(*this) = _Other;
	static_cast<FUnitEffectDT&>(*this) = _Other;

	return *this;

/*
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

		*/
		
}