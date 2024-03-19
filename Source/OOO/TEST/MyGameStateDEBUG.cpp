

//#include "TEST/MyGameStateDEBUG.h"
#include "MyGameStateDEBUG.h"

#include "../Base/Base/BaseGameState.h"

#include "../Base/Unit/Base/Unit.h"

#include "DrawDebugHelpers.h"


AMyGameStateDEBUG::AMyGameStateDEBUG()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyGameStateDEBUG::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyGameStateDEBUG::Tick(float DeltaTime)
{
	if (!GameState)
	{
		AGameStateBase* SimpleGameState = GetWorld()->GetGameState();
		GameState = Cast<ABaseGameState>(SimpleGameState);
	}



	if (DrawSelectUnit && GameState)
	{
		for (int32 i = 0; i < GameState->SelectedUnits.Num(); ++i)
		{
			FColor color = FColor::White;

			if (GameState->SelectedUnits.Num() == 1)
				color = FColor::Black ;

				DrawDebugSphere(
					GetWorld(),
					GameState->SelectedUnits[i]->GetActorLocation(),
					25.f, 
					5,
					color,
					false, // bPersistLine
					DeltaTime * 3,
					5, // DepthPriority
					5); // Siknes			
		}
	}



	Super::Tick(DeltaTime);

}

