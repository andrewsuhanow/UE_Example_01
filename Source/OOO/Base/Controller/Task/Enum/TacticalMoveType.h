
#pragma once

// #include "Base/Controller/Task/Enum/TacticalMoveType.h"

UENUM(BlueprintType)
enum class ETacticalMoveType : uint8
{
	none = 0,

	SimpleMoveToPoint,	//+++				// ** Look forward, Set special speed
	SimpleMoveToActor,	//+++

	MoveToPointWithUnitFocus,	//+++
	MoveToActorWithUnitFocus,	//+++

	MoveToPointWithRotateFix,	//+++
	MoveToActorWithRotateFix,	//+++

	//+++++ MoveToPointWithPOINTFocus,	
	//+++++ MoveToActorWithPOINTFocus,	







	
	MAX
};
