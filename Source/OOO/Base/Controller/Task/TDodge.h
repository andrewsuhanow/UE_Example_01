
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "TDodge.generated.h"

UCLASS()
class OOO_API UTDodge : public UTask
{
	GENERATED_BODY()

public:

	UTDodge();

public:

	UPROPERTY()			bool IsUsingAnimate = false;

public:

	UPROPERTY()			AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

};



