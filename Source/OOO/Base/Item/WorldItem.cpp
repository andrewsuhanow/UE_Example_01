

// #include "Base/Item/WorldItem.h"
#include "WorldItem.h"

#include "Components/BoxComponent.h"



AWorldItem::AWorldItem()
{
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = Root;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("NoCollision"));
	Collision->SetupAttachment(Root);
	
	if (ItemDT.MeshPrimitive)
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
		StaticMeshComponent->SetupAttachment(Root);


		SetMesh(ItemDT.MeshPrimitive);
	}
}


void AWorldItem::SetMesh(UObject* MeshPrimitive)
{
	// ******** if "Static Mesh"  
	UStaticMesh* NewStaticMesh = Cast<UStaticMesh>(MeshPrimitive);
	if (NewStaticMesh)
	{
		StaticMeshComponent->SetStaticMesh(NewStaticMesh);
		StaticMeshComponent->bHiddenInGame = false;
		SetActorHiddenInGame(false);
		return;
	}


	StaticMeshComponent->bHiddenInGame = true;
	SetActorHiddenInGame(true);
}






void AWorldItem::SetItemCollision(FName CollisionName)
{
	Collision->SetCollisionProfileName(CollisionName);
}



void AWorldItem::SetVisibility(bool IsVisibility)
{

	if (StaticMeshComponent)
	{
		StaticMeshComponent->bHiddenInGame = IsVisibility;		// ** true - Set Visible
	}
}




void AWorldItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWorldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

