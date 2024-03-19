






// ** Level
// ** Body
// ** Agil
// ** Observ
// ** Will(mana)
// ** Con(Pow)
// ** 
// ** Total-Wpn-Level
// ** Wpn-Slot-Skill
// ** 
// ** Total-Gun-Level
// ** Gun-Slot-Skill
// ** 
// ** Total-Magik-Level
// ** Magik-Slot-skill
// ** 
// ** Armor-Skill 
// ** 

// Pow
// Hp		  : +(Body)
// BodyArmor  : +(Body)
// Stamina    : +(Body, Agil)
// RegenHP    : +(Body)
// RegStamina : +(Body)
// DefSkill   : +(Body, Agil)
// AttackSkill: +(Pow / Observ)
// Тochnost   : +(Observ)
// MagicPow   : +(Con)
// Mana	      :	+(Will)
// PowArmor   : +(Con, Will)
// RegMana    : +(Will)

// WpnItm  : Damage	  : +Slf(Itm) -Enm(Armor)		<if Hit Succes>
// WpnItm  : Penetrat : +(Itm, Pow)
// WpnComp :
// ArmComp : Armor    : +(Itm)

// GetHit  :

// Parrir	= +Slf(Agil, Defence, Wpn-Skill)		
//			  -Enm(Attack, Wpn-Skill, Pow)
// Block	= (Agil, Pow, Defence, Armor-Skill)		
//			  -Enm(Attack, Wpn-Skill, Pow)
// dodge	= (Agil)								
//			  -Enm(Attack, Wpn-Skill, Agil)




	



//-------------------------------------------------------------------

// ** stabbing			war-20__?@				Ranger-20__?1@	Assas-10__?@					Magwar-10__?2@
// ** cutting			war-20__?@				Ranger-20__?1@	Assas-10__?@					Magwar-10__?2@
// ** crushing			war-20__?@																Magwar-10__?2@

// ** 

// ** Pow				war-40		Arh-10	    Ranger-20__?2@									Magwar-10__?3@
// ** Heal				war-40					Ranger-30		Assas-10						Magwar-10					
// ** Agil									    Ranger-20__?3@	Assas-40						Magwar-10__?1@
//----Speed									  --Ranger-40--										
// ** Observ						Arh-90		Ranger-20__?3@	Assas-40						Magwar-10__?1@
// ** Will(mana)								Ranger-30__?4@					Mag-40			Magwar-10
// ** Con(Pow)									Ranger-20__?4@					Mag-40			Magwar-20

// ** Fire																		Mag-20__?@		
///			: DAMAGE-100,						 Speed-60)  
// ** Blizzard																					Magwar-20
///			: Damage-60, STOP-100,						   Teleport-30)  
// ** Water										 Ranger-20__?1@
///			:															  HEALTH-100, Slow-30,			      Drain-30)
// ** Wind										 Ranger-20__?1@
///			: 									 SPEED-100, TELEPORT-100) 
// ** Earth																						Magwar-20
///			: 			 Stop-30,										  Health-30,  SLOW-100, Transform-30)
// ** Substance																	Mag-20__?@
///			: Damage-30, Stop-60,																TRAMSFORM-100)
// ** Spirit																	Mag-20__?@
///			: Damage-30,			Control-30															      DRAIN-100)
// ** Mind																		Mag-20__?@
///			:			 Stop-60,   CONTROL-100)

//	          DAMAGE+    STOP+      CONTROL     SPEED       TELEPORT+      HEALTH+     SLOW      TRAMSFORM+     DRAIN





// #include "Base/UnitState/UnitParamComponent.h"

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Struct/UnitParamModifier.h"

#include "UnitParamComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OOO_API UUnitParamComponent : public UActorComponent
{
	GENERATED_BODY()




public:

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void Init();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		float GetParam(EUnitParam _Param);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void SetParam(EUnitParam _Param, float _Val);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ModParam(EUnitParam _Param, float _Val);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void ModParamModificator(EUnitParam _Param, float _Val);


public:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<FUnitParamModifier> UnitParam;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<FUnitParamModifier> ParamModificator;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")	int32 iHP = -1;			// ** Current-HP Original
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")	int32 iCritHP = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")	int32 iMinHP = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")	int32 iMaxHP = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")	int32 iRegHP = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")	int32 iPotentialHP = -1;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO")	int32 iSP = -1;





	


//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
//		FUnitParamModifier BaseHP;

//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
//		FUnitParamModifier RealHP;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
	//	FUnitParamModifier BaseCritMinHP;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
	//	FUnitParamModifier RealCritMinHP;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
	//	FUnitParamModifier BaseMinHP;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
	//	FUnitParamModifier RealMinHP;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
	//	FUnitParamModifier BaseMaxHP;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
	//	FUnitParamModifier RealMaxHP;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
	//	FUnitParamModifier BaseRegHP;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
	//	FUnitParamModifier RealRegHP;



	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
	//	FUnitParamModifier BaseSP;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
	//	FUnitParamModifier RealSP;



/*
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		FUnitParamModifier DDDDDDDDDDDDDD;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		FUnitParamModifier DDDDDDDDDDDDDD;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		FUnitParamModifier DDDDDDDDDDDDDD;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		FUnitParamModifier DDDDDDDDDDDDDD;
*/



public:	

/*
	int32 CurrentHP = 80;	

	int32 CriticalHP = 10;		// ** -10  (value lov then zero when Unit deadly but still alive)
	int32 CriticalHP_add = 0;

	int32 MinHP = 10;
	int32 MinHP_add = 0;

	int32 HP = 100;
	int32 HP_add = 0;
	

	int32 TotalWpnLevel = 1;
	int32 TotalWpnLevel_add = 0;

	int32 TotalGunLevel = 1;
	int32 TotalGunLevel_add = 0;

	int32 TotalMagikLevel = 1;
	int32 TotalMagikLevel_add = 0;

*/


public:	

	UUnitParamComponent();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	



};




