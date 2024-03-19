
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "../Controller/Task/Struct/TaskData.h"		// ** Unit->SetUnitTask()
#include "../Controller/Enum/TargetType.h"

#include "Enum/TurnBaseGameState.h"

#include "Spectator.generated.h"

UCLASS()
class OOO_API ASpectator : public APawn
{
	GENERATED_BODY()

public:

	ASpectator();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO")
		USceneComponent* root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		class UCameraComponent* Camera;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		class ABaseGameMode* GameMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		class ABaseGameState* GameState;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		class ABaseHUD* HUD;

	UFUNCTION()		void SetDefaultGameParam(class ABaseGameMode* _GameMode,
		class ABaseHUD* _HUD, class ABaseGameState* _GameState);


	// ****************************    Set_In_Editor    ****************************
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "OOO!")				float FreeCameraSpeed = 0.5f;
	



	// ----------------------------    *********    ----------------------------
public:

//---777---	UPROPERTY()															int32 iFastPanelButtonActicated = -1;
	UPROPERTY()																	TArray<AUnit*> CollectionTargetUnits;
	UPROPERTY()																	TArray<FVector> CollectionTargetPoints;

	UPROPERTY()																	bool IsSelectionRectangleDrawing = false;
	UPROPERTY()																	bool IsActivateButton_Select_WayPoint = false;			// ** Way-Point    (Select Button Clicked)
	UPROPERTY()																	bool IsActivateButton_Add_WayPoint = false;				// ** Way-Point    (Add Button Clicked)

	// ** Check Up-high position
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OOO_Base_Param")	float CurrentCameraProectionPoint = 0.f;

	// ** Screen
	UPROPERTY()																	int32 ViewportSize_X;
	UPROPERTY()																	int32 ViewportSize_Y;

	// ** Mouse press
	UPROPERTY()																	FVector MouseLocationPos_Click_L;			// ** Lost Mouse Clicking 3D
	UPROPERTY()																	FVector2D MousePos2D_Click_L;				// ** Lost Mouse Clicking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO_Input")		FVector2D MouseDeltaPos = FVector2D(0, 0);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO_Input")		FVector2D R_LustMouseClickPos = FVector2D(0, 0);	// ** Lost Mouse Clicking (Right)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO_Input")		FVector2D L_LustMouseClickPos = FVector2D(0, 0);	// ** Lost Mouse Clicking (Left)

	// ** Mouse press
	UPROPERTY()																	float RightMouseClick_CheckTime;	// ** Check Mouse--R--HOLDING
	UPROPERTY()																	float LeftMouseClick_CheckTime;		// ** Check Mouse--L--HOLDING
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO_Input")		bool Mouse_R_Click = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO_Input")		bool Mouse_L_Click = false;

	UPROPERTY()																	float MouseStopHoldingTime = 1.f;		// ** time mouse holding on const position (Context param/meny)
	UPROPERTY()																	bool IsMouseWaitingContextActive = false;// ** is mouse holding on const position (Context param/meny)
	





	
	// ****************************    Unit_Operation    ****************************









	// ****************************    Move_Rotate    ****************************
public:


	// ** Move
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void MoveForward(float val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void MoveRight(float val);


	// ** Rotate / Cursor-move
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void CursorMoveX(float val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void CursorMoveY(float val);
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void StopCursorMove();
	

	// ** Scrool Whell (Zoom)
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void ScrollZoom(float val);




	// ****************************    Mouse_Press    ****************************
public:

	// ** Press mouse
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Mouse_L_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Mouse_L_Release();

	UPROPERTY()																	FTimerHandle TH_LeftMouseClick;			// ** Check Mouse--L--HOLDING
	UFUNCTION()																	void LeftMouseClick_Handle();			// ** Check Mouse--L--HOLDING

	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Mouse_R_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Mouse_R_Release();
	UPROPERTY()																	FTimerHandle TH_RightMouseClick;		// ** Check Mouse--R--HOLDING
	UFUNCTION()																	void RightMouseClick_Handle();			// ** Check Mouse--R--HOLDING


	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Mouse_M_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Mouse_M_Release();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO_Input")		bool Mouse_M_Click = false;


	// ****************************    Ray_Cast    ****************************
public:


	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void L_MousePress_ReyCast();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void R_MousePress_ReyCast();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void L_MouseRelase_ReyCast();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void R_MouseRelase_ReyCast();

	UFUNCTION()																	void MouseStopHolding_ReyCast();	// ** time when mouse on const position (Context param/meny)

	UPROPERTY()																	FHitResult LineTraceHit;
	UPROPERTY()																	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesQuery; 


	// ****************************    Key_1    ****************************
public:


	// ** Press Keyboard
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Shift_Left_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Shift_Left_Release();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO_Input")		bool bShift_Left = false;

	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void TAB_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void TAB_Release();

	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Enter_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Enter_Release();

	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Space_Press();
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Space_Release();



	// ****************************    Key_2    ****************************
public:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OOO_Input")		bool bSpaceBar = false;

	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_0_Press();		// ** Posses
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_Q_Press();		// ** 777777
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_E_Press();		// ** 777777
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_F_Press();		// ** 777777
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_G_Press();		// ** 777777
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_Z_Press();		// ** 777777
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_X_Press();		// ** 777777
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_C_Press();		// ** 777777
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_V_Press();		// ** 777777
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_R_Press();		// ** 777777
	UFUNCTION(Blueprintcallable, Category = "OOO_Input")						void Key_T_Press();		// ** 777777
	




	// ****************************    Input    ****************************
public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};





/*


// ***********************************************************************************************************
// ********************************************     Select     ***********************************************

public:

	UFUNCTION(BlueprintCallable, Category = "OOO_Select")
		bool SelectingUnit(class ABaseUnit* _Unit, bool _DoSelect = true);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class ABaseUnit*> SelectGroup;


public:

	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_Selection")
		void AddToSelectUnit(ABaseUnit* _Unit);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_Selection")
		void DeselectOneUnit(ABaseUnit* _Unit);
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_Selection")
		void DeselectAllUnits();



// ***********************************************************************************************************
// ***************************************     Helper_Function     *******************************************

	// ** Set-Select-Attack
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_Selection_Weapon")
		void SetSelectAttack_inCurrWeapon(int32 _AttackIndex);
	// ** Set-Select-Permanent-Attack
	UFUNCTION(Blueprintcallable, Category = "OOO_Unit_Selection_Weapon")
		void SetPermanentSelectAttack_inCurrWeapon(int32 _AttackIndex);
	// ** Try Deselected UI  "Attack button"
	UFUNCTION(Blueprintcallable)
		void Update_ActionButton_UI();
	// ** update Task-Icon-Panel-UI
	UFUNCTION(Blueprintcallable)
		void Update_TaskPanel_UI();

	// ** Way-Point-Actor   (Button  Daily-Behavior)
	UFUNCTION(Blueprintcallable)
		void SpawnNew_WayPointActor();
	UFUNCTION(Blueprintcallable)
		void Select_WayPointActor();



// ***********************************************************************************************************
// ****************************************     Draw_Selection     *******************************************

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "OOO")
		TArray<class AUnitSelector*> SelectorArray;

	// ** Arrow-Actor (Draw when player set his "Group-unin" stand direction)
	UPROPERTY(EditAnywhere, Category = "OOO_SetBP_Helper")
		TSubclassOf<class APositionDirrectionArrow> DirrectionArrow_Class;
	UPROPERTY()
		class APositionDirrectionArrow* DirrectionArrow;
	UPROPERTY()
		bool IsDirrectionArrowDrawing = false;



*/