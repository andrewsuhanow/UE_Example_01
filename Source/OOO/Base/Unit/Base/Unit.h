
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../Enum/UnitPose.h"
#include "../Struct/PoseLocomotion.h"

#include "../../Item/Struct/ItemDT.h"
#include "../../Amunition/WeaponDT.h"

#include "../Struct/FastPanelSlot.h"

#include "../../Controller/Task/Struct/TaskData.h"		// ** SetUnitTask()  ->  AI
#include "../../Controller/Task/Enum/TaskType.h"		// ** SetUnitTask()  ->  AI

#include "../../Base/Enum/TurnBaseGameState.h"

#include "../Enum/UnitGameType.h"

#include "../../Amunition/Enum/WeaponType.h"

// --------------------------------------

#include "Perception/AIPerceptionTypes.h"

#include "Unit.generated.h"





UCLASS()
class OOO_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:

	AUnit();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY()		class ABaseGameMode* GameMode;
	UPROPERTY()		class ABaseGameState* GameState;
	UPROPERTY()		class ABaseHUD* HUD;



	// **  ************************   "Game-Delay" at the BeginPlay()  ************************  
public:

	UFUNCTION()		bool StartGame(bool finalInit = false);


	// **  ************************   Unit_Parameter  ************************
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		EUnitGameType UnitGameType = EUnitGameType::none;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		FName GameName = FName("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		FName GameId;

	// ** Move-Speeds, Rorate-Speeds and pictures (Mod)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		TArray<struct FPoseLocomotion> PoseLocomotionParam;

	// ** Daily-behavior Default class (Queue stored) (for "AI::DailyBhvrTaskDT")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		TSubclassOf<class UDailyBhvrQueue> DailyBhvrQueueClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		TSubclassOf<class AUnitAI> AIController_Class;

	// ** Alternate Set (Priority)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		TSubclassOf<class UHumanAnimInst> AnimInstance_Class;

	// ** (GAME DEBUG)  Gape betwean target-point for stoping    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		float StopDistance = 100.f;



	// *******************   Inventor_Parameter   *******************
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_BigContactWpn = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_SmalContactWpn = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_RangeWpn = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_Pistol = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_Cup = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_Armor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_Clothes = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_Collar = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_Braslet = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_Ring = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* EquipPanelSlotTexture_HeavyStuff = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		TArray<TSubclassOf<class AWorldItem>> InitInvertorItems;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		UTexture2D* MainInvertorySlotTexture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		bool IsInventorSizeFixed = true;
	// ** Invertor slot count (0 - use default feon GameMod)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		int32 FullRowNum = 0;							// ** (Can be Add Using Scroll)
	UFUNCTION(Blueprintcallable, Category = "OOO!_Unit_Parameter")
		int32 GetMainInvCollNum() const;
	UFUNCTION(Blueprintcallable, Category = "OOO!_Unit_Parameter")
		int32 GetMainInvRowNum() const;
	UFUNCTION(Blueprintcallable, Category = "OOO!_Unit_Parameter")
		float MainInventorSlotSize() const;


	// *******************   Unit_Parameter_Getters   *******************
public:

	UFUNCTION(Blueprintcallable, Category = "OOO")
		FTransform GetUnitSocketParam(FName _SocketName);

	UFUNCTION(Blueprintcallable, Category = "OOO")
		float GetUnitCapsuleRadius();

	UFUNCTION(Blueprintcallable, Category = "OOO")
		float GetUnitCapsuleHalfHaight();




	// *******************     AI_Controller    ********************* 
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		class AUnitAI* AI;

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetUnitTask(bool _bAddMoreOne, ETaskType _TaskType, 
			FTaskData _TaskData, 
			ETaskCauser _TaskCauser = ETaskCauser::FractionTask,
			ETaskPriority _TaskPriority = ETaskPriority::Normal);


	// **  ****************      HUD      **************** 

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateTaskQueuePanel_HUD();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateAttacksWpnPanel_HUD();


	// **************************************     PERCEPTION  (Undate reaction)     *******************************************
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		class UAIPerceptionComponent* Perception;
	UPROPERTY()
		class UAISenseConfig_Sight* SightSense;
	UPROPERTY()
		class UAISenseConfig_Hearing* HearingSense;
	UPROPERTY()
		class UAISenseConfig_Damage* DamageSense;	// ** Damage reaction

public:

	UFUNCTION(Blueprintcallable)
		void TargetPerceptionUpdated(AActor* _ActorActivator, FAIStimulus _Stimulus);

	// ** Notice any Damage like "Sense EVENT"
	//------UFUNCTION(Blueprintcallable)
	//------	void NoticeSelfDamageAsPerception(float _DamageAmount, struct FDamageEvent const& _DamageEvent, AController* _Instigator, AActor* _ActorCauser);

	// ** 
	// ** UFUNCTION(Blueprintcallable)
	// ** TakeDamage()   (AAA::Unit EXAMPLE)
	// +++ float TakeSpecialDamage(float _DamageHP, 
	// +++							float DamageArmor, 
	// +++							float DamagePArmor, 
	// +++							float DamageStamina, 
	// +++							FVec HitPoint,
	// +++							FVec ImpulsDir,
	// +++							EImpulsPower ImpulsPower,
	// +++							FVec WaponlineDir, 
	// +++							EEffectType EffectType,		// ** Blood, Flash, Explosion
	// +++							AActor* Agressor
	// +++	);



	// **  ************************   AnimInstance  ************************ 
public:

	UPROPERTY()		class UHumanAnimInst* AnimInstance;

	FOnMontageEnded FinishAnimationDELEGATE;

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetWeaponAnimType(EWeaponType _NewWeaponAnim);
	// ** UFUNCTION(BlueprintCallable, Category = "OOO")
		void UpdateRotateAnimSpeedHandler(TArray<FPoseLocomotion>* _ActualPosesArray = nullptr);
	

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void PlayAnimate(UAnimMontage* _AnimMontage, bool _isPlayTOP, float _fromTime = 0.f);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void StopAnimate();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void OnAnimNotify(FString _NotifyName);


/*++++++++++++++++++

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void BreakAnimate(); 
		{
			StopAnimMontage(GetCurrentMontage());
		}
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void PauseAnimate();
		{
			save AnimateStopTime
			....................
		}
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ResumeAnimate();
		{
			....................
		}
*/

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PreInitializeComponents() override;



	// *******************   OOOOOOOOOOOOOOOO   *******************
public:

	//---UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
	//---	bool IsUnitInGroup = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsUnitSelected = false;


	// **  ************************   Unit_Main_Function  ************************
public:

	UFUNCTION(Blueprintcallable, Category = "OOO_Main_Function")
		void SelectUnit();

	UFUNCTION(Blueprintcallable, Category = "OOO_Main_Function")
		void DeselectUnit();

	UFUNCTION(Blueprintcallable, Category = "OOO_Main_Function")
		bool GetIsUnitSelected();

	UFUNCTION(Blueprintcallable, Category = "OOO_Main_Function")
		bool IsUnitInGroup();



// **  ************************   Unit_State   ************************

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO_Unit_State")
		class UUnitStateComponent* UnitState;

	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		int32 GetLevel() const;
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void SetLevel(int32 _Val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void ModLevel(int32 _Val);

	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		int32 GetCurrentHP() const;
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		int32 GetCriticalHP(bool _GetBaseValue = false) const;
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		int32 GetMinHP(bool _GetBaseValue = false) const;
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		int32 GetHP(bool _GetBaseValue = false) const;
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		int32 GetTotalWpnLevel(bool _GetBaseValue = false) const;
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		int32 GetTotalGunLevel(bool _GetBaseValue = false) const;
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		int32 GetTotalMagikLevel(bool _GetBaseValue = false) const;


	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void SetCurrentHP(int32 _Val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void SetCriticalHP(int32 _Val, bool _GetBaseValue = false);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void SetMinHP(int32 _Val, bool _GetBaseValue = false);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void SetHP(int32 _Val, bool _GetBaseValue = false);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void SetTotalWpnLevel(int32 _Val, bool _GetBaseValue = false);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void SetTotalGunLevel(int32 _Val, bool _GetBaseValue = false);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void SetTotalMagikLevel(int32 _Val, bool _GetBaseValue = false);


	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void ModCurrentHP(int32 _Val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void ModCriticalHP(int32 _Val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void ModMinHP(int32 _Val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void ModHP(int32 _Val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void ModTotalWpnLevel(int32 _Val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void ModTotalGunLevel(int32 _Val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		void ModTotalMagikLevel(int32 _Val);

/*
		void SetCriticalHP(int32 _Val)
		void SetMinHP(int32 _Val)
		void SetHP(int32 _Val)
		void SetTotalWpnLevel(int32 _Val)
		void SetTotalGunLevel(int32 _Val)
		void SetTotalMagikLevel(int32 _Val)
*/

// **  ************************   Skill_Depend   ************************

public:

	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_State")
		int32 GetSkillDepend_FirstAttackSeries() const;

// **  ************************   Fraction  ************************

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		int32 Fraction = 0;

	UFUNCTION(Blueprintcallable, Category = "OOO_Fraction")
		FORCEINLINE int32 GetFraction() const { return Fraction; };

	UFUNCTION(Blueprintcallable, Category = "OOO_Fraction")
		void SetFraction(int32 _Fraction = -1) { Fraction = _Fraction; };






// **  ************************   Inventory   ************************

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO")
		class UInventoryComponent* Inventory;

	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		bool TryAddItemToMainInventory(FItemDT* ItemDT, int32 ToSlotIndex = -1, 
			TSubclassOf<class AWorldItem> WorldItem = nullptr, bool ForseAdd= false);

	UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		bool IsMainInventorySlotEmpty(int32 SlotIndex);

	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		FItemDT* GetItemRefFromMainInventory(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		void RemoveItemFromMainInventory(int32 SlotIndex);



	// **  -------------------   Global_Inventory   ---------------------
	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		void AddItemToGlobalInventory(FItemDT* ItemDT, int32 ToSlotIndex = -1);
	
	UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		bool IsGlobalInventorySlotEmpty(int32 SlotIndex);

	///UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		FItemDT* GetItemRefFromGlobalInventory(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO_Inventory")
		void RemoveItemFromGlobalInventory(int32 SlotIndex);

// **  ************************   Fast_Panel   ************************

public:

	// ** IndexInContainer  (KEY in Map : FastPanelItem)
	// ** AbilityType
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Fast_Panel")		
		TArray<FFastPanelSlot> FastPanelSlots;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Fast_Panel")		
		TMap<int32, FItemDT> FastPanelItem;

	UFUNCTION(BlueprintCallable, Category = "OOO_Fast_Panel")
		void InitFastPanel();

	///UFUNCTION(BlueprintCallable, Category = "OOO_Fast_Panel")
		bool SetItemToFastPanel(FItemDT* ItemDT, int32 ToSlotIndex = -1);

	UFUNCTION(BlueprintCallable, Category = "OOO_Fast_Panel")
		bool SetAbilityToFastPanel(EAbilityType _Ability, int32 ToSlotIndex = -1);

	// ** return "false" if slot empty 
	///UFUNCTION(BlueprintCallable, Category = "OOO_Fast_Panel")
	bool GetFastPanelSlotElement(int32 Index,
		FItemDT*& GetItemDT, EAbilityType*& GetAbilityType);

	UFUNCTION(BlueprintCallable, Category = "OOO_Fast_Panel")
		void RemoveElementFromFastPanel(int32 ToSlotIndex);



// **  ************************   Ability   ************************

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO")
		class UAbilityComponent* Ability;

	UFUNCTION(BlueprintCallable, Category = "OOO_Ability")
		void AddAbility(EAbilityType _Ability);

	// ** IndexInContainer  (KEY in Map : FastPanelItem)
	// ** AbilityType


public:


// ** *********************     Weapon_Component    ************************
// ** *********************       Equip_Panel       ************************

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO")
		class UWeaponComponent* WeaponComponent;



	UFUNCTION(BlueprintCallable, Category = "OOO")
		int32 IsWeaponActive();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool ActivateWeapon();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool UnactivateWeapon();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		class AWeaponWorldItem* GetCurrWeaponItem();
		//FItemDT* GetCurrWeaponData();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		EWeaponType GetCurrentWeaponType();

	///UFUNCTION(BlueprintCallable, Category = "OOO")
		bool EquipAmunitionByItemDT(const FItemDT* _ItemDT);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool SetWeaponSlotSelected(int32 _WeaponSlotIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		int32 GetSelectedWeaponSlotIndex();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		EWeaponType GetWeaponTypeBySlotIndex(int32 _SlotIndex) const;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool IsEquipPanelSlotEmpty(int32 SlotIndex);

	///UFUNCTION(BlueprintCallable, Category = "OOO")
		FItemDT* GetItemRefFromEquipPanel(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void RemoveItemFromEquipPanel(int32 SlotIndex);

	// ** UW_WeaponPanel Open (Data from WeaponComponent)
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void OpenChangeWeaponPanel();





	/*++++++++++++++++++++++++++

		// ** Equip-Item  (Put item from Inventory to EQUIP-slot)
		UFUNCTION(BlueprintCallable, Category = "AAA")
			int32 TryEquipAmunitionBySlot(EInvCell_Type SlotType, FItemData& itemToEquip, int32 _LastWSlot_Index = -1);
		// ** Equip-Item  (Put item from Inventory to EQUIP-slot)
		UFUNCTION(BlueprintCallable, Category = "AAA")
			int32 EquipAmunition(const FItemData& itemToEquip, int32 _LastWSlot_Index = -1);
	*/

// ** *********************     Armor_Component    *************************
// ** *********************       Equip_Panel      *************************


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO")
		class UArmorComponent* ArmorComponent;

	///UFUNCTION(BlueprintCallable, Category = "OOO")
	bool EquipArmorByItemDT(const FItemDT* _ItemDT);



	// **  ************************   Pose-Locomotion  ************************ 
public:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		EUnitPose CurrUnitPose;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void StopMove();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void GetActualPoseLocomotion(TArray<FPoseLocomotion>& _ActualPoseLocomotion);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetPose(EUnitPose _UnitPosen);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		EUnitPose GetCurrUnitPose() const;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetMoveSpeed(float _Speed);

	// ** UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetMoveSpeedFromPose(EUnitPose _UnitPose, TArray<FPoseLocomotion>* _ActualPosesArray = nullptr);

	// ** UFUNCTION(BlueprintCallable, Category = "OOO")
		float GetMoveSpeedFromPose(EUnitPose _UnitPose, TArray<FPoseLocomotion>* _ActualPosesArray = nullptr);

	// ** Rotate speed (Set for Creature in Editor)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")
		float SlowRotateSpeed = 150.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")
		float NormalRotateSpeed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")
		float FastRotateSpeed = 600.f;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetRotateSpeedFromVal(float _NewSpeed);
	UFUNCTION(BlueprintCallable, Category = "OOO")
		float GetRotateSpeedFromPose(EUnitPose _UnitPose);

/*+++++++++++++++++
	UFUNCTION(BlueprintCallable, Category = "OOO")
		UnitPose GetCurrPoseLocomotion();
		{
			return AnimInstance->PoseLocomotion;
		}
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetPoseLocomotion(UnitPose pose);
		{
			AnimInstance->PoseLocomotion = pose;
		}
*/






public:

// ****************************************************
// *****************   TEST_DEBUG  *****************
// ****************************************************



};
