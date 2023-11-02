
#pragma once



//#include "Amunition/Enum/EWeaponType.h"

//#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class EWeaponType : uint8
{
	Locomotion, // Base_Locomotion,

	HandFight,
	Staff,
	Pike,

	Sword,
	Axe,

	Shield,

	Rapier,
	BigAxe,
	LongSword,
	Glefa,

	Dagger,
	Pistol,

	Bow,
	Rifle,
	RapidGun,
	HeavyGun,

	Throw,
	
	//Mage,


	MG_Fire,																		
	MG_Blizzard,
	MG_Water,
	MG_Wind,
	MG_Earth,
	MG_Body,
	MG_Spirit,
	MG_Mind,

	MAX
};
