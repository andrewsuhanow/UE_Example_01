

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
	HealthMax = Other.HealthMax;
	Health = Other.Health;
	ValueKoef = Other.ValueKoef;
	Cost = Other.Cost;
	Waight = Other.Waight;


	AllowInventorySlotType = Other.AllowInventorySlotType;
	InventorySizeX = Other.InventorySizeX;
	InventorySizeY = Other.InventorySizeY;
	ItemStaticMash = Other.ItemStaticMash;
	ItemSkeletalMash = Other.ItemSkeletalMash;

	WeaponDT = Other.WeaponDT;
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


