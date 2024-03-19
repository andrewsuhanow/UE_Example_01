
#pragma once

// #include "Base/Controller/Task/Enum/TaskType.h"

UENUM(BlueprintType)
enum class ETaskType : uint8
{
	none = 0,

	MoveTo = 10,	
	//MovePoint,
	//MoveActor,
	//MovePoint_FixLook,
	//MoveActor_FixLook,
	//MovePoint_LookActor,
	//MoveActor_LookActor,
	
	
	

	//FastMoveToPoint = 1,
	//MoveToPoint,
	//TacticalMove,
	//---BattleSideMove,
	//---BattleRetreatMove,

	Rotate,

	Wait,

	CheckPoint,
	LookOnPoint,

	ActivateWeapon,
	ChangeWeapon,			// ** 7777777777777777777777

	UseAbility,
	WeaponAttack,
	GetHit,
	Parrir,
	Block,
	Dodge,

	XXXXX1,
	XXXXX2,

	DailyBehavior,

	MAX
};
