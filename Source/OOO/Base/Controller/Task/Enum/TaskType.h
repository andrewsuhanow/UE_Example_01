
#pragma once

// #include "Base/Controller/Task/Enum/TaskType.h"

UENUM(BlueprintType)
enum class ETaskType : uint8
{
	none = 0,
	FastMoveToPoint = 1,
	MoveToPoint,
	BattleSideMove,
	BattleRetreatMove,

	RotateToPointFast,
	RotateToPointNormal,
	RotateToPointSlow,
	RotateAngle,

	Wait,

	ActivateWeapon,
	ChangeWeapon,			// ** 7777777777777777777777

	XXXXX1,
	XXXXX2,

	DailyBehavior,

	MAX
};
