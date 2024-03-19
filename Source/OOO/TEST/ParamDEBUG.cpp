

// #include "TEST/ParamDEBUG.h"
#include "ParamDEBUG.h"



#include "../Base/Base/BaseGameState.h"
#include "../Base/Base/BaseGameMode.h"

#include "../Base/Base/Enum/TurnBaseGameState.h"

#include "../Base/HUD/BaseHUD.h"

#include "../Base/Unit/Base/Unit.h"
#include "../Base/Controller/UnitAI.h"
#include "../Base/Controller/Task/TDailyTask.h"
#include "../Base/Controller/Task/Struct/DailyBhvrData.h"
#include "../Base/Controller/Task/Enum/DailyBhvrPointPos.h"
#include "../Base/WorldObject/WayPoint/WayPoint.h"
#include "../Base/Controller/Task/TWeaponAttack.h"

#include "../Base/Inventory/InventoryComponent.h"

#include "../Base/Amunition/WeaponComponent.h"
#include "../Base/Amunition/WeaponWorldItem.h"

//#include "../Base/Ability/Enum/AbilityLogic.h"
#include "../Base/Ability/AbilityComponent.h"
#include "../Base/Controller/Enum/TargetType.h"

#include "../Base/Ability/AbilityDT.h"

#include "../Base/Controller/Task/Base/Task.h"
#include "../Base/Controller/Task/TMoveTo.h"
#include "../Base/Controller/Task/TUnitRotate.h"
#include "../Base/Controller/Task/TCheckPoint.h"
#include "../Base/Controller/Task/TUseAbility.h"

// ** Unit-Effect
#include "../Base/UnitEffect/UnitEffectRealizer/UER_ChangeUnitParam.h"

#include "../Base/Item/WorldItem.h"

//---------------------------------------------

#include "Kismet/GameplayStatics.h"   // ** GetAllActorsOfClass()

#include "DrawDebugHelpers.h"









AParamDEBUG::AParamDEBUG()
{
	PrimaryActorTick.bCanEverTick = true;
	   

}


void AParamDEBUG::BeginPlay()
{
	Super::BeginPlay();

}

void AParamDEBUG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// ************************    Select Unit


void AParamDEBUG::SelctUn_1()
{
	SelctUn_Performance(SelectUnitName_1);
}
void AParamDEBUG::SelctUn_2()
{
	SelctUn_Performance(SelectUnitName_2);
}
void AParamDEBUG::SelctUn_3()
{
	SelctUn_Performance(SelectUnitName_3);
}
void AParamDEBUG::SelctUn_4()
{
	SelctUn_Performance(SelectUnitName_4);
}
void AParamDEBUG::SelctUn_Performance(FName _SelectUnitName)
{
	GameState = Cast<ABaseGameState>(GetWorld()->GetGameState());
	GameMod = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());



	TArray<AActor*> AllUnitsActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), AllUnitsActor);
	for (int32 i = 0; i < AllUnitsActor.Num(); i++)
	{
		AUnit* unit = Cast<AUnit>(AllUnitsActor[i]);
		if (unit->GameName == _SelectUnitName)
		{
			SelectTestUnit = unit;
			GameState->SelectOneUnit(unit);


			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		}
	}

	// ** ShowPerkPanel();
	ABaseGameMode* gameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	ABaseHUD* hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (SelectTestUnit && hud)
	{
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}



// **************************



// **************************


void AParamDEBUG::SetParam()
{
	if (SelectTestUnit)
	{
		SelectTestUnit->SetParam(Param, Value);
	}
}

void AParamDEBUG::AddParam()
{
	if (SelectTestUnit)
	{
		float newVal = SelectTestUnit->GetParam(Param) + Value;
		SelectTestUnit->SetParam(Param, newVal);
	}
}

void AParamDEBUG::DamageParam()
{
	if (SelectTestUnit)
	{
		float newVal = SelectTestUnit->GetParam(Param) - Value;
		SelectTestUnit->SetParam(Param, newVal);
	}
}
