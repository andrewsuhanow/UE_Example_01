

// ** #include "Base/Controller/Fraction/FractionController.h"
#include "FractionController.h"

#include "../../Unit/Base/Unit.h"

#include "Struct/PointTaskAgent.h"
#include "Struct/UnitTaskAgent.h"


AFractionController::AFractionController()
{
	PrimaryActorTick.bCanEverTick = true;

}


void AFractionController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFractionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



//------------------------------------------------------




void AFractionController::RegisterUnit(AUnit* _Unit)
{
	_Unit->SetFraction(FractionIndex);
	AllControlledUnits.Add(_Unit);
}