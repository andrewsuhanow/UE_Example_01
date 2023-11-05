
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

// ** ----------------------

#include "../Fraction/FractionSystem.h"

// ** ----------------------

#include "BaseGameMode.generated.h"


UCLASS()
class OOO_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:

	ABaseGameMode();

protected:

	virtual void BeginPlay() override;


public:

	// *************************   Default Game Param   ****************************

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		TSubclassOf<class ABaseGameState> BaseGameState_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		TSubclassOf<class ABaseHUD> BaseHUD_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		TSubclassOf<class UW_Screen> W_Screen_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		TSubclassOf<class UW_Slot> W_Slot_Class;

	UPROPERTY(EditDefaultsOnly, Category = "OOO!_DefaultGameParam")						class UDataTable* GameAbilityArchive;



	// ** UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")	bool IsInventorSizeFixed = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		int32 MainInvCollNum = 6;			// ** (Const) Horizontal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		int32 MainInvRowNum = 9;			// ** (Const) Vertical
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		int32 FullRowNum = 12;				// ** (Can be Add Using Scroll)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		float MainInventorSlotSize = 64.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		int32 GlobalInventorHeight = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		float GlobalInventorSlotSize = 256.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		float FastPanelSlotSize = 64.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		float PerkPanelSlotSize = 128.f; // ++ 64.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_DefaultGameParam")		UTexture2D* MainInvertorySlotTexture = nullptr;

	
	



public:

	// ** "Game-Delay" at the BeginPlay() 
	UFUNCTION()		void StartGame();
	UPROPERTY()		FTimerHandle TH_Start;
	
	// ** Set all gane Entity ConectingParams, like Delegates
	UFUNCTION()		void SceneUnitsInit();
	UPROPERTY()		FTimerHandle TH_SceneUnitsInit;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_DefaultGameParam")
		class ABaseGameState* BGameState;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_DefaultGameParam")
		class ABaseHUD* HUD;



// ****************************************************************************************************	
// *******************************************    Fraction    *****************************************

public:

	// ** (Set in Editor)  FFractionUnit(Unit_A, Unit_B, AttitudeStatus)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Set_Fraction")
		TArray<FFractionUnit> FractionsAttitude;

	// ** Fraction component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO_Fraction")
		UFractionSystem* Fraction;

	UFUNCTION(Blueprintcallable, Category = "OOO_Fraction")
		EUnitAttitudeStatus GetFractionAttitude(uint8 A, uint8 B);


// ****************************************************************************************************	
// ***************************************    Global Inventory    *************************************

public:

	//+++++UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO_Inventory")		
	//+++++	TArray<FInventorItem> GlobalInvertorSlots;


// ****************************************************************************************************	
// *******************************************    Ability    ******************************************

public:

	UFUNCTION(Blueprintcallable, Category = "OOO_Ability")
		UDataTable* GetGameAbilityArchive();
// ****************************************************************************************************	
// ******************************************     Game_Time    ****************************************

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA_Game_TIME")			// ** 8888888888
		int32 Year = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA_Game_TIME")			// ** 12 
		int32 Month = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA_Game_TIME")			// ** 30
		int32 Day = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA_Game_TIME")			// ** 24
		int32 Hour = 0;

	//+++UFUNCTION(Blueprintcallable, Category = "OOO_GameTime")
	//+++	int32 GetGameTime();
	UFUNCTION(Blueprintcallable, Category = "OOO_GameTime")
		int32 GetGameHour();
	UFUNCTION(Blueprintcallable, Category = "OOO_GameTime")
		void AddTime(int32 _Hour = 1);
	
};

