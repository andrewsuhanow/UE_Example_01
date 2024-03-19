

// #include "Base/UnitState/Enum/UnitParam.h"

#pragma once


UENUM(BlueprintType, Blueprintable)
enum class EUnitParam : uint8
{

	// ** i + 0:	Base-Value
	// ** i + 1:	Max-Value
	// ** i + 2:	Reg-Value
	// ** i + 3:	Min-Value	(HP only)
	// ** i + 4:	Crit-Value	(HP only)


	// ** if( i < 10) { it HP Block }


	HP		= 0,			// ** HP - Health
	MaxHP	= 1,
	RegHP	= 2,
	MinHP	= 3,
	CritHP	= 4,			/// ** value lov then zero, when Unit olmost dead but still alive
	
	//------------



	// ** if( i >= 10 && i < 100) { it Other Param Block }


	MP		= 10,			// ** MP - Mana-Point
	MaxMP	= 11,
	RegMP	= 12,

	//------------

	AP		= 15,			// ** AP - Action-Point
	MaxAP	= 16,
	RegAP	= 17,

	//------------

	DP		 = 20,			// ** DP - Defense-Point
	MaxDP	 = 21,
	RegDP	 = 22,

	//------------

	MSP		= 25,			// ** MSP - Magic-Shield-Point
	MaxMSP	= 26,
	RegMSP	= 27,

	//------------

	SP		= 30,			// ** SP - Stamina-Point
	MaxSP	= 31,
	RegSP	= 32,

	//------------




	// ** if( i >= 100) { it Other Single-Param Block }


	PotentialHP = 100,

	DefenseKoef,			// ** how mutch damage take an Armor, and how mutch an Unit
	ArmorMultiply,			// ** Armor will take a low damage then real hit caudsed

	LVL,
	Exp,
	NextExp,


	none = 200			UMETA(DisplayName = "none"),


	//TotalWpnLevel,
	//TotalWpnLevel_add,

	//TotalGunLevel,
	//TotalGunLevel_add,

	//TotalMagikLevel,
	//TotalMagikLevel_add,

	MAX
};

