
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "TRotateToPointNormal.generated.h"

UCLASS()
class OOO_API UTRotateToPointNormal : public UTask
{
	GENERATED_BODY()

public:

	UTRotateToPointNormal();

public:

	UPROPERTY()			AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void TaskPerformance(class AUnitAI* _OwnerAI) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	UPROPERTY()			FTimerHandle TH_Rotate;
	UFUNCTION()			void RotateTick();

	float GetAngleRotateToPoint(class AUnitAI* _OwnerAI, FVector _VectorToTarget);

};



