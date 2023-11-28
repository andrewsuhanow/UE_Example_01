
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../Enum/UnitPose.h"

#include "../../Item/Struct/ItemDT.h"
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

public:

// **  ************************   "Game-Delay" at the BeginPlay()  ************************  

	UFUNCTION()		bool StartGame(bool finalInit = false);






public:

// **  ************************   AI_Controller  ************************ 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Default_Controller")
		TSubclassOf<class AUnitAI> AIController_Class;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		class AUnitAI* AI;

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetUnitTask(bool _bAddMoreOne, ETaskType _TaskType, 
			FTaskData _TaskData, 
			ETaskInstigator _TaskInstigator = ETaskInstigator::General,
			ETaskPriority _TaskPriority = ETaskPriority::Normal);

	/*
			AddComand()			// ** FROM HUD,	FROM GameMod/
			{
				AI->NewComand()
			}
			ChangeWeapon()		// ** From AI
			{
				HUD_Redraw_if;
				WeaponComp;
			}
			ChangePose()		// ** From AI
			{
				HUD_Redraw_if;
				WeaponComp;
			}
	*/


	// **************************************     PERCEPTION  (Undate reaction)     *******************************************


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
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


public:

// **  ************************   AnimInstance  ************************ 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Default_Controller")
		TSubclassOf<class UHumanAnimInst> AnimInstance_Class;
	UPROPERTY()
		class UHumanAnimInst* AnimInstance;

	FOnMontageEnded FinishAnimationDELEGATE;

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetWeaponAnimType(EWeaponType _NewWeaponAnim);

public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void PlayAnimate(UAnimMontage* _AnimMontage, bool _isPlayTOP, float _fromTime = 0.f);

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

public:


// **  ************************   Unit_Parameter  ************************

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		EUnitGameType UnitGameType = EUnitGameType::none;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		FName GameName = FName("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		FName GameId;

	//----------------UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
	//----------------	bool IsUnitInGroup = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsUnitSelected = false;

	// ** Gape betwean target-point for stoping     (FIX)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		float StopDistance = 120.f;

	// ** Daily-behavior Default class (Queue stored) (for "AI::DailyBhvrTaskDT")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		TSubclassOf<class UDailyBhvrQueue> DailyBhvrQueueClass;

	


	// ---------------   Inventor_Parameter   ---------------

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_BigContactWpn = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_SmalContactWpn = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* EquipPanelSlotTexture_RangeWpn = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		
		UTexture2D* EquipPanelSlotTexture_Pistol= nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		
		UTexture2D* EquipPanelSlotTexture_Cup = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		
		UTexture2D* EquipPanelSlotTexture_Armor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		
		UTexture2D* EquipPanelSlotTexture_Clothes = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		
		UTexture2D* EquipPanelSlotTexture_Collar = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		
		UTexture2D* EquipPanelSlotTexture_Braslet = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		
		UTexture2D* EquipPanelSlotTexture_Ring = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		
		UTexture2D* EquipPanelSlotTexture_HeavyStuff = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		TArray<TSubclassOf<class AWorldItem>> InitInvertorItems;

/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter_Inventor")		
		int32 GlobalInventorHeight = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter_Inventor")		
		float GlobalInventorSlotSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		
		float FastPanelSlotSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		
		float PerkPanelSlotSize = 0; 
*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")
		UTexture2D* MainInvertorySlotTexture = nullptr;
	// ---------------   Inventor!!!   ---------------
	
public:


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

// **  ************************   Fraction  ************************

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Fraction")
		int32 Fraction = 0;
public:

	UFUNCTION(Blueprintcallable, Category = "OOO_Fraction")
		FORCEINLINE int32 GetFraction() { return Fraction; };








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
		EWeaponType GetCurrentWeaponType();

	///UFUNCTION(BlueprintCallable, Category = "OOO")
		bool EquipWeaponByItemDT(const FItemDT* _ItemDT);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool SetWeaponSlotSelected(int32 _WeaponSlotIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		int32 GetWeaponSlotSelected();

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

// ** *********************     Armour Component    *************************








// **  ************************   Pose-Locomotion  ************************ 

public:

/*+++++++++++++++
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		float OriginMoveSpeed = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		float ActualMoveSpeed = 0;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		float GetMoveSpeed() const;
	{
		GetCharacterMovement()->MaxWalkSpeed;
	}
*/	
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetMoveSpeed(float _Speed);
	UFUNCTION(BlueprintCallable, Category = "OOO")
		void StopMove();




	// ** Rotate speed (Set for Creature in Editor)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")
		float SlowRotateSpeed = 150.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")
		float NormalRotateSpeed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")
		float FastRotateSpeed = 600.f;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetRotateSpeed(uint8 _RotSpeedIndex);

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








// **  ************************   Select Unit  ************************ 
public:
/*++++++++++++++++++++++++
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
		bool IsSelected = false;
	UFUNCTION(Blueprintcallable, Category = "AAA")
		void SelectUnit(); // int32 FractionStatus = 0
	UFUNCTION(Blueprintcallable, Category = "AAA")
		void DeselectUnit();
*/







public:

// ****************************************************
// *****************   TEST_DEBUG  *****************
// ****************************************************

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_TEST_MoveToPointName") 		void MoveToPointName();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		bool IsRotateByPoint1 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		FName PointNameForMove1 = FName("wpL01");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		bool IsRotateByPoint2 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		FName PointNameForMove2 = FName("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		bool IsRotateByPoint3 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		FName PointNameForMove3 = FName("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		bool IsRotateByPoint4 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		FName PointNameForMove4 = FName("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		bool IsRotateByPoint5 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		FName PointNameForMove5 = FName("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		bool IsRotateByPoint6 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		FName PointNameForMove6 = FName("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		bool IsRotateByPoint7 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		FName PointNameForMove7 = FName("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		bool IsRotateByPoint8 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		FName PointNameForMove8 = FName("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		bool IsRotateByPoint9 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		FName PointNameForMove9 = FName("none");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		bool IsRotateByPoint10 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_TEST_MoveToPointName")		FName PointNameForMove10 = FName("none");
};
