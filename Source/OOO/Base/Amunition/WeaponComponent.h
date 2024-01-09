
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Item/Struct/ItemDT.h"
#include "Enum/WeaponType.h"

#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OOO_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	UWeaponComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	

	UPROPERTY(BlueprintReadOnly, Category = "OOO")
		class AUnit* UnitOwner;

public:	

	///UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Existing weapon", Category = "OOO!_Weapon")
	// ** REQUIRE to:  (WeaponDT, OneItemImage)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		FItemDT HandFightData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO!_Unit_Parameter")
		TArray<TSubclassOf<class AWeaponWorldItem>> Weapon_class;

public:	

	// ** Weapon class object
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")		
		TArray<class AWeaponWorldItem*> WeaponSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		int32 SelectedWeaponSlot = -1;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool SetWeaponSlotSelected(int32 _WeaponSlotIndex);

	//UFUNCTION(BlueprintCallable, Category = "OOO")
	//	int32 GetWeaponSlotSelected();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		bool iWeaponActive = false;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool IsWeaponActive();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		int32 GetSelectedWeaponSlotIndex();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void GetSelectedWeaponAttacksData(TArray<UTexture2D*> &_attackImage,
			int32 &_SelectIndex, int32 &_PermanentIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		EWeaponType GetWeaponTypeBySlotIndex(int32 _SlotIndex) const;

	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool ActivateWeapon();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool UnactivateWeapon();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		//-------FItemDT* GetCurrWeaponData();
		AWeaponWorldItem* GetCurrWeaponItem();

	UFUNCTION(BlueprintCallable, Category = "OOO")
		EWeaponType GetCurrentWeaponType();

public:

	UFUNCTION(BlueprintCallable)
		void InitWeapons(class AUnit* _UnitOwner);

	bool EquipWeaponByItemDT(const FItemDT* _ItemDT);


	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool IsEquipPanelSlotEmpty(int32 SlotIndex);

	///UFUNCTION(BlueprintCallable, Category = "OOO")
	FItemDT* GetItemRefFromEquipPanel(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "OOO")
		void RemoveItemFromEquipPanel(int32 SlotIndex);
	
// ---------------------------------------------------------------------

	// ** Weapons-slots-List Data (index, WpnType, Texture) for W_Weapon_Chenger_Panel
	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool GetWeaponSlotsListData(//)
			TArray<int32> &_WeaponSlotsIndex,
			TArray<ESlotType> &_WeaponSlotsType,
			TArray<UTexture2D*> &_WeaponSlotsTexture);

	// ** Current Weapons-slot Data (index, WpnType, Texture) for W_Weapon_Chenger_Panel
	UFUNCTION(BlueprintCallable, Category = "OOO")
		bool GetCurrentWeaponSlotData(//)
			int32& _WeaponSlotsIndex,
			ESlotType& _WeaponSlotsType,
			UTexture2D*& _WeaponSlotsTexture);
};
