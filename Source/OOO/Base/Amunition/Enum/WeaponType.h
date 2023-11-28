
#pragma once



// #include "Base/Amunition/Enum/WeaponType.h"

//#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class EWeaponType : uint8
{
	none,

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

	Dagger,				// ** 777777
	Pistol,

	Bow,
	Rifle,
	RapidGun,
	HeavyGun,

	Throw,				// **  77777777
	
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
