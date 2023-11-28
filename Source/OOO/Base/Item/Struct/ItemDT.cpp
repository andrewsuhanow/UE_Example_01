

// #include "Base/Item/Struct/ItemDT.h"
#include "ItemDT.h"

#include "../../Amunition/WeaponDT.h"  
//++++++++++++++++++++++++#include "../../Amunition/Srtuct/ArmorParamr.h"  




FItemDT::FItemDT(const FItemDT& Other)
{
	GameName = Other.GameName;
	Description = Other.Description;
	ItemImage = Other.ItemImage;

	ItemOneCellImage = Other.ItemOneCellImage;
	IsStackable = Other.IsStackable;
	Count = Other.Count;
	CountMax = Other.CountMax;
	HealthMax = Other.HealthMax;
	Health = Other.Health;
	ValueKoef = Other.ValueKoef;
	Cost = Other.Cost;
	Waight = Other.Waight;


	AllowInventorySlotType = Other.AllowInventorySlotType;
	InventorySizeX = Other.InventorySizeX;
	InventorySizeY = Other.InventorySizeY;
	MeshPrimitive = Other.MeshPrimitive;

	WeaponDT = Other.WeaponDT;
}

FItemDT& FItemDT::operator=(const FItemDT& Other)
{
	GameName = Other.GameName;
	Description = Other.Description;
	ItemImage = Other.ItemImage;

	ItemOneCellImage = Other.ItemOneCellImage;
	IsStackable = Other.IsStackable;
	Count = Other.Count;
	CountMax = Other.CountMax;
	HealthMax = Other.HealthMax;
	Health = Other.Health;
	ValueKoef = Other.ValueKoef;
	Cost = Other.Cost;
	Waight = Other.Waight;


	AllowInventorySlotType = Other.AllowInventorySlotType;
	InventorySizeX = Other.InventorySizeX;
	InventorySizeY = Other.InventorySizeY;
	MeshPrimitive = Other.MeshPrimitive;

	WeaponDT = Other.WeaponDT;

	return *this;
}

bool operator==(const FItemDT& Self, const FItemDT& Other)
{
	if (Self.GameName == Other.GameName &&
		Self.Description == Other.Description &&

		Self.ItemImage == Other.ItemImage &&
		Self.ItemOneCellImage == Other.ItemOneCellImage &&

		Self.IsStackable == Other.IsStackable &&
		// ** Self.Count == Other.Count;
		Self.CountMax == Other.CountMax &&

		Self.HealthMax == Other.HealthMax &&
		Self.Health == Other.Health &&

		Self.ValueKoef == Other.ValueKoef &&
		Self.Cost == Other.Cost &&
		Self.Waight == Other.Waight &&

		Self.AllowInventorySlotType == Other.AllowInventorySlotType &&

		Self.InventorySizeX == Other.InventorySizeX &&
		Self.InventorySizeY == Other.InventorySizeY &&

		Self.MeshPrimitive == Other.MeshPrimitive &&

		Self.WeaponDT == Other.WeaponDT)
	{
		return true;
	}
	return false;
}







bool FItemDT::IsSlotEmpty() const
{
	// ** true: if slot empty
	return (Count <= 0) ? true : false;
}


void FItemDT::SetSlotEmpty()
{
	Count = -1;
	ItemImage = nullptr;
	ItemOneCellImage = nullptr;
}



bool FItemDT::IsItemStackable() const
{
	return IsStackable;
}





UTexture2D* FItemDT::GetFullImage() const
{
	return ItemImage;
}
UTexture2D* FItemDT::GetOneSlotImage() const
{
	return ItemOneCellImage;
}

int32 FItemDT::GetItemHorizontalSize() const
{
	return InventorySizeX;
}

int32 FItemDT::GetItemVerticalSize() const
{
	return InventorySizeY;
}


bool FItemDT::IsItemWeapon()
{ 
	return WeaponDT ? true : false;
}
/*
bool FItemDT::IsItemArmor()
{
	return ArmorClass ? true : false;
}
*/


