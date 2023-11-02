

// #include "Base/Item/Struct/ItemDT.h"
#include "ItemDT.h"

#include "../../Amunition/WeaponDT.h"  
//++++++++++++++++++++++++#include "../../Amunition/Srtuct/ArmorParamr.h"  







UTexture2D* FItemDT::GetFullImage()
{
	return ItemImage;
}
UTexture2D* FItemDT::GetOneSlotImage()
{
	return ItemOneCellImage;
}

int32 FItemDT::GetItemHorizontalSixe() const
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


