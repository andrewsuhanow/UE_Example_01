
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "TMoveToPoint.generated.h"

UCLASS()
class OOO_API UTMoveToPoint : public UTask
{
	GENERATED_BODY()

public:

	UTMoveToPoint();

public:

	UPROPERTY()			AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void TaskPerformance(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	UPROPERTY()			FTimerHandle TH_Move;
	UFUNCTION()			void MoveTick();
};



