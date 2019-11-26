

#pragma once

#include "BattleMania.h"
#include "BattleManiaInterfaceABPIK.h"

#include <Animation/AnimInstance.h>
#include "BattleManiaAnimInstanceIK.generated.h"

class ABattleManiaCharacter;

UCLASS()
class BATTLEMANIA_API UBattleManiaAnimInstanceIK : public UAnimInstance, public IBattleManiaInterfaceABPIK {

	GENERATED_BODY()

public:
	
	/** Setup default properties */
	UBattleManiaAnimInstanceIK();
	
	/** Called at start of play */
	virtual void NativeInitializeAnimation() override;

	/** Called every frame */
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;


protected:
	////////////////////////////////////////////////////////////////////
	//
	//   Inverse kinematic functions, can be overriden in blueprint or C++
	//
	////////////////////////////////////////////////////////////////////
	
	/** Handles IK for normal modes */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void FootIK();
	virtual void FootIK_Implementation();

	/** Handles IK when ragdolling */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|Animation")
	void RagdollIK();
	virtual void RagdollIK_Implementation();


public:
	////////////////////////////////////////////////////////////////////
	//
	//   Interface functions to needed character variables
	//
	////////////////////////////////////////////////////////////////////

	/** Calls all interface functions to synchronize animation state with character*/
	UFUNCTION(BlueprintCallable, Category = "BattleMania|ABPIK_Interface")
	void UpdateAnimationState();

	/** Called to update animation debug traces state */
	virtual void OnSetShowTraces_Implementation(bool bShow) { bShowTraces = bShow; };

	/** Called to update animation debug traces state */
	virtual void OnSetIsRagdoll_Implementation(bool bRagdoll) { bIsRagdoll = bRagdoll; };

	/** Called to update animation stance */
	virtual void OnSetStance_Implementation(EStance NewStance) { Stance = NewStance; };

	/** Called to update animation locomotion mode */
	virtual void OnSetLocomotionMode_Implementation(ELocomotionMode NewMode) { LocomotionMode = NewMode; };


protected:
	////////////////////////////////////////////////////////////////////
	//
	//   User variables
	//
	////////////////////////////////////////////////////////////////////
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania")
	ABattleManiaCharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania")
	FName LeftFootBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania")
	FName RightFootBoneName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania")
	float FootIKAlpha;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania")
	float RotationInterpolationSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania")
	float Z_InterpolationSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|Linetrace")
	float TraceHeightAboveFoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|Linetrace")
	float TraceHeightBelowFoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|Limits")
	FVector StandingMinLimits;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|Limits")
	FVector StandingMaxLimits;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|Limits")
	FVector CrouchingMinLimits;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BattleMania|Limits")
	FVector CrouchingMaxLimits;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|CharacterState")
	bool bShowTraces;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|CharacterState")
	bool bIsRagdoll;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|CharacterState")
	EStance Stance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|CharacterState")
	ELocomotionMode LocomotionMode;


protected:
	////////////////////////////////////////////////////////////////////
	//
	//   Internal animation blueprint variables
	//
	////////////////////////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	bool bEnableFootIK;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float PelvisOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FVector LeftFootOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FVector RightFootOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FTransform LeftFootTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FTransform RightFootTransform;

};
