

// #include "Base/Controller/Task/Struct/TaskData.h"

#pragma once

#include "../Enum/TaskCauser.h"
#include "../Enum/TaskPriority.h"

#include "TaskData.generated.h"







USTRUCT(BlueprintType) // , Blueprintable
struct FTaskData
{
	// ** GENERATED_BODY()
	GENERATED_USTRUCT_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		// ** none, newTask,		
		// ** GeneralComand, AIComand, DominantComand, 		
		// ** ChildTask
		ETaskCauser TaskCauser = ETaskCauser::none;
//-------------	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
//-------------		// ** GeneralComand = 0,	AI = 1,		DominantComand = 2
//-------------		ETaskInstigator TaskInstigator = ETaskInstigator::General;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		// ** Normal,  Hi,  Great
		ETaskPriority TaskPriority = ETaskPriority::Normal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")		
		class UTask* TaskRef = nullptr;
		
		// ** What parameter using (Actor, point, rotate)
	//----------------UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
	//----------------	 ETaskDislocation TaskDislocation = ETaskDislocation::PointNoRotate;		// ** PointRotate,  UnitNoRotate,  UnitRotate,  RotatePointNoMove, RotateUnitNoMove

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")			
		TArray<class AUnit*> Unit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")			
		TArray<AActor*> Actor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		TArray<uint8> Uint8Param;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		TArray<int32> Int32Param;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		TArray<float> FloatParam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		TArray<FVector> Vector3dParam;
	//+++++UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
	//+++++	FRotator Rotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")
		TArray<FName> NameParam;


	FTaskData& operator=(const FTaskData& Other)
	{
		// ** this->TaskCauser = Other.TaskCauser;
		//-------------this->TaskInstigator	= Other.TaskInstigator;
		this->TaskPriority		= Other.TaskPriority;
		this->TaskRef			= Other.TaskRef;
		
		// ** Unit
		this->Unit.Reset();
		for (int32 i = 0; i < Other.Unit.Num(); ++i)
			this->Unit.Add(Other.Unit[i]);

		// ** Actor
		this->Actor.Reset();
		for (int32 i = 0; i < Other.Actor.Num(); ++i)
			this->Actor.Add(Other.Actor[i]);

		// ** Vector
		this->Vector3dParam.Reset();
		for (int32 i = 0; i < Other.Vector3dParam.Num(); ++i)
			this->Vector3dParam.Add(Other.Vector3dParam[i]);

		//+++++++++++++++++++++this->Rotation			= Other.Rotation;

		// ** Uint8Param  <uint8>
		this->Uint8Param.Reset();
		for (int32 i = 0; i < Other.Uint8Param.Num(); ++i)
			this->Uint8Param.Add(Other.Uint8Param[i]);

		// ** Int32Param  <uint8>
		this->Int32Param.Reset();
		for (int32 i = 0; i < Other.Int32Param.Num(); ++i)
			this->Int32Param.Add(Other.Int32Param[i]);
		
		// ** FloatParam  <float>
		this->FloatParam.Reset();
		for (int32 i = 0; i < Other.FloatParam.Num(); ++i)
			this->FloatParam.Add(Other.FloatParam[i]);

		// ** NameParam  <FName> ;
		this->NameParam.Reset();
		for (int32 i = 0; i < Other.NameParam.Num(); ++i)
			this->NameParam.Add(Other.NameParam[i]);

		return *this;
	}
};


