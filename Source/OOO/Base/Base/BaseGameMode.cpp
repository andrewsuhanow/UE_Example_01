

//#include "Base/Base/BaseGameMode.h"
#include "BaseGameMode.h"





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
	GetWorld()->GetTimerManager().SetTimer(TH_Start, this, &ThisClass::Start, 1.f, false);

}

void ABaseGameMode::Start()
{
	// *******************************************    Fraction    *****************************************
	if (Fraction){	Fraction->Init(FractionsAttitude);	}
}



// ****************************************************************************************************	
// *******************************************    Fraction    *****************************************
EUnitAttitudeStatus ABaseGameMode::GetFractionAttitude(uint8 A, uint8 B)
{
	return Fraction->GetAttitude(FractionsAttitude, A, B);
}