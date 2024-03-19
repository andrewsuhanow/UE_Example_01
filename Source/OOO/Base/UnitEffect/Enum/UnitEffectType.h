
#pragma once



// #include "Base/UnitEffect/Enum/UnitEffectType.h"

//#include "CoreMinimal.h"


////--------------------------------------------------------  Use  UObject insted
////--------------------------------------------------------  Use  UObject insted
////--------------------------------------------------------  Use  UObject insted
////--------------------------------------------------------  Use  UObject insted
////--------------------------------------------------------  Use  UObject insted
////--------------------------------------------------------  Use  UObject insted
////--------------------------------------------------------  Use  UObject insted
////--------------------------------------------------------  Use  UObject insted
////--------------------------------------------------------  Use  UObject insted

UENUM(BlueprintType, Blueprintable)
enum class EUnitEffectType : uint8

{
	none = 0, 

	ChangeTargetParam,

	TargetPlayMontage,

/*	DecorateTrangformTargetMesh,	// ** for a while
	TrangformTarget,

	SpawnUnitNearby,			// ** CreateCoverObstacle
	SpawnUnitInLocation,
	Harvest,					// ** need ResourseActor

	Invisible,			//** !!!!!!!!!!!!@@@@@@@@@@@@@@@@!!!!!!!!!!!
	TakeCover,			//** !!!!!!!!!!!!@@@@@@@@@@@@@@@@!!!!!!!!!!!
	BuringDiging,			//** !!!!!!!!!!!!@@@@@@@@@@@@@@@@!!!!!!!!!!!
	Faster_AllSlowMotion,			//** !!!!!!!!!!!!@@@@@@@@@@@@@@@@!!!!!!!!!!!
	Rentgen,			//** !!!!!!!!!!!!@@@@@@@@@@@@@@@@!!!!!!!!!!!

	SelectTarget,
	Move,	// ** 
	WeaponAttack,	// ** 
	StelsMoveToPoint_InvisibleAndCovering,	// ** 
	UpStairs,	// ** 
	Jump,	// ** 
	
	DropItem,	// ** 
	PutTrap,	// ** 
	PickUp,	// ** 
	ThrowItem,	// ** 
	ActivateObject,		// ** 		
	AttractAttention,	// ** 
	ControllUnit,	// ** 
	
	AddItem,	// ** 
	RemoveItem,	// ** 
	ChangeItem,	// ** 
	AddItemToSlotIndex,	// ** 
	RemoveItemFromSlotIndex,	// ** 
	ChangeItemInSlotIndex,	// ** 
*/







/*
	SelectTarget__,

	ApplayEffectToUnit__,

	FireBall__,
	HealthSelf__,
	HealthOther__,
	MagicAOE__,

	

	Invisible,

	BuringDiging,

	CreateCoverObstacle,

	TakeCover,

	
	

	

	

	SumonNearby_Building,

	SumonAtPoint,

	Transform,
	



	Faster_AllSlowMotion,

	// ** 

	ChangeStatePermanent,	// ** (AppSkill, Rengen)
	ChangeStateHolding,
	ChangeStateDurationInTime,

	// ** 

	AddItem,
	RemoveItem,
	ChangeItem,
	AddItemToSlotIndex,
	RemoveItemFromSlotIndex,
	ChangeItemInSlotIndex,
	
	// ** Action

	WeaponAttack,
	StelsMoveToPoint_InvisibleAndCovering,

	UpStairs,
	Move,
	StopMove,
	Jump,
	DropItem,
	PutTrap,
	PickUp,
	Harvest,
	ThrowItem,
	ActivateObject,
	
	AttractAttention,
	ControllUnit,

	// ** Action Use item

	


	// -------------------------------
	drink,

	//--throw_sing,
	//--throw_knife,

	//--use_up,
	//--usem_middle,
	//--use_down,

	//--harvest,

	//--pick_up,
	drop,

	health,
*/
	MAX
};
