

// #include "Base/Inventory/Enum/SlotType.h"
#pragma once

//#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class ESlotType : uint8
{
	none = 0,			// 0      // ** Weapon BaseFight don't put to slot

	// ** EQUIP Slot

	cup = 1,			// 1 
	
	armour,				// 2
	clothes,			// 3

	contact_wpn_big,	// 4	LSword, Axe, Pike, Club
	contact_wpn_small,	// 5	Dagger, Sword, Spage

	range_wpn,			// 6	RapidGun, Rifle, Bow, Armbow
	pistol,				// 7	Pistol, ThrowRagger 

	heavy_amunition,				// ** Shield, BigGun, bagpak

	collar,				// 8
	braslet1,			// 9
	braslet2,			// 10

	ring1,				// 11
	ring2,				// 12
	ring3,				// 13
	ring4,				// 14

	// ** Panels Slot

	global_inv,
	main_inv,
	fast_panels,
	Perk_panels,		//777777777777777777777777

	Gloves,				// 77777777777777777777777	
	Boots,				// 777777777777777777777777

	MAX
};


