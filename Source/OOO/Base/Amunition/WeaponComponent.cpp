

// #include "Base/Amunition/WeaponComponent.h"
#include "WeaponComponent.h"

#include "WeaponWorldItem.h"
#include "WeaponDT.h"

#include "../Unit/Base/Unit.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}



void UWeaponComponent::InitWeapons(AUnit* _UnitOwner)
{
	UnitOwner = _UnitOwner;

	
	// set LocomotionPose
	UnitOwner->SetWeaponAnimType(EWeaponType::Locomotion);
	

	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ** Hand-Fight-Data
	if (HandFightData.WeaponDT)
	{
		AWeaponWorldItem* WeaponTEMP = GetWorld()->SpawnActor<AWeaponWorldItem>(
			AWeaponWorldItem::StaticClass(),
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			spawnParameters);
		if (WeaponTEMP)
		{
			WeaponTEMP->EquipSlotTypeFix = ESlotType::hand_fight;
			WeaponTEMP->SetItemCollision(FName("NoCollision"));
			// ** WeaponTEMP->AttachToUnitOnSocket(UnitOwner);		// ** done it in construct    

			WeaponSlot.Add(WeaponTEMP);

			// ** set as equip
			WeaponSlot.Last()->ItemDT = HandFightData;
			WeaponSlot.Last()->ItemDT.Count = 1;

			// ** set as selected
			SelectedWeaponSlot = WeaponSlot.Num() - 1;
		}
	}


	// ** All Weapon_Class
	for (int32 i = 0; i < Weapon_class.Num(); ++i)
	{
		if (Weapon_class[i])
		{
			AWeaponWorldItem* WeaponTEMP = GetWorld()->SpawnActor<AWeaponWorldItem>(
				Weapon_class[i],
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				spawnParameters);

			if (WeaponTEMP)
			{
				WeaponTEMP->SetItemCollision(FName("NoCollision"));
				// ** ArmorTEMP->SetAmunitionMesh(nullptr);
				// ** WeaponTEMP->AttachToUnitOnSocket(UnitOwner, SocketName);		   
				WeaponSlot.Add(WeaponTEMP);
			}
		}
	}
}





bool UWeaponComponent::SetWeaponSlotSelected(int32 _WeaponSlotIndex)
{

	bool isWpnSlotIndexError = false;

	if (_WeaponSlotIndex > WeaponSlot.Num()-1 || _WeaponSlotIndex < 0)
	{
		isWpnSlotIndexError = true;
	}
	else if(WeaponSlot[_WeaponSlotIndex]->ItemDT.IsSlotEmpty())
	{
		isWpnSlotIndexError = true;
	}
	else
	{
		SelectedWeaponSlot = _WeaponSlotIndex;
		UnitOwner->UpdateAttacksWpnPanel_HUD();
		return true;
	}

	// ** set first available slot
	for (int32 i = 0; i < WeaponSlot.Num(); ++i)
	{
		if (!WeaponSlot[i]->ItemDT.IsSlotEmpty())
		{
			SelectedWeaponSlot = _WeaponSlotIndex;
			UnitOwner->UpdateAttacksWpnPanel_HUD();
			return true;
		}
	}
	return false;
}

/*
int32 UWeaponComponent::GetWeaponSlotSelected()
{
	return SelectedWeaponSlot;
}
*/

bool UWeaponComponent::IsWeaponActive()
{
	if (iWeaponActive)
		return true;
	else
		return false;
}

int32 UWeaponComponent::GetSelectedWeaponSlotIndex()
{
	if (SelectedWeaponSlot < 0)
		return -1;
	if (SelectedWeaponSlot >= WeaponSlot.Num())
		return -1;
	if (WeaponSlot[SelectedWeaponSlot]->ItemDT.IsSlotEmpty())
		return -1;

	// ** if (iWeaponActive) 
	return SelectedWeaponSlot;
}

void UWeaponComponent::GetSelectedWeaponAttacksData(TArray<UTexture2D*> &_attackImage,
	int32 &_SelectIndex, int32 &_PermanentIndex)
{
	if (SelectedWeaponSlot < 0)
		return;
	if (SelectedWeaponSlot >= WeaponSlot.Num())
		return;

	UWeaponDT* weaponDT = WeaponSlot[SelectedWeaponSlot]->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();

	_SelectIndex = WeaponSlot[SelectedWeaponSlot]->SelectedAttacIndex;
	_PermanentIndex = WeaponSlot[SelectedWeaponSlot]->PermanentAttacIndex;

	for (int32 i = 0; i < weaponDT->AttakParam.Num(); ++i)
	{
		_attackImage.Add(weaponDT->AttakParam[i].ButtonImage);
	}
	
}

EWeaponType UWeaponComponent::GetWeaponTypeBySlotIndex(int32 _SlotIndex) const
{
	if (_SlotIndex < 0)
		return EWeaponType::none;
	if(_SlotIndex >= WeaponSlot.Num())
		return EWeaponType::none;
	if (WeaponSlot[_SlotIndex]->ItemDT.IsSlotEmpty())
		return EWeaponType::none;

	UWeaponDT* itemWeaponDT;

	if (WeaponSlot[_SlotIndex]->ItemDT.WeaponDT)
	{
		itemWeaponDT = WeaponSlot[_SlotIndex]->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();

		return itemWeaponDT->WeaponType;
	}

	return EWeaponType::none;
}

bool UWeaponComponent::ActivateWeapon()
{
	
	if(SelectedWeaponSlot < 0)
		return false;

	UWeaponDT* weaponDT_CDO = WeaponSlot[SelectedWeaponSlot]->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();

	FName NewSocket = FName("none");
	NewSocket = weaponDT_CDO->SocketActivated;
	WeaponSlot[SelectedWeaponSlot]->AttachToUnitOnSocket(UnitOwner, NewSocket);

	// set LocomotionPose
	UnitOwner->SetWeaponAnimType(weaponDT_CDO->WeaponType);

	iWeaponActive = true;

	return true;
}

bool UWeaponComponent::UnactivateWeapon()
{
	if (SelectedWeaponSlot < 0)
		return false;

	UWeaponDT* weaponDT_CDO = WeaponSlot[SelectedWeaponSlot]->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();

	FName NewSocket = FName("none");
	NewSocket = weaponDT_CDO->SocketUnactivated;
	WeaponSlot[SelectedWeaponSlot]->AttachToUnitOnSocket(UnitOwner, NewSocket);

	// set LocomotionPose
	UnitOwner->SetWeaponAnimType(EWeaponType::Locomotion);

	iWeaponActive = false;

	return true;
}



//-----FItemDT* UWeaponComponent::GetCurrWeaponData()
AWeaponWorldItem* UWeaponComponent::GetCurrWeaponItem()
{
	if (SelectedWeaponSlot < 0)
		return nullptr;

	//------return &WeaponSlot[SelectedWeaponSlot]->ItemDT;
	return WeaponSlot[SelectedWeaponSlot];
}



EWeaponType UWeaponComponent::GetCurrentWeaponType()
{
	int32 SelectSlot = IsWeaponActive();
	if (SelectSlot != -1)
	{
		UWeaponDT* weaponDT_CDO = WeaponSlot[SelectSlot]->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();
		if (weaponDT_CDO)
			return weaponDT_CDO->WeaponType;
	}
	return EWeaponType::Locomotion;
}


bool UWeaponComponent::EquipWeaponByItemDT(const FItemDT* _ItemDT)
{
	if (!_ItemDT)
		return false;

	UWeaponDT* newItemWeaponDT;

	if (!_ItemDT->IsSlotEmpty() && _ItemDT->WeaponDT)
	{
		newItemWeaponDT = _ItemDT->WeaponDT->GetDefaultObject<UWeaponDT>();

		for (int32 i = 0; i < WeaponSlot.Num(); ++i)
		{
			if (WeaponSlot[i]->EquipSlotTypeFix == newItemWeaponDT->AllowInventorySlotType)
			{
				WeaponSlot[i]->ItemDT = *_ItemDT;
				WeaponSlot[i]->SetMesh(WeaponSlot[i]->ItemDT.MeshPrimitive);


				FName newSocket = FName("none");

				if (IsWeaponActive())
				{
					newSocket = newItemWeaponDT->SocketActivated;

					// ** Anim Instance - Set AnimType
					EWeaponType newAnimType = newItemWeaponDT->WeaponType;
					UnitOwner->SetWeaponAnimType(newAnimType);
				}
				else
				{
					newSocket = newItemWeaponDT->SocketUnactivated;
				}

				WeaponSlot[i]->AttachToUnitOnSocket(UnitOwner, newSocket);

				return true;
			}
		}
	} 
	return false;
}




bool UWeaponComponent::IsEquipPanelSlotEmpty(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= WeaponSlot.Num())
		return true;

	if (WeaponSlot[SlotIndex]->ItemDT.IsSlotEmpty())
		return true;


	return false;
}

FItemDT* UWeaponComponent::GetItemRefFromEquipPanel(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= WeaponSlot.Num())
		return nullptr;

	if (WeaponSlot[SlotIndex]->ItemDT.IsSlotEmpty())
		return nullptr;
	else
		return &(WeaponSlot[SlotIndex]->ItemDT);

	return nullptr;
}

void UWeaponComponent::RemoveItemFromEquipPanel(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= WeaponSlot.Num())
		return;

	WeaponSlot[SlotIndex]->ItemDT.SetSlotEmpty();

	// ** Set-Amunition-Mesh
	//--XXX--Weapon_DecorObj[CurrentWeapon_Index]->SetAmunitionMesh(Weapon_DecorObj[CurrentWeapon_Index]->GetAmunition_StaticMesh_If());

	// ** Attach to Back
	//FName NewSocket = Weapon_DecorObj[CurrentWeapon_Index]->WpnParam.Socket_Unactivated;
	//Weapon_DecorObj[CurrentWeapon_Index]->AttachToUnitOnPosition(owner, NewSocket);
}




// ---------------------------------------------


bool UWeaponComponent::GetWeaponSlotsListData(//)
	TArray<int32> &_WeaponSlotsIndex,
	TArray<ESlotType> &_WeaponSlotsType,
	TArray<UTexture2D*> &_WeaponSlotsTexture)
{
	for (int32 i = 0; i < WeaponSlot.Num(); ++i)
	{
		if (!WeaponSlot[i]->ItemDT.IsSlotEmpty() && WeaponSlot[i]->ItemDT.WeaponDT)
		{
			UWeaponDT* weaponDT_CDO = WeaponSlot[i]->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();
			if(weaponDT_CDO)
				_WeaponSlotsType.Add(weaponDT_CDO->AllowInventorySlotType);
			
			_WeaponSlotsIndex.Add(i);
			_WeaponSlotsTexture.Add(WeaponSlot[i]->ItemDT.GetOneSlotImage());
		}
	}
	return true;
}


bool UWeaponComponent::GetCurrentWeaponSlotData(//)
	int32& _WeaponSlotsIndex,
	ESlotType& _WeaponSlotsType,
	UTexture2D*& _WeaponSlotsTexture)
{
	if(SelectedWeaponSlot >= 0)
	{
		UWeaponDT* weaponDT_CDO = WeaponSlot[SelectedWeaponSlot]->ItemDT.WeaponDT->GetDefaultObject<UWeaponDT>();
		if (weaponDT_CDO)
			_WeaponSlotsType = weaponDT_CDO->AllowInventorySlotType;

		_WeaponSlotsIndex = SelectedWeaponSlot;
		_WeaponSlotsTexture = WeaponSlot[SelectedWeaponSlot]->ItemDT.GetOneSlotImage();
		return true;
	}
	return false;
}