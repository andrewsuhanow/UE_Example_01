
#pragma once

// #include "../Controller/Task/Enum/TaskType.h"

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
	XXXXX1,
	XXXXX2,

	MAX
};
