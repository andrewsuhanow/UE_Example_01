
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Struct/ItemDT.h"

#include "WorldItem.generated.h"

UCLASS()
class OOO_API AWorldItem : public AActor
{
	GENERATED_BODY()

public:	

	AWorldItem();
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO")
		FItemDT ItemDT;

	UPROPERTY()
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA_Item")
		class UBoxComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		UStaticMeshComponent* StaticMeshComponent = nullptr;


public:

	// ** Set Mesh to Item 
	UFUNCTION(BlueprintCallable, Category = "OOO")
		virtual void SetMesh(UObject* MeshPrimitive);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetItemCollision(FName CollisionName);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		virtual void SetVisibility(bool IsVisibility);



protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
