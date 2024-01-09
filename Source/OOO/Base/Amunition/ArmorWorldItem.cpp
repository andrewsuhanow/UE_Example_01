

// #include "Base/Amunition/ArmorWorldItem.h"
#include "ArmorWorldItem.h"

AArmorWorldItem::AArmorWorldItem()
{
	if (!SkeletalMeshComponent)
	{
		SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
		//SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this, TEXT("SleletalMesh"));
		//SkeletalMeshComponent->RegisterComponent();
		SkeletalMeshComponent->SetupAttachment(Root);
		SkeletalMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
		SkeletalMeshComponent->bHiddenInGame = false;

	}

	if (!StaticMeshComponent)
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
		//StaticMeshComponent = NewObject<UStaticMeshComponent>(this, TEXT("StaticMesh"));
		//StaticMeshComponent->RegisterComponent();
		StaticMeshComponent->SetupAttachment(Root);
		StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
		StaticMeshComponent->bHiddenInGame = false;
	}
}

/* (-------------------------------)
void AArmorWorldItem::SetMesh(UObject* MeshPrimitive)
{

	// ******** if "Skeletal Mesh"
	USkeletalMesh* NewSkeletalMesh = Cast<USkeletalMesh>(MeshPrimitive);
	if (NewSkeletalMesh)
	{
		StaticMeshComponent->SetStaticMesh(nullptr);
		StaticMeshComponent->bHiddenInGame = true;
		SkeletalMeshComponent->SetSkeletalMesh(NewSkeletalMesh);
		SkeletalMeshComponent->bHiddenInGame = false;
		SetActorHiddenInGame(false);
		return;
	}
	else
	{
		SkeletalMeshComponent->SetSkeletalMesh(nullptr);
		SkeletalMeshComponent->bHiddenInGame = true;

		// ******** if "Static Mesh"
		AWorldItem::SetMesh(MeshPrimitive);
	}
}

void AArmorWorldItem::AttachToUnitOnSocket(class AUnit* _UnitOwner, FName Socket)
{
	if (Socket != FName("none"))
	{
		AttachToComponent(_UnitOwner->GetMesh(),
			FAttachmentTransformRules::KeepRelativeTransform, *Socket.ToString());

	}
	else
	{
		AttachToComponent(_UnitOwner->GetMesh(),
			FAttachmentTransformRules::KeepRelativeTransform); // , NAME_None);
	}
}


void AArmorWorldItem::SetVisibility(bool IsVisibility)
{


	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->bHiddenInGame = IsVisibility;		// ** true - Set Visible
	}

	Super::SetVisibility(IsVisibility);
}*/