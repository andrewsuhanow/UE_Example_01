
#pragma once

// #include "../Controller/Task/Enum/TaskStatus.h"

UENUM(BlueprintType) // , Blueprintable
enum class ETaskStatus : uint8
{
	none = 0, // ** UMETA(DisplayName = "Visible name"),
	NewTask,

	GeneralComand,
	AIComand,
	DominantComand,

	ChildTask,

	MAX
};



