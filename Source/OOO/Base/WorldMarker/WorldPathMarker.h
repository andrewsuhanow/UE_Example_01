

// **
// **
// **	Unit path.   Visual markers draving in world
// **
// **

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldPathMarker.generated.h"

UCLASS()
class OOO_API AWorldPathMarker : public AActor
{
	GENERATED_BODY()
	
public:	

	AWorldPathMarker();

protected:

	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, Category = "OOO")
		class UTMoveTo* MoveTaskOwner;

	//virtual void Tick(float DeltaTime) override;


public:	

	UPROPERTY(EditAnywhere, Category = "OOO")
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO") 
		UStaticMeshComponent* GoalPathPoint = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<UStaticMeshComponent*> PathLines;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<UStaticMeshComponent*> PathPoints;



public:
	UFUNCTION()
		void DrawPathLine(TArray<FVector>& _Path, class UTMoveTo* _MoveTaskOwner);
	UFUNCTION()
		void DrawPathLineAndPoint(TArray<FVector>& _Path, class UTMoveTo* _MoveTaskOwner);
	UFUNCTION()
		void StopDraw();

	UPROPERTY()
		bool IsDrawing = false;
	UPROPERTY()		
		FTimerHandle TH_Update;
	UFUNCTION()		
		void DrawUpdatePerformance();

	UPROPERTY()
		bool IsDrawLine = false;
	UPROPERTY()
		bool IsDrawPoint = false;
	
};




