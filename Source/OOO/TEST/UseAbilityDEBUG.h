
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Base/Controller/Task/Struct/TaskData.h"		// ** SetUnitTask()  ->  AI
#include "../Base/Controller/Task/Enum/TaskType.h"			// ** SetUnitTask()  ->  AI



#include "GameFramework/PlayerInput.h"						// ** FInputActionKeyMapping

#include "../Base/Base/Enum/TurnBaseGameState.h"

#include "../Base/Item/Struct/ItemDT.h"
//#include "../Base/Ability/Enum/AbilityLogic.h"

#include "../Base/Controller/Task/Enum/TacticalMoveType.h"
#include "../Base/Unit/Enum/UnitPose.h"


#include "../Base/UnitEffect/Struct/UnitEffectDT.h"



#include "UseAbilityDEBUG.generated.h"

UCLASS()
class OOO_API AUseAbilityDEBUG : public AActor
{
	GENERATED_BODY()
	
public:	

	AUseAbilityDEBUG();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;




public:
	// ** Select Unit
	UPROPERTY()		class ABaseGameMode* GameMod;
	UPROPERTY()		class ABaseGameState* GameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		class AUnit* SelectTestUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		TArray<FTaskData> StoreQueueTaskDTCopy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		TArray<FTaskData> CurrTaskDTBufferCopy;
	UPROPERTY()																			float sh = 0;

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelctUn_1();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelctUn_2();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelctUn_3();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_001_SelectUnit") 		void SelctUn_4();
	UFUNCTION() 																		void SelctUn_Performance(FName _SelectUnitName);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_1 = FName("Un6_Ability");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_2 = FName("Un2");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_3 = FName("Un5_DrawWpn");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		FName SelectUnitName_4 = FName("Un4_CheckPoint");


	


public:
	// ** Attack
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Use_Ability") 		void PrepareToUseAbilitty();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Use_Ability") 		void UseAbility______SET();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Use_Ability") 		void UseAbility______ADD();
	UFUNCTION()										void UseAbilityk_Performance(TArray<FName> _UnitTargetName, bool _bAddMoreOneTask);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Use_Ability")		TArray<FName> UnitTargetName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Use_Ability")		FVector PointTargetLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Use_Ability")		int32 UseAbilityIndex = 0;



	// ** Add Ability
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_003_Add_Ability")		void AddAbility();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_003_Add_Ability")		TArray <FName> AbiilityAddToFastPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_003_Add_Ability")		TArray< TSubclassOf<class UAbilityDT> > AbilityClass;
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_003_Add_Ability")		void Add_ToFastPanel();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_003_Add_Ability")		int32 FastPanelSlotIndex = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_003_Add_Ability")		int32 AbilityIndexToFastPanel = 0;




	// ** Add Effect
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Effect")				void InitEffect();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_004_Effect")				void AddEffect();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Effect")			TArray<FUnitEffectDT> UnitEffects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Effect")			TArray<FName> UnitEffectsName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_004_Effect")			int32 UnitEffectsIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		TArray<FName> TatgUnitName;


};
