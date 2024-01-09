
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Base/Task.h"
#include "../../Item/Struct/ItemDT.h"
#include "../../Amunition/WeaponDT.h"

#include "../Enum/RotateToActorType.h"

#include "TWeaponAttack.generated.h"


UENUM()
enum class EDistType : uint8
{
	min,
	max,
	optimal
};


UCLASS()
class OOO_API UTWeaponAttack : public UTask
{
	GENERATED_BODY()

	

public:

	UTWeaponAttack();


public:

	// ***** Helper data *****

	// ** few target in one Attack
	UPROPERTY()			TArray<AActor*> CurrHittingActors;
	UPROPERTY()			FHitResult TraceHit;
	UPROPERTY()			FVector StartPoint;
	UPROPERTY()			FVector EndPoint;
	UPROPERTY()			float WeaponLenght = 0.f;

	UPROPERTY()			bool IsUsingAnimate = false;
	//UPROPERTY()			bool IsTaskFinish = false;



	// ***** Base data *****

	UPROPERTY()			AUnit* LastTargetActor = nullptr;
	UPROPERTY()			AUnit* CurrTargetUnit = nullptr;
	UPROPERTY()			AActor* CurrTargetActor = nullptr;

	// ++++  mHasBestPositionToFire = bool;
	// ++++  mBestPositionToFire = FVector;		// ** finded EQS

	



	// ***** Attack series time *****
	UPROPERTY()			float TimeAttackTickLeft = 0.f;
	UPROPERTY()			FTimerHandle TH_WeaponAttackTick;
	UFUNCTION()			void WeaponAttackTick();


	// ***** Attack series *****
	UPROPERTY()			int32 ActualWpnAttackIndex = 0;
	UPROPERTY()			TArray<int32> SeriesAttackIndexes;
	UPROPERTY()			int32 CurrentAttackInSeries = -1;
	UPROPERTY()			class UWeaponDT* LastWeaponDT = nullptr;
	UFUNCTION()			void ResetAttackData(class AUnitAI* _OwnerAI);
	UFUNCTION()			bool IsInAttackSeries();
	UFUNCTION()			int32 GenerateAttackIndex(class AUnitAI* _OwnerAI, 
		class AWeaponWorldItem* _WeaponItem, class UWeaponDT* _CurrWeaponDT);
	UFUNCTION()			int32 CheckAndGetNextAttackIndex();


	// *****  Series Tactical-Move  *****
	UPROPERTY()			int32  TacticalMoveStep = -1;
	UPROPERTY()			int32  TotalTacticalMoveStep = 0;
	///UFUNCTION()			bool IsInTacticalMove();
	UFUNCTION()			bool IsTacticalMoveOwerflow(class AWeaponWorldItem* _WeaponItem);
	UFUNCTION()			bool IsTacticalMoveTotalOwerflow();
	UFUNCTION()			void ResetTacticalMoveData();
		// ** How much Tactical-Move(Limit) steps Unit do betwean attcks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Parameter")
		int32  TotalTacticalMoveStepMAX = 19;


	   	 

public:

	UFUNCTION()
		bool CheckAndMoveFromCloserDist(class AUnitAI* _OwnerAI, class AUnit* _TargetUnit, 
			class AWeaponWorldItem* _WeaponItem = nullptr, 
			ETaskCauser _TaskCauser = ETaskCauser::ChildTask);

	UFUNCTION()
		bool CheckAndMoveMaxDist(class AUnitAI* _OwnerAI, UWeaponDT* _WeaponDT);

	UFUNCTION()
		bool CheckOnTacticalMove(class AUnitAI* _OwnerAI, AActor* _CurrTargetActor, 
			class AWeaponWorldItem* _WeaponItem);



	// ----------------------------------------



	UFUNCTION()
		ERotateToActorType GetTargetRelativeRotPosition(class AUnitAI* _OwnerAI, AActor* _CurrTargetActor);

	UFUNCTION() // **  SelfOprimal*2  orIF(<)  SelfMax orIF(<)  TargetOptimal
		float GetDist_SafeSparingWithTarget(class AUnitAI* _OwnerAI, AActor* _CurrTargetActor, UWeaponDT* _WeaponDT = nullptr);

	UFUNCTION()
		float GetDist_WeaponParam(AActor* _Actor, EDistType _WpnDistType, UWeaponDT* _WeaponDT = nullptr);

	UFUNCTION()
		FVector FindLoc_OnDistFromTargetByDir(class AUnitAI* _OwnerAI, AActor* _TargetActor, float _Dist = 0.f);

	UFUNCTION()
		FVector FindLoc_GoRndSideAroundTarget(class AUnitAI* _OwnerAI, class AUnit* _TargetUnit, ERotateToActorType _RotateToActorType);

	UFUNCTION()
		FVector FindLoc_GoForwardToTargetOnDist(class AUnitAI* _OwnerAI, class AUnit* _TargetUnit, float _Dist = 0.f);



	// ----------------------------------------


	UFUNCTION()
		void RayCast(class AUnitAI* _OwnerAI, FHitResult& _TraceHit,
			FVector _StartPoint, FVector _EndPoint);

	UFUNCTION()
		void GenerateWeaponContactRayCast(class AUnitAI* _OwnerAI,
			class AWeaponWorldItem* _WeaponItem, FHitResult& _TraceHit);

	UFUNCTION()
		void GenerateWeaponRangeRayCast(class AUnitAI* _OwnerAI,
			class AWeaponWorldItem* _WeaponItem, FHitResult& _TraceHit,
			float _RayDist = -1.f);

	UFUNCTION()
		void GenerateWeaponBoundHit(class AUnitAI* _OwnerAI, TArray<FHitResult>& _HitResult,
			FVector _StartPoint, FVector _EndPoint, float _SpherDiametr);

	UFUNCTION()
		bool CheckClearVisionToActor(class AUnitAI* _OwnerAI, class AUnit* _Target);

	UFUNCTION()
		bool IsWayCorrect_RayCastCapsule(class AUnitAI* _OwnerAI, FVector _EndPoint);


	// ----------------------------------------


	UFUNCTION()
		bool CheckAndFindClearVisionPosition(class AUnitAI* _OwnerAI);

	UFUNCTION()
		void FindBestFiringPoint(class AUnitAI* _OwnerAI);		// ** Start EQS

	UFUNCTION()
		bool CorectDistBeforeAttack(class AUnitAI* _OwnerAI, AActor* _CurrTargetActor, class AWeaponWorldItem* _WeaponItem);
	   	  
	UFUNCTION()
		bool AttackAction(class AUnitAI* _OwnerAI);
	   	  


public:

	UPROPERTY()	AUnitAI* OwnerAI;

	virtual void StartTask(class AUnitAI* _OwnerAI) override;

	virtual void ContinueTask(class AUnitAI* _OwnerAI) override;

	virtual void OnAnimationNotify(class AUnitAI* _OwnerAI, FString _NotifyName) override;

	virtual void TaskComplit(class AUnitAI* _OwnerAI) override;

	virtual void BreakTask(class AUnitAI* _ThisAI) override;

	virtual void ResetTask(class AUnitAI* _OwnerAI) override;

	virtual bool IdentifyTask(class AUnitAI* _ThisAI) override;



	// ** ---------------------  Static func  ------------------------

public:

	UFUNCTION()
		static void SetAttackData_AttackUnit(FTaskData& _TaskData, AActor* _TargetActor, int32 _AttackIndex = -1);



};



