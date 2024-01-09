
// #include "Base/Amunition/WeaponWorldItem.h"
#include "WeaponWorldItem.h"

#include "WeaponDT.h"




AWeaponWorldItem::AWeaponWorldItem()
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


int32 AWeaponWorldItem::GetSelectedAttackIndex()
{

	if (SelectedAttacIndex != -1)
		return SelectedAttacIndex;

	else if (PermanentAttacIndex != -1)
		return PermanentAttacIndex;

	else
		return -1;

}

bool AWeaponWorldItem::IsAttackIndexCorrect(int32 Index)
{
	UWeaponDT* weaponDT_CDO = ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();
	return (weaponDT_CDO->AttakParam.Num() > Index);
}


TArray<ETacticalMoveStepLogic>* AWeaponWorldItem::GetCurrTacticalMoveSteps()
{
	UWeaponDT* weaponDT_CDO = ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();
	return &weaponDT_CDO->TacticalMoveStepLogic;
}

/*
void AWeaponWorldItem::SetMesh(UObject* MeshPrimitive)
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



void AWeaponWorldItem::AttachToUnitOnSocket(class AUnit* _UnitOwner, FName Socket)
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


void AWeaponWorldItem::SetVisibility(bool IsVisibility)
{


	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->bHiddenInGame = IsVisibility;		// ** true - Set Visible
	}

	Super::SetVisibility(IsVisibility);
}
*/


bool AWeaponWorldItem::IcCanEquipItemOnSlot(const FItemDT& _Item, ESlotType SlotType)
{
	if (SlotType == ESlotType::none)
	{
		//++++ find weapon by slot
	}

	return false;
}
bool AWeaponWorldItem::EquipItemOnSlot(const FItemDT& _Item, ESlotType SlotType)
{
	if (SlotType == ESlotType::none)
	{
		//++++ find weapon by slot
	}

	return false;
}

bool AWeaponWorldItem::IsCanEquipItemOnIndex(const FItemDT& _Item, int32 _Index)
{
	if(_Index == -1)
		return false;

	return false;
}
bool AWeaponWorldItem::EquipItemOnIndex(const FItemDT& _Item, int32 _Index)
{
	if (_Index == -1)
		return false;

	return false;
}