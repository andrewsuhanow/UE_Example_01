

#include "../Enum/TaskStatus.h"
//#include "../Task/Base/Task.h"

#include "TaskData.generated.h"

USTRUCT(BlueprintType) // , Blueprintable
struct FTaskData
{
	// ** GENERATED_BODY()
	GENERATED_USTRUCT_BODY()

		// ** Current Task status: (non_task, new_task, uses_task, sub_task)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
		ETaskStatus TaskStatus = ETaskStatus::non_task;
		// ** Current Task Type: (Move, UseWeapon, ActivateWeapon, ....)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
		class UTask* TaskRef = nullptr;

	//Unit*;
	//Point;
	//Dir;

		// ** Task stage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
		int32 CurrStage = 0;




};
