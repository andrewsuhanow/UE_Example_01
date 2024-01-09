
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "TParrir.generated.h"

UCLASS()
class OOO_API UTParrir : public UTask
{
	GENERATED_BODY()

public:

	UTParrir();

public:

	bool IsUsingAnimate = true;

	float fTimeLostControll = 0.0f;

public:

	UPROPERTY()			AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void OnAnimationNotify(class AUnitAI* _OwnerAI, FString _NotifyName) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	UPROPERTY()			FTimerHandle TH_Parrir;
	UFUNCTION()			void ParrirTick();
};



