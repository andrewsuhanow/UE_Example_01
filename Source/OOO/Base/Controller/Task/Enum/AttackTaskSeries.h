
#pragma once

// #include "Base/Controller/Task/Enum/AttackTaskSeries.h"

UENUM(BlueprintType)
enum class EAttackTaskSeries : uint8
{
	none = 0,

	first_attack_first_actor,

	start_first_series = 100,

	start_second_series = 200,

	MAX
};
