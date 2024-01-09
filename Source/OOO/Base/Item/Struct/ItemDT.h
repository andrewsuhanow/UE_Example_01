
// #include "Base/Item/Struct/ItemDT.h"

#pragma once

#include "Engine/DataTable.h"

#include "../../Inventory/Enum/SlotType.h"

//#include "../ArmorData.h"
//#include "../WeaponData.h"
//#include "../UseItemData.h"

#include "ItemDT.generated.h"

//#define SLOT_IS_EMPTY FName("SLOT_IS_EMPTY");

USTRUCT(Blueprintable, BlueprintType)
struct FItemDT : public FTableRowBase //  FTableRowBase - make avaulable in DataTable
{
	GENERATED_USTRUCT_BODY()
		//GENERATED_BODY()



	FItemDT() {};
	FItemDT(const FItemDT& Other);


	FItemDT& operator=(const FItemDT& Other);
	friend bool operator==(const FItemDT& Self, const FItemDT& Other);
	

	
																	void SetSlotEmpty();	// ** 
																	bool IsSlotEmpty() const;	// ** is Empty slot

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	FName GameName = FName("none");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	FString Description = FString("no description");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	UTexture2D* ItemImage;
																	UTexture2D* GetFullImage() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	UTexture2D* ItemOneCellImage;
																	UTexture2D* GetOneSlotImage() const;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		// Soft Mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	bool IsStackable = false;
																	bool IsItemStackable() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	int32 Count = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	int32 CountMax = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	float HealthMax = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	float Health = 0.f;

	// ** if UWeapon or UArmour: this value multiply that damage or defence 
	// ** if UseItem: multiply effect Power

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	float ValueKoef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	float Cost = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	float Waight = 0.f;




	// ** Weapon-Type:   "Sword, LongSword, Bow, Base-Fight, Locomotion"        (((((for equip weapon)))))
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
//		EWeapon_Type Weapon_Type = EWeapon_Type::Locomotion;
//		EWeapon_Type GetAmunitionType() const;


	// ** Equip-Panel, FAST-Panel, Inventory, Perk-Panel:Cup/Armor/Clothes/...
	// ** Slot where item can be kip
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	TArray<ESlotType> AllowInventorySlotType
									= { ESlotType::global_inv, ESlotType::main_inv, ESlotType::fast_panel};


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	int32 InventorySizeX = 1;
																	int32 GetItemHorizontalSize() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")	int32 InventorySizeY = 1;
																	int32 GetItemVerticalSize() const;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Set_Param_OOO")		UObject* MeshPrimitive = nullptr;
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Set_Param_OOO")		TSubclassOf<class UWeaponDT> WeaponDT;
																				bool IsItemWeapon() const; 		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Set_Param_OOO")		TSubclassOf<class UArmorDT> ArmorDT;
																				bool IsItemArmor() const;

//++++	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Set_Param_OOO")		TSubclassOf<class UItem_UseableClass> UseableClass;
//+++


//++	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Set_Param_OOO")
//++	//	TSubclassOf<class UAbilityDataAsset> Ability_BP;						//  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
	 
	// Param  Health
	// value  -20
	// duration/Time/Permanent  5
	
	
	 
};