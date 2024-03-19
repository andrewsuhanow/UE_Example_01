

// #include "Base/Inventory/Enum/SlotType.h"
#pragma once

//#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class ESlotType : uint8
{
	none = 0,			// 0      // ** Weapon BaseFight don't put to slot
	World,

	global_inv,
	main_inv,
	fast_panel,
	Perk_panel,		
	weapon_panel,
	weapon_attacks_panel,
	task_queue_panel,
	ability_container,

	heavy_amunition,				// ** Shield, BigGun, bagpak


	weapon_equip = 50,
	contact_wpn_big,	// LSword, Axe, Pike, Club
	contact_wpn_small,	// Dagger, Sword, Spage
	range_wpn,			// RapidGun, Rifle, Bow, Armbow
	pistol,				// Pistol, ThrowRagger 
	heavy_gun,
	hand_fight,			// ** INVISIBLE slot

	armor_equip = 100,
	cup,				// 
	armour,				// 
	clothes,			// 
	collar,				// 
	braslet1,			// 
	braslet2,			// 
	ring1,				// 
	ring2,				// 
	ring3,				// 
	ring4,				// 

	shield,

	//Gloves,				// 77777777777777777777777	
	//Boots,				// 777777777777777777777777

	unit_effect = 150,

	MAX
};


