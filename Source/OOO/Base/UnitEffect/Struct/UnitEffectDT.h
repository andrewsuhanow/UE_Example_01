
// #include "Base/UnitEffect/Struct/UnitEffectDT.h"

#pragma once

#include "../../UnitState/Struct/UnitParamModifier.h"

//-----#include "../Enum/UnitEffectType.h"

#include "UnitEffectDT.generated.h"

//#define SLOT_IS_EMPTY FName("SLOT_IS_EMPTY");

USTRUCT(Blueprintable, BlueprintType)
struct FUnitEffectDT
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()


public:
	
//	UPROPERTY()
//		int32 IndexInUnit = -1;

	UPROPERTY()
		class AUnit* UnitOwner = nullptr;

//	bool Init(class AUnit* _UnitOwner);

	
//	void ActivateUpdate();
//	FTimerDelegate UpdateDelegate;
//	FTimerHandle TH_Update;
//	void Update();

//	void Finish();

//	void Cancel();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		UTexture2D* EffectImage = nullptr;

	// ** Effect type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO" )
		TSubclassOf<class UUnitEffectRealizer> UnitEffectRealizer;




	 
#if WITH_EDITORONLY_DATA  // #if WITH_EDITOR 

	// ** Desctiption Editor-only: 
	void SetDescriptionText();
	// ** PAREMETER REQUIRE fot this UnitEffect
	UPROPERTY(VisibleAnywhere, Category = "OOO", DisplayName = "**HELPER__UnitEffectParamDescription")
		TArray<FString> HELPER__UnitEffectParamDescription;
	// ** check if "UnitEffectRealizer" changed in editor
	UPROPERTY()
		TSubclassOf<class UUnitEffectRealizer> LastUnitEffectRealizer_EDITTOR;
#endif


	

	



//---	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO ")
//----		EUnitEffectType UnitEffectType = EUnitEffectType::none;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		bool IsUnitEffectCanBeCanel = false;

	// ** It can generate a chaine reaction 
	// ** (AbilityEffect will born a new "TraseReselector" and again and again)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!")
		TArray<int32> GenertateNewTraseReselectorIndex;

	// ------------------------------------------------------------------------------


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO" )
		TArray<FUnitParamModifier> UnitParamModifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		TArray<FVector> Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		TArray<FRotator> Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		TArray<class AUnit*> Unit;
	//+++UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		//+++TArray<class AObject> Object;
	//+++UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		//+++TArray<class AItem> Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		TArray<float> Float;	// ** SphereSize, DurationTime
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		TArray<UStaticMesh*> StMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		TArray<USkeletalMesh*> SkMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		TArray< TSubclassOf< class AUnit> > Unit_class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		TArray<class UNiagaraSystem*> VisualEffect;
	// ** NAME_None
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
		TArray<FName> VisualEffectSocket;	

	//+++UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
	//+++	TArray<USound> Sound;








	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO " )
	//	TArray<> fff;


	FUnitEffectDT& operator=(const FUnitEffectDT& _Other);
	
};