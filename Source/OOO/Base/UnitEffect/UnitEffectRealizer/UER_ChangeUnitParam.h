
#pragma once

#include "CoreMinimal.h"
#include "../UnitEffectRealizer.h"



#include "UER_ChangeUnitParam.generated.h"


UCLASS()
class OOO_API UUER_ChangeUnitParam : public UUnitEffectRealizer
{
	GENERATED_BODY()
	
public:

	UUER_ChangeUnitParam();

public:

	virtual bool InitEffect(struct FUnitEffectSlotDT& _UnitEffectSlotDT, class AUnit* _UnitOwner) override;

	virtual bool ContinueEffect(struct FUnitEffectSlotDT& _UnitEffectSlotDT, class AUnit* _UnitOwner) override;

	virtual void FinishEffect(struct FUnitEffectSlotDT& _UnitEffectSlotDT,	class AUnit* _UnitOwner) override;

	virtual void CancelEffect(struct FUnitEffectSlotDT& _UnitEffectSlotDT, class AUnit* _UnitOwner) override;
};
