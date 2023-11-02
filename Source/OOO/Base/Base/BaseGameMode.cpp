

//#include "Base/Base/BaseGameMode.h"
#include "BaseGameMode.h"

#include "BaseGameState.h"
#include "../HUD/BaseHUD.h"
#include "../HUD/Widget/W_Screen.h"
#include "../HUD/Widget/Slot/W_Slot.h"

#include "../Unit/Base/Unit.h"
#include "../Controller/UnitAI.h"

//----------------

#include "Kismet/GameplayStatics.h"   // ** GetAllActorsOfClass(),  QuitGame()

#include "Engine/DataTable.h"

ABaseGameMode::ABaseGameMode()
{
	
	


	// *******************************************    Fraction    *****************************************
	Fraction = CreateDefaultSubobject<UFractionSystem>(TEXT("Fraction"));
	// ** SET in UE
	FractionsAttitude.Add(FFractionUnit(0, 1, EUnitAttitudeStatus::Enemy));
	FractionsAttitude.Add(FFractionUnit(0, 2, EUnitAttitudeStatus::Enemy));
	FractionsAttitude.Add(FFractionUnit(0, 3, EUnitAttitudeStatus::Friend));
	FractionsAttitude.Add(FFractionUnit(1, 2, EUnitAttitudeStatus::Enemy));
	FractionsAttitude.Add(FFractionUnit(1, 3, EUnitAttitudeStatus::Friend));
	FractionsAttitude.Add(FFractionUnit(2, 3, EUnitAttitudeStatus::Enemy));

}


void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	// ** "Game-Delay" 
	GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::StartGame, 1.f, false);

}

void ABaseGameMode::StartGame()
{

	// ****** 11111111111 (NEED exec before other) 
	// *******************************************    Set GameState    *****************************************
	
	if (!BGameState)
	{
		AGameStateBase* SimpleGameState = GetWorld()->GetGameState();
		if (nullptr == (BGameState = Cast<ABaseGameState>(SimpleGameState)))
		{
			if (BaseGameState_Class)
			{
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.Instigator = GetInstigator();
				SpawnInfo.ObjectFlags |= RF_Transient;	// ** We never want to save game states or network managers into a map

				BGameState = GetWorld()->SpawnActor<ABaseGameState>(BaseGameState_Class, SpawnInfo);
				GetWorld()->SetGameState(BGameState);
				if (BGameState)
				{
					BGameState->AuthorityGameMode = this;

					if (SimpleGameState)
						SimpleGameState->Destroy();
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame():  'GameState' not init"));
					GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::StartGame, 1.f, false);
					return;
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame():  'GameState' not init   >>>>>>>>   'BaseGameState_Class' - absent"));
				UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, true);
				return; 
			}
		}
	}

	// ****** 11111111111 (NEED exec before other) 
	
	if (!HUD)
	{
		AHUD* SimpleHud = GetWorld()->GetFirstPlayerController()->GetHUD();
		if (nullptr == (HUD = Cast<ABaseHUD>(SimpleHud)))
		{
			if (BaseHUD_Class)
			{
				GetWorld()->GetFirstPlayerController()->ClientSetHUD(BaseHUD_Class);
				HUD = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
				if (!HUD)
				{
					//HUD->Init(W_Screen_Class);
					UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame():  'HUD' not init"));
					GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::StartGame, 1.f, false);
					return;
				}
				if (SimpleHud)
					SimpleHud->Destroy();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame():  'HUD' not init   >>>>>>>>   'BaseHUD_Class' - absent"));
				UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, true);
				return;
			}
		}

		if (!W_Screen_Class || !W_Slot_Class)
		{
			UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR:    ABaseGameMode::Init():  'W_Screen' not init   >>>>>>>>   'W_Screen_Class' - absent"));
			UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, true);
			return;
		}
		else if (!HUD->Init(W_Screen_Class))
		{
			GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::StartGame, 1.f, false);
			return;
		}
	}


	if (!GameAbilityArchive)
	{
		UE_LOG(LogTemp, Error, TEXT(">>>>>>>>>> ERROR:    ABaseGameMode::Init():     >>>>>>>>   'GameAbilityArchive' - absent"));
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Type::Quit, true);
	}


	// *******************************************    Init fraction    *****************************************
	if (!Fraction)
	{	
		UE_LOG(LogTemp, Warning, TEXT(">>>>>>>>>> ERROR: ABaseGameMode::StartGame(): \"Fraction\" not init"));
		GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::StartGame, 1.f, false);
		return;
	}
	else
	{
		Fraction->Init(FractionsAttitude);
		UE_LOG(LogTemp, Log, TEXT(">>>>>>>>>> OK: ABaseGameMode::StartGame(): \"Fraction\" Init Succes"));
	}


	// **************************************    Set default game param    ************************************



	HUD->SetDefaultGameParam(this, BGameState);
	BGameState->SetDefaultGameParam(this, HUD);


	// ********************    All Scene-Units Init    ********************
	SceneUnitsInit();
}


void ABaseGameMode::SceneUnitsInit()
{
	TArray<AActor*> UnitsIt;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), UnitsIt);
	for (int32 i = 0; i < UnitsIt.Num(); ++i)
	{
		AUnit*unit = Cast<AUnit>(UnitsIt[i]);
		if (unit)
		{
			bool isSucces = unit->StartGame(false);
			if (!isSucces)
			{
				GetWorld()->GetTimerManager().SetTimer(TH_SceneUnitsInit, this, &ThisClass::SceneUnitsInit, 0.5f, false);
				return;
			}
		}
	}

	ABaseGameState* GmState = Cast<ABaseGameState>(GetWorld()->GetGameState());
	if (GmState)
	{
		for (int32 i = 0; i < UnitsIt.Num(); ++i)
		{
			AUnit* unit = Cast<AUnit>(UnitsIt[i]);
			if (unit)
			{
				unit->StartGame(true);

				// ** XXXXXXXXXXXXXXX
				GmState->TurnBaseGmStateSender.AddUObject(unit->AI, &AUnitAI::OnChangeTurnBaseGameState);
			}
		}
		GetWorld()->GetTimerManager().ClearTimer(TH_SceneUnitsInit);

		return;
	}
	GetWorld()->GetTimerManager().SetTimer(TH_SceneUnitsInit, this, &ThisClass::SceneUnitsInit, 0.5f, false);
}





// ****************************************************************************************************	
// *******************************************    Fraction    *****************************************
EUnitAttitudeStatus ABaseGameMode::GetFractionAttitude(uint8 A, uint8 B)
{
	return Fraction->GetAttitude(FractionsAttitude, A, B);
}


// ****************************************************************************************************	
// ***************************************    Global Inventory    *************************************


//...................................




// ****************************************************************************************************	
// *******************************************    Ability    ******************************************

UDataTable* ABaseGameMode::GetGameAbilityArchive()
{
	return GameAbilityArchive;
}

// ****************************************************************************************************	
// ******************************************    Game_Time    *****************************************

int32 ABaseGameMode::GetGameHour()
{
	return Hour;
}


void ABaseGameMode::AddTime(int32 _Hour)
{
	Hour += _Hour;

	// ** Hour > 24 
	// ** Day > 30 
	// ** Month > 12 
	if (Hour > 23)
	{
		Hour = 0;
		++Day;
		if (Day > 30)
		{
			Day = 0;
			++Month;
			if (Month > 12)
			{
				Month = 0;
				++Year;
			}
		}
	}
}