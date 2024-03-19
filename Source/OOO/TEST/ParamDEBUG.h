
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Base/Controller/Task/Struct/TaskData.h"		// ** SetUnitTask()  ->  AI
#include "../Base/Controller/Task/Enum/TaskType.h"			// ** SetUnitTask()  ->  AI



#include "GameFramework/PlayerInput.h"						// ** FInputActionKeyMapping

#include "../Base/Base/Enum/TurnBaseGameState.h"

//#include "../Base/Item/Struct/ItemDT.h"
//#include "../Base/Ability/Enum/AbilityLogic.h"

//#include "../Base/Controller/Task/Enum/TacticalMoveType.h"
//#include "../Base/Unit/Enum/UnitPose.h"


//#include "../Base/UnitEffect/Struct/UnitEffectDT.h"

#include "../Base/UnitState/Enum/UnitParam.h"


#include "ParamDEBUG.generated.h"

UCLASS()
class OOO_API AParamDEBUG : public AActor
{
	GENERATED_BODY()

public:	

	AParamDEBUG();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;




public:
	// ** Select Unit
	UPROPERTY()		class ABaseGameMode* GameMod;
	UPROPERTY()		class ABaseGameState* GameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_001_SelectUnit")		class AUnit* SelectTestUnit;


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
	// ** Param
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Param") 		void SetParam();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Param") 		void AddParam();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "OOO_002_Param") 		void DamageParam();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Param")		EUnitParam Param = EUnitParam::HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_002_Param")		float Value = 20.f;

};
