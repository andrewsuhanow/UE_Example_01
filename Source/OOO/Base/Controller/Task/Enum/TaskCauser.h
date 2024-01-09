
#pragma once

// #include "../Controller/Task/Enum/TaskCauser.h"

UENUM(BlueprintType)
enum class ETaskCauser : uint8
{
	none = 0,			// ** UMETA(DisplayName = "Visible name"),


	FractionTask,
	NpcTask,
	CriticalTask,

	FractionTask_New,
	NpcTask_New,
	CriticalTask_New,

	ChildTask,

	MAX
};



