
#pragma once

// #include "Base/Controller/Task/Enum/ETaskStep.h"



// ** Use in Task: TCheckPoint     **    Do it separ file


UENUM(BlueprintType)
enum class ETaskStep111 : uint8
{
	none = 0,
	Move,
	PartMove,
	FirstRotate,

	MAX
};
