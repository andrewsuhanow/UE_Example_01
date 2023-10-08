
// ** #include "../Controller/UnitAI.h"
#include "UnitAI.h"
#include "../Unit/Base/Unit.h"

AUnitAI::AUnitAI()
{
	PrimaryActorTick.bCanEverTick = true;




}


void AUnitAI::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("ERROR:_______________AUnit::Start()_______________Init Continue"));



	UnitOwner = Cast<AUnit>(GetPawn());
	if (!UnitOwner)
		return;

	return;
}


