
#pragma once



// #include "Base/Amunition/Enum/AttackHitCollisionType.h"

//#include "CoreMinimal.h"

UENUM(BlueprintType, Blueprintable)
enum class EAttackHitCollisionType : uint8
{
	// ** Alvays hit at the time
	Simple,	
	// ** collided bound in front 
	Front,	
	// ** collided bound arround  
	Around,	
	// ** injection, RayCast near in front
	Sting,		
	// ** gun firing, RayCast far 
	Fire,		
	// ** fly agent
	Bullet,			
	
	MAX
};
