#pragma once

#include "BattleManiaEnum.generated.h"


UENUM(BlueprintType)
enum class ECardinalDirection : uint8 
{
	eNorth UMETA(DisplayName = "North"),
	eEast UMETA(DisplayName = "East"),
	eSouth UMETA(DisplayName = "South"),
	eWest UMETA(DisplayName = "West")
};


UENUM(BlueprintType)
enum class EStance : uint8
{
	eStanding UMETA(DisplayName = "Standing"),
	eCrouching UMETA(DisplayName = "Crouching")
};



UENUM(BlueprintType)
enum class ECameraMode : uint8
{
	eFirstPerson UMETA(DisplayName = "FirstPerson"),
	eThirdPerson UMETA(DisplayName = "ThirdPerson")
};


UENUM(BlueprintType)
enum class ERotationMode : uint8 
{
	eVelocityMode UMETA(DisplayName = "VelocityMode"),
	eLookingMode UMETA(DisplayName = "LookingMode")
};



UENUM(BlueprintType)
enum class EGaitMode : uint8
 {
	eNone UMETA(DisplayName = "None"),
	eWalking UMETA(DisplayName = "Walking"),
	eRunning UMETA(DisplayName = "Running"),
	eSprinting UMETA(DisplayName = "Sprinting")
};



UENUM(BlueprintType)
enum class ELocomotionMode : uint8 
{
	eNone UMETA(DisplayName = "None"),
	eGrounded UMETA(DisplayName = "Grounded"),
	eFalling UMETA(DisplayName = "Falling")
};



UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
	eNone UMETA(DisplayName = "None"),
	eNotMoving UMETA(DisplayName = "NotMoving"),
	eMoving UMETA(DisplayName = "Moving"),
	ePivot UMETA(DisplayName = "Pivot"),
	eStopping UMETA(DisplayName = "Stopping")
};



UENUM(BlueprintType)
enum class EIdleEntryState : uint8 
{
	eN_Idle UMETA(DisplayName = "N_Idle"),
	eLF_Idle UMETA(DisplayName = "LF_Idle"),
	eRF_Idle UMETA(DisplayName = "RF_Idle"),
	eCLF_Idle UMETA(DisplayName = "CLF_Idle"),
	eCRF_Idle UMETA(DisplayName = "CRF_Idle")
};



UENUM(BlueprintType)
enum class EMovementDirection : uint8
 {
	eForward UMETA(DisplayName = "Forward"),
	eBackward UMETA(DisplayName = "Backward")
};



UENUM(BlueprintType)
enum class EFootstepType : uint8
 {
	eStep UMETA(DisplayName = "Stepping"),
	eWalk UMETA(DisplayName = "Walking"),
	eRun UMETA(DisplayName = "Running"),
	eSprint UMETA(DisplayName = "Sprinting"),
	ePivot UMETA(DisplayName = "Pivoting"),
	eJump UMETA(DisplayName = "Jumping"),
	eLand UMETA(DisplayName = "Landing")
};

