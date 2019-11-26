

#pragma once

#include "BattleMania.h"
#include "BattleManiaEnum.h"
#include "UObject/Interface.h"
#include "BattleManiaInterfaceABP.generated.h"


UINTERFACE(MinimalAPI)
class UBattleManiaInterfaceABP : public UInterface 
{

	GENERATED_BODY()
};



class BATTLEMANIA_API IBattleManiaInterfaceABP 
{

	GENERATED_BODY()

public: 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetShowTraces(bool bShow);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetIsRagdoll(bool bRagdoll);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetIsAiming(bool bAiming);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetIsMoving(bool bMoving);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetHasMovementInput(bool bHasInput);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetForwardFoot(bool bRightFoot);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetCrouchSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetWalkSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetRunSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetSprintSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetCharacterVelocity(FVector NewVelocity);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetCameraMode(ECameraMode NewMode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetStance(EStance NewStance);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetRotationMode(ERotationMode NewMode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetLocomotionMode(ELocomotionMode NewMode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetGaitMode(EGaitMode NewMode);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetCharacterRotation(FRotator NewRotation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetLookRotation(FRotator NewRotation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetPrevVelocityRotation(FRotator NewRotation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetPrevMovementRotation(FRotator NewRotation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetYawDifferential(float NewValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetMovementDifferential(float NewValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetRotationDifferential(float NewValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetAimYawRate(float NewValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BattleMania|ABP_Interface")
	void OnSetAimYawDelta(float NewValue);
};

