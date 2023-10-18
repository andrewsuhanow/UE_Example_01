
#pragma once

// #include "../Controller/Task/Enum/TaskDislocation.h"

UENUM(BlueprintType)
enum class ETaskDislocation : uint8
{
	PointNoRotate,
	PointRotate,
	UnitNoRotate,				// ** move no rotate
	UnitRotate,					// ** move and rotate
	RotatePointNoMove,
	RotateUnitNoMove,
	RotatePointFocusNoMove,		// ** Rotate before attack
	RotateUnitFocusNoMove,		// ** Rotate before attack
	// ChangeWeapon
	// ChangeWPose
	MAX
};
