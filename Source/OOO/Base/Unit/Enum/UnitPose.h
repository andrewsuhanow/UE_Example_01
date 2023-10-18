

//#include "../../Unit/Enum/UnitPose.h"

#pragma once


UENUM(BlueprintType, Blueprintable)
enum class EUnitPose : uint8
{
	Crawl			UMETA(DisplayName = "Crawl"),
	Crouch,
	StandRelax,		// ** slow walk
	Stand,			// ** walk
	Run,
	Sprint,
	Fly,
	//Error,			// ** pose is ebsent
	MAX
};