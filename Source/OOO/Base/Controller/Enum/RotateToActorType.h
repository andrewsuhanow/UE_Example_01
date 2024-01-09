
#pragma once

// #include "Base/Controller/Enum/RotateToActorType.h"

UENUM(BlueprintType)
enum class ERotateToActorType : uint8
{
	none = 0,

	Forward,
	ForwardLeft,	
	ForwardRight,	

	Back,
	   	  
	
	MAX
};
