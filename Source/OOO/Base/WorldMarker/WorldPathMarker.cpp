

// #include "Base/WorldMarker/WorldPathMarker.h"
#include "WorldPathMarker.h"

#include "../Controller/Task/TMoveTo.h"



#include "Kismet/KismetMathLibrary.h"

// ** TEST
#include "DrawDebugHelpers.h"




AWorldPathMarker::AWorldPathMarker()
{
	PrimaryActorTick.bCanEverTick = false;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = Root;

	GoalPathPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalPathPoint"));
	GoalPathPoint->SetCollisionProfileName(TEXT("NoCollision"));
	GoalPathPoint->SetupAttachment(Root);
	GoalPathPoint->bHiddenInGame = true;


	//UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Test/Geometry/SM_Rock.SM_Rock"));
	//GoalPathPoint->SetStaticMesh(mesh);
}


void AWorldPathMarker::BeginPlay()
{
	Super::BeginPlay();
	
}



void AWorldPathMarker::DrawPathLine(TArray<FVector>& _Path, UTMoveTo* _MoveTaskOwner)
{
	MoveTaskOwner = _MoveTaskOwner;


	if (!GetWorld()->GetTimerManager().IsTimerActive(TH_Update))
	{
		IsDrawing = true;
		IsDrawLine = true;
		GetWorld()->GetTimerManager().SetTimer(TH_Update, this, &ThisClass::DrawUpdatePerformance, GetWorld()->GetDeltaSeconds() * 5.0f, false);
	}
/*	GoalPathPoint->bHiddenInGame = true;


	for (int32 i = 0; i < _Path.Num(); ++i)
	{
		// ** if Last point
		if (i == _Path.Num() - 1)
			break;


		
		//////if (i >= PathLines.Num() || !PathLines[i])
		//////{
		//////	FString fragmentName = FString("PathLine_") + FString::FromInt(i);
		//////	UStaticMeshComponent* newEl = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), FName(*fragmentName));
		//////	newEl->RegisterComponent();
		//////	newEl->SetCollisionProfileName(TEXT("NoCollision"));
		//////	PathLines.Add(newEl);
		//////}


		//////UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Test/Geometry/wayPoint.wayPoint"));

		//////float dist = FVector::Distance(_Path[i + 1], _Path[i]);

		//////PathLines[i]->SetWorldLocation(_Path[i]);

		//////PathLines[i]->SetWorldScale3D(FVector(0.5f, 0.5f, dist / 100.0f));

		//////FVector dir = _Path[i] + (_Path[i + 1] - _Path[i]).GetSafeNormal() * dist;
		//////FRotator rot = UKismetMathLibrary::Conv_VectorToRotator(dir);
		//////rot.Roll += 90.f;
		//////PathLines[i]->SetWorldRotation(rot);

		//////PathLines[i]->bHiddenInGame = false;

		//////PathLines[i]->SetStaticMesh(mesh);
		
	}

*/

}


void AWorldPathMarker::DrawPathLineAndPoint(TArray<FVector>& _Path, UTMoveTo* _MoveTaskOwner)
{
	MoveTaskOwner = _MoveTaskOwner;

	if (!GetWorld()->GetTimerManager().IsTimerActive(TH_Update))
	{
		IsDrawing = true;
		IsDrawPoint = true;
		IsDrawLine = true;
		GetWorld()->GetTimerManager().SetTimer(TH_Update, this, &ThisClass::DrawUpdatePerformance, GetWorld()->GetDeltaSeconds() * 5.0f, false);
	}
}

void AWorldPathMarker::DrawUpdatePerformance()
{

	TArray<FVector>& _Path = MoveTaskOwner->Path;

	if (IsDrawLine )
	{
		for (int32 i = 0; i < _Path.Num(); ++i)
		{
			// ** if Last point
			if (i == _Path.Num() - 1)
				break;

			// ** TEST
			DrawDebugLine(
				GetWorld(),
				_Path[i], // ** Start
				_Path[i + 1], // ** Trace_End,
				FColor::Blue,
				false, // is visible always
				GetWorld()->GetDeltaSeconds() * 5.0f, // visible time
				8, // DepthPriority
				8.0f); // Siknes


			if (IsDrawPoint)
			{
				DrawDebugSphere(
					GetWorld(),
					_Path[i], // center
					20.f, // radius
					10, // Segments
					FColor(FColor::Cyan),
					false, // bPersistLine
					GetWorld()->GetDeltaSeconds() * 5.0f, //GetWorld()->GetDeltaSeconds() * 3,
					8, // DepthPriority
					5); // Thick
			}
		}
	}


	DrawDebugSphere(
		GetWorld(),
		_Path.Last(), // center
		20.f, // radius
		10, // Segments
		FColor(FColor::Red),
		false, // bPersistLine
		GetWorld()->GetDeltaSeconds() * 5.0f, //GetWorld()->GetDeltaSeconds() * 3,
		8, // DepthPriority
		5); // Thick





	if(IsDrawing)
		GetWorld()->GetTimerManager().SetTimer(TH_Update, this, &ThisClass::DrawUpdatePerformance, GetWorld()->GetDeltaSeconds(), false);  // ** * 50.0f
	else
		GetWorld()->GetTimerManager().ClearTimer(TH_Update);
}


void AWorldPathMarker::StopDraw()
{
	IsDrawing = false;	
	IsDrawLine = false;
	IsDrawPoint = false;
	GetWorld()->GetTimerManager().ClearTimer(TH_Update);
}



/*void AWorldPathMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
