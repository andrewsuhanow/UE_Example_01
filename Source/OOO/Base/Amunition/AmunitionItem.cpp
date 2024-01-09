

//#include "../Amunition/AmunitionItem.h"
#include "AmunitionItem.h"

#include "../Unit/Base/Unit.h"



/*(-------------------------------)
bool AAmunitionItem::EquipAmunitionByItemDT(const FItemDT* _ItemDT)
{
	return EquipWeaponByItemDT(_ItemDT);
}
*/
void AAmunitionItem::SetMesh(UObject* MeshPrimitive)
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
		Super::SetMesh(MeshPrimitive);
	}
}



void AAmunitionItem::AttachToUnitOnSocket(class AUnit* _UnitOwner, FName Socket, bool IsArmor)
{
	if (IsArmor)
	{
		// ** Static Armor 
		/// *777*  or (Static animate Armor)  
		if (Socket != FName("none"))
		{
			AttachToComponent(_UnitOwner->GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale, *Socket.ToString());
		}

		// ** Skeletal Armour  (Unit-body-Skeletal)       
		else
		{
			AttachToComponent(_UnitOwner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

			SkeletalMeshComponent->SetWorldLocationAndRotation(
				_UnitOwner->GetMesh()->GetComponentLocation(), _UnitOwner->GetMesh()->GetComponentRotation());

			SkeletalMeshComponent->SetMasterPoseComponent(_UnitOwner->GetMesh());
		}
	}

	// ** Weapon
	else
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
}


void AAmunitionItem::SetVisibility(bool IsVisibility)
{

	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->bHiddenInGame = IsVisibility;		// ** true - Set Visible
	}

	Super::SetVisibility(IsVisibility);
}
