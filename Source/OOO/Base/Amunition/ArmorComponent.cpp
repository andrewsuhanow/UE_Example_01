

//#include "Base/Amunition/ArmorComponent.h"
#include "ArmorComponent.h"

#include "ArmorWorldItem.h"

#include "ArmorDT.h"

#include "../Unit/Base/Unit.h"



UArmorComponent::UArmorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UArmorComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UArmorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}





void UArmorComponent::InitArmor(AUnit* _UnitOwner)
{
	UnitOwner = _UnitOwner;


	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ** All Armor_Class
	for (int32 i = 0; i < Armor_class.Num(); ++i)
	{
		if (Armor_class[i])
		{
			AArmorWorldItem* ArmorTEMP = GetWorld()->SpawnActor<AArmorWorldItem>(
				Armor_class[i],
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				spawnParameters);

			if (ArmorTEMP)
			{
				ArmorTEMP->SetItemCollision(FName("NoCollision"));
				// ** ArmorTEMP->SetAmunitionMesh(nullptr);
				// ** ArmorTEMP->AttachToUnitOnSocket(UnitOwner, SocketName, bIsArmor);	
				ArmorSlot.Add(ArmorTEMP);
			}
		}
	}
}




bool UArmorComponent::EquipArmorByItemDT(const FItemDT* _ItemDT)
{
	if (!_ItemDT)
		return false;
	
	UArmorDT* newItemArmorDT;

	if (!_ItemDT->IsSlotEmpty() && _ItemDT->ArmorDT)
	{
		newItemArmorDT = _ItemDT->ArmorDT->GetDefaultObject<UArmorDT>();
		
		for (int32 i = 0; i < ArmorSlot.Num(); ++i)
		{

			if (ArmorSlot[i]->EquipSlotTypeFix == newItemArmorDT->AllowInventorySlotType)
			{
				ArmorSlot[i]->ItemDT = *_ItemDT;
				ArmorSlot[i]->SetMesh(ArmorSlot[i]->ItemDT.MeshPrimitive);


				FName newSocket = FName("none");

				if (UnitOwner->IsWeaponActive())
				{
					newSocket = newItemArmorDT->SocketActivated;
				}
				else
				{
					newSocket = newItemArmorDT->SocketUnactivated;
				}

				bool isArmor = true;
				ArmorSlot[i]->AttachToUnitOnSocket(UnitOwner, newSocket, isArmor);

				return true;
			}
		}
	}

	return false;
}