

// #include "Base/Ability/AbilityDT.h"
#include "AbilityDT.h"

UAbilityDT::UAbilityDT()
{

}



UTexture2D* UAbilityDT::GetImage() const
{
	return AbilityImage;
}




#if WITH_EDITOR 

void UAbilityDT::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{

	// ** Desctiption "UAbilityDT.AbilityStep.UnitEffectDT"
	for (int32 as = 0; as < AbilityStep.Num(); ++as)
	{
		for (int32 uf = 0; uf < AbilityStep[as].UnitEffectDT.Num(); ++uf)
		{
			AbilityStep[as].UnitEffectDT[uf].SetDescriptionText();
		}
	}
}

#endif
