
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WayPoint.generated.h"

UCLASS()
class OOO_API AWayPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AWayPoint();

protected:
	virtual void BeginPlay() override;

	//virtual void PostInitializeComponents() override;

public:

	
	UPROPERTY()
		USceneComponent* Root;

	// ** Helper Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA_SetBP")
		UStaticMeshComponent* HelperMesh = nullptr;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA_SetBP")
		FName WayPointName = FName("none");									// ** TAG

//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA")
//		float CollisionWidth = 150.f;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA")
//		float CollisionHeight = 150.f;
		
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA")
		TArray<AActor*> SpectatorUnits;
	UFUNCTION(Blueprintcallable)
		void AddSpectatorUnit(AActor* _NewSpectatorUnit);
	UFUNCTION(Blueprintcallable)
		void RemoveSpectatorUnit(AActor* _SpectatorUnit);
	UFUNCTION(Blueprintcallable)
		void RecheckSpectatorUnit();


//public:	
//	virtual void Tick(float DeltaTime) override;

};
