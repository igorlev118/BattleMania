

#pragma once

#include "BattleMania.h"
#include "BattleManiaStruct.h"
#include "BattleManiaInterfaceABP.h"

#include <Animation/AnimInstance.h>
#include "BattleManiaAnimInstance.generated.h"


class ABattleManiaCharacter;
class UCapsuleComponent;
class UCharacterMovementComponent;


UCLASS()
class BATTLEMANIA_API UBattleManiaAnimInstance : public UAnimInstance, public IBattleManiaInterfaceABP 
{

	GENERATED_BODY()

public:
	UBattleManiaAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;


protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void DoWhileMoving();
	virtual void DoWhileMoving_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void DoWhileFalling();
	virtual void DoWhileFalling_Implementation();
 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void DoTurnInPlace();
	virtual void DoTurnInPlace_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void DoWhileRagdoll();
	virtual void DoWhileRagdoll_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void DoDelayedTurn(float MaxCameraSpeed,
		float YawLimit1, float Delay1, float PlayRate1, FTurnAnimations TurnAnims1,
		float YawLimit2, float Delay2, float PlayRate2, FTurnAnimations TurnAnims2);

	virtual void DoDelayedTurn_Implementation(float MaxCameraSpeed,
		float YawLimit1, float Delay1, float PlayRate1, FTurnAnimations TurnAnims1,
		float YawLimit2, float Delay2, float PlayRate2, FTurnAnimations TurnAnims2);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void DoResponsiveTurn(float YawLimit, float PlayRate, FTurnAnimations TurnAnims);
	virtual void DoResponsiveTurn_Implementation(float YawLimit, float PlayRate, FTurnAnimations TurnAnims);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void CalculateGaitValue();
	virtual void CalculateGaitValue_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void CalculatePlayRates(float Crouch, float Walk, float Run, float Sprint);
	virtual void CalculatePlayRates_Implementation(float Crouch, float Walk, float Run, float Sprint);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void CalculateMovementDirection(float ThresholdMin = -90.0f, float ThresholdMax = 90.0f, float Tolerance = 5.0f);
	virtual void CalculateMovementDirection_Implementation(float ThresholdMin = -90.0f, float ThresholdMax = 90.0f, float Tolerance = 5.0f);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void CalculateAimOffset();
	virtual void CalculateAimOffset_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void CalculatePivot();
	virtual void CalculatePivot_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void CalculateStartPosition();
	virtual void CalculateStartPosition_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void CalculateGroundedLeaningValues();
	virtual void CalculateGroundedLeaningValues_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void CalculateAirLeaningValues();
	virtual void CalculateAirLeaningValues_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void CalculateLandPredictionAlpha();
	virtual void CalculateLandPredictionAlpha_Implementation();


public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void Pivot_Notify(const FPivotParameters& Params);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void TurnInPlace_Notify(UAnimMontage* TurnAnim, bool bShouldTurn, bool bIsTurning, bool bRightTurn);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void IdleEntry_Notify(EIdleEntryState NewIdleState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void IdleTransition_Notify(UAnimSequenceBase* Animation, float PlayRate, float StartTime);

	/** Animation notify for entering locomotion state moving */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void AnimNotify_Entered_Moving();

	/** Animation notify for leaving locomotion state moving */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void AnimNotify_Left_Moving();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void AnimNotify_Entered_NotMoving();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void AnimNotify_Left_NotMoving();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void AnimNotify_Entered_Pivot();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void AnimNotify_Left_Pivot();

	/** Animation notify for entering locomotion state stopping */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void AnimNotify_Entered_Stopping();

	/** Animation notify for leaving locomotion state stopping */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void AnimNotify_Left_Stopping();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "BattleMania|Notifications")
	void AnimNotify_Land();


public:
	UFUNCTION(BlueprintCallable, Category = "BattleMania|ABP_Interface")
	void UpdateAnimationState();

	virtual void OnSetShowTraces_Implementation(bool bShow) { bShowTraces = bShow; };

	virtual void OnSetIsRagdoll_Implementation(bool bRagdoll) { bIsRagdoll = bRagdoll; };

	virtual void OnSetIsAiming_Implementation(bool bAiming) { bIsAiming = bAiming; };

	virtual void OnSetIsMoving_Implementation(bool bMoving) { bIsMoving = bMoving; };

	virtual void OnSetHasMovementInput_Implementation(bool bHasInput) { bHasMovementInput = bHasInput; };

	virtual void OnSetForwardFoot_Implementation(bool bRightFoot) { bRightFootForward = bRightFoot; };

	virtual void OnSetCrouchSpeed_Implementation(float NewSpeed) { CrouchSpeed = NewSpeed; };

	virtual void OnSetWalkSpeed_Implementation(float NewSpeed) { WalkSpeed = NewSpeed; };

	virtual void OnSetRunSpeed_Implementation(float NewSpeed) { RunSpeed = NewSpeed; };

	virtual void OnSetSprintSpeed_Implementation(float NewSpeed) { SprintSpeed = NewSpeed; };

	/** Called to update animation character velocity */
	virtual void OnSetCharacterVelocity_Implementation(FVector NewVelocity) { CharacterVelocity = NewVelocity; };


	/** Called to update animation camera view mode */
	virtual void OnSetCameraMode_Implementation(ECameraMode NewMode) { CameraMode = NewMode; };

	/** Called to update animation stance */
	virtual void OnSetStance_Implementation(EStance NewStance);

	/** Called to update animation rotation mode */
	virtual void OnSetRotationMode_Implementation(ERotationMode NewMode) { RotationMode = NewMode; };

	/** Called to update animation locomotion mode */
	virtual void OnSetLocomotionMode_Implementation(ELocomotionMode NewMode);

	virtual void OnSetGaitMode_Implementation(EGaitMode NewMode) { GaitMode = NewMode; };

	virtual void OnSetCharacterRotation_Implementation(FRotator NewRotation) { CharacterRotation = NewRotation; };

	virtual void OnSetLookRotation_Implementation(FRotator NewRotation) { LookRotation = NewRotation; };

	virtual void OnSetPrevVelocityRotation_Implementation(FRotator NewRotation) { PrevVelocityRotation = NewRotation; };

	virtual void OnSetPrevMovementRotation_Implementation(FRotator NewRotation) { PrevMovementRotation = NewRotation; };

	virtual void OnSetYawDifferential_Implementation(float NewValue) { YawDifferential = NewValue; };

	virtual void OnSetMovementDifferential_Implementation(float NewValue) { MovementDifferential = NewValue; };

	virtual void OnSetRotationDifferential_Implementation(float NewValue) { RotationDifferential = NewValue; };

	virtual void OnSetAimYawRate_Implementation(float NewValue) { AimYawRate = NewValue; };

	virtual void OnSetAimYawDelta_Implementation(float NewValue) { AimYawDelta = NewValue; };


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	FTurnAnimations N_Turn_90;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	FTurnAnimations N_Turn_180;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	FTurnAnimations LF_Turn_90;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	FTurnAnimations RF_Turn_90;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	FTurnAnimations CLF_Turn_90;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	FTurnAnimations CRF_Turn_90;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	UAnimMontage* GetUpBack;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	UAnimMontage* GetUpFront;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	UAnimSequenceBase* AdditiveLand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	UCurveFloat* FlailAlphaCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	UCurveFloat* LandAlphaCurve;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|AnimationAssets")
	UAnimMontage* ActiveTurningMontage; 


protected:
	////////////////////////////////////////////////////////////////////
	//
	//   Variables used within the animation blueprint
	//
	////////////////////////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	bool bIsRagdoll;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	bool bIsAiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	bool bIsMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	bool bHasMovementInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	bool bRightFootForward;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	EStance Stance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	ELocomotionMode LocomotionMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	float YawDifferential;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	float MovementDifferential;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	float RotationDifferential;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|AnimGraph|CharacterState")
	FVector CharacterVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|AnimGraph|InternalVariables")
	bool bShouldTurnInPlace;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|AnimGraph|InternalVariables")
	EIdleEntryState IdleEntryState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|AnimGraph|InternalVariables")
	ELocomotionMode PrevLocomotionMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|AnimGraph|InternalVariables")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|AnimGraph|InternalVariables")
	FVector2D AimOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|AnimGraph|InternalVariables")
	FVector2D FeetPosition;


protected:
	////////////////////////////////////////////////////////////////////
	//
	//   Animation blueprint state variables retrieved from character
	//
	////////////////////////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	ABattleManiaCharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	UCharacterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	bool bShowTraces;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	float CrouchSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	float WalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	float RunSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	float SprintSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	ECameraMode CameraMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	ERotationMode RotationMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	EGaitMode GaitMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	FRotator LookRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	FRotator CharacterRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	FRotator PrevMovementRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	FRotator PrevVelocityRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	float AimYawRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania|CharacterState")
	float AimYawDelta;


protected:
	////////////////////////////////////////////////////////////////////
	//
	//   Internal animation blueprint variables
	//
	////////////////////////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	ELocomotionState ActiveLocomotionState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	EMovementDirection MovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	bool bTurningInPlace;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	bool bTurningRight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float TurnInPlaceDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float GaitValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float PreviousSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float StartPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float N_PlayRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float C_PlayRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float FlailRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float FlailBlendAlpha;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float LandPredictionAlpha;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float LeanInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FVector2D LeanGrounded;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FRotator PrevVelocityRotationABP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FPivotParameters PivotParameters;
};
