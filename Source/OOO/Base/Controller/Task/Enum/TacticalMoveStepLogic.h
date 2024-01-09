
#pragma once

// #include "Base/Controller/Task/Enum/TacticalMoveStepLogic.h"

UENUM(BlueprintType)
enum class ETacticalMoveStepLogic : uint8
{
	none = 0,

	LongWait,
	NormalWait,
	ShortWait,	

	// ** Move side depend target rotation
	// ** Righr or left (try move around target)
	RightOrLeft,
	Forward,

	// ** Move forward (if dist more then Optimal-Attack-Dist-for-weapon * 3) 
	// ** or Move side (oposit target rotation)
	MoveForward_IF__MoweSide,

	// ** Move forward (if dist more then Optimal-Attack-Dist-for-weapon * 3) 
	// ** or Wait in place
	MoveForward_IF__Wait,


	   


	TEST,

	MAX
};
