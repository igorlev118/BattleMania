

#pragma once

#include "BattleMania.h"
#include "BattleManiaEnum.h"
#include "BattleManiaStruct.h"
#include "BattleManiaMovement.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"

#include <GameFramework/Character.h>
#include <Components/TimelineComponent.h>
#include "BattleManiaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UTimelineComponent;
class UPlayerInfoWidget;
class UHealthComponent;
class UPointOfInterest;

 
UCLASS()
class BATTLEMANIA_API ABattleManiaCharacter : public ACharacter, public IAbilitySystemInterface
{

	GENERATED_BODY()

public:
	ABattleManiaCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;


private:
	virtual void OnStartCrouch(float HHAdjust, float SHHAdjust) override;

	virtual void OnEndCrouch(float HHAdjust, float SHHAdjust) override;

	virtual void Landed(const FHitResult& Hit) override;

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PrevCustomMode) override;


private:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void JumpAction();

	void StanceAction();

	void WalkAction();

	void BeginSprint();

	void EndSprint();

	void BeginAiming();

	void EndAiming();

	void SwitchRotationMode();

	void RagdollAction();

	void SwitchForwardFoot();

	void BeginSwitchCamera();

	void EndSwitchCamera();

	void SwitchCamera();


public:
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	FCameraSettings GetCameraTargetSettings() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	FVector GetCharacterVelocity() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetCharacterRotationRate(float SlowSpeed, float SlowRate, float FastSpeed, float FastRate);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	bool IsAiming() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	bool IsSprinting() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	EStance GetStance() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	EGaitMode GetGaitMode() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	ERotationMode GetRotationMode() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	ELocomotionMode GetLocomotionMode() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetCrouchingSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetWalkingSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetRunningSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetSprintingSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetWalkAcceleration() const;
	
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetRunAcceleration() const;
	
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetWalkDeceleration() const;
	
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetRunDeceleration() const;
	
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetWalkGroundFriction() const;
	
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Getters")
	float GetRunGroundFriction() const;


public:
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetCharacterRotation(FRotator NewRotation, bool bDoInterp, float InterpSpeed);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void AddCharacterRotation(FRotator AdditiveRotation);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void LimitCharacterRotation(float AimYawLimit, float InterpSpeed);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetCameraMode(ECameraMode NewMode);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetCameraGaitMode(float Speed);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetRightShoulder(bool bRight);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetAiming(bool bAiming);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetRotationMode(ERotationMode NewMode);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetLocomotionMode(ELocomotionMode NewMode);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetCrouchSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetWalkSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetRunSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetSprintSpeed(float NewSpeed);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "BattleMania|Character|Server")
	void ServerSetShowSettings(bool bShow);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetShowSettings(bool bShow);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "BattleMania|Character|Server")
	void ServerSetShowTraces(bool bShow);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "BattleMania|Character|Server")
	void ServerSetForwardFoot(bool bRightFoot);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetForwardFoot(bool bRightFoot);
	

public:
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Utility")
	void CameraLerpCallback(float Alpha);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Utility")
	void UpdateCapsuleVisibility();

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Setters")
	void SetShowTraces(bool bShow);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Utility")
	void PrintCharacterInfo();

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Utility")
	void UpdateCamera(UCurveFloat* LerpCurve);

	void CreateArrowComponents();

	void UpdateArrowPositions();

	void UpdateArrowComponents(bool bAlwaysUpdate = false);


public:
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Utility")
	void ManageCharacterRotation();


	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Utility")
	void CalculateStateVariables();

	/** Determines the looking yaw offset */
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Utility")
	FRotator CalculateLookingDirection(float NEAngle, float NWAngle, float SEAngle, float SWAngle, float Buffer, float InterpSpeed);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Utility")
	float WithinCardinalRange(float Value, float Min, float Max, float Tol, ECardinalDirection Cardinal);

	/** Handle animNotify turn in place event */
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Utility")
	void DelayedRotation_Notify(FRotator AdditiveRotation, float DelayTime);

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Utility")
	void CameraShake_Notify(TSubclassOf<UCameraShake> ShakeClass, float ShakeScale);


public:
	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Ragdoll")
	void ManageRagdoll();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "BattleMania|Character|Server")
	void MulticastRagdollUpdate(bool bGrounded, FVector DollLocation, FVector NewLocation, FRotator NewRotation);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "BattleMania|Character|Server")
	void ServerRagdollUpdate(bool bGrounded, FVector DollLocation, FVector NewLocation, FRotator NewRotation);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "BattleMania|Character|Server")
	void MulticastEnterRagdoll();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "BattleMania|Character|Server")
	void ServerEnterRagdoll();

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Ragdoll")
	void EnterRagdoll();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "BattleMania|Character|Server")
	void MulticastExitRagdoll();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "BattleMania|Character|Server")
	void ServerExitRagdoll();

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Ragdoll")
	void ExitRagdoll();

	UFUNCTION(BlueprintCallable, Category = "BattleMania|Character|Ragdoll")
	bool RagdollLineTrace(FVector InLocation, FRotator InRotation, FVector& OutLocation, FRotator& OutRotation);


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania")
	FName FPCameraSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania")
	FName PelvisBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BattleMania")
	FName RagdollPoseName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BattleMania")
	float HalfHeight = 90.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BattleMania")
	float CrouchedHalfHeight = 60.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BattleMania")
	bool bToggleSprint;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "BattleMania")
	bool bRightFootForward;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "BattleMania|Debug")
	bool bShowSettings;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "BattleMania|Debug")
	bool bShowTraces;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BattleMania|Camera")
	bool bRightShoulder;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BattleMania|Camera")
	ECameraMode CameraMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BattleMania|Camera")
	FCameraTargetSettings CameraTargets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BattleMania|Camera")
	TArray<UCurveFloat*> CameraLerpCurves;


public:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	bool bRagdollGrounded;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	bool bIsMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	bool bHasMovementInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	bool bIsRagdoll;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	ECardinalDirection CardinalDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	ELocomotionMode PrevLocomotionMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	EGaitMode CameraGaitMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float AimYawDelta;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float AimYawRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float MovementDifferential;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float RotationDifferential;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float YawDifferential;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float RotationOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	float RotationRateMultiplier;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FVector MovementInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FVector RagdollLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FRotator CharacterRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FRotator LookRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FRotator TargetRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FRotator JumpRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FRotator PrevVelocityRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BattleMania|InternalVariables")
	FRotator PrevMovementRotation;

	UPROPERTY()
	FCameraSettings CurrentCameraSettings;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* TP_SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* TP_Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* FP_Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Arrows;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* LookingRotationArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* TargetRotationArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* CharacterRotationArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* MovementInputArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* PrevMovementInputArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* VelocityArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* PrevVelocityArrow;

	UPROPERTY(BlueprintReadWrite)
	UPlayerInfoWidget* PlayerInfoWidget;


private:
	FTimerHandle InputTimer;

	FOnTimelineFloat onCameraLerpCallback;

	UPROPERTY()
	UTimelineComponent* CameraLerpTimeline;

	TWeakObjectPtr<class UBattleManiaAbilitySystemComponent> AbilitySystemComponent;

public:

	FORCEINLINE UBattleManiaMovement* GetBattleManiaMovement() const { return Cast<UBattleManiaMovement>(GetCharacterMovement()); };

public:
	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};

