
#pragma once

UENUM(BlueprintType) // , Blueprintable

enum class ETaskStatus : uint8
{
	non_task = 0, // ** UMETA(DisplayName = "Visible name"),
	new_task,
	uses_task,
	sub_task,	//** use fromParent
	MAX
};



