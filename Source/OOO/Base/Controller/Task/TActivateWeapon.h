
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"

#include "TActivateWeapon.generated.h"

UCLASS()
class OOO_API UTActivateWeapon : public UTask
{
	GENERATED_BODY()

public:

	UTActivateWeapon();


public:

	UPROPERTY()	int32 NewWpnIndexForChange = -1;

public:

	UPROPERTY()	AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	//virtual void TaskPerformance(class AUnitAI* _OwnerAI) override;

	virtual void OnAnimationNotify(class AUnitAI* _OwnerAI, FString _NotifyName) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	virtual bool IdentifyTask(class AUnitAI* _ThisAI) override;




	// -----------------------------   Static   -----------------------------


public:

	UFUNCTION()
		static void SetActivateWeaponTaskData_ChangeWpn(FTaskData& _TaskData, AUnit* _SelfUnit,  int32 _NewWeaponIndex = -1);



};



