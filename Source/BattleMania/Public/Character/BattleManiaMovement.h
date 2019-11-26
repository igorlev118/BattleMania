

#pragma once

#include "BattleMania.h"
#include "BattleManiaEnum.h"

#include <GameFramework/CharacterMovementComponent.h>
#include "BattleManiaMovement.generated.h"


class FNetworkPredictionData_Client;
class FNetworkPredictionData_Server;

 
UCLASS()
class BATTLEMANIA_API UBattleManiaMovement : public UCharacterMovementComponent
{

	GENERATED_BODY()

	friend class FSavedMove_BattleManiaCharacter;

public:
	UBattleManiaMovement(const FObjectInitializer& ObjectInitializer);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	virtual FNetworkPredictionData_Server* GetPredictionData_Server() const override;

	virtual FVector ConsumeInputVector() override;

	virtual float GetMaxSpeed() const override;
	
	virtual float GetMaxAcceleration() const override;
	
	virtual float GetMaxBrakingDeceleration() const override;

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	bool IsRunning() const { return bWantsToRun; }

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	bool IsSprinting() const { return bWantsToSprint; }

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	bool IsAiming() const { return bWantsToAim; }

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	FVector GetMovementInput() const { return MovementInput; }
	
	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	FRotator GetControlRotation() const { return ControlRotation; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetCrouchSpeed() const { return CrouchSpeed; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetWalkSpeed() const { return WalkSpeed; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetRunSpeed() const { return RunSpeed; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetSprintSpeed() const { return SprintSpeed; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetWalkAcceleration() const { return WalkAcceleration; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetRunAcceleration() const { return RunAcceleration; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetWalkDeceleration() const { return WalkDeceleration; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetRunDeceleration() const { return RunDeceleration; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetWalkGroundFriction() const { return WalkGroundFriction; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetRunGroundFriction() const { return RunGroundFriction; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetGroundSpeed() const;

	// Get character crouched speed based on state
	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetCrouchedSpeed() const;
	
	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	float GetGroundFriction() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	EStance GetStance() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	EGaitMode GetGaitMode() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	ELocomotionMode GetLocomotionMode() const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	ELocomotionMode ConvertMovementMode(EMovementMode Mode) const;

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	ERotationMode GetRotationMode() const { return RotationMode; };


public:
	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void WantsToRun(bool bRunning) { bWantsToRun = bRunning; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void WantsToSprint(bool bSprinting) { bWantsToSprint = bSprinting; };

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void WantsToAim(bool bAiming) { bWantsToAim = bAiming; };

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetCrouchSpeed(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetCrouchSpeed(float NewValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetWalkSpeed(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetWalkSpeed(float NewValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetRunSpeed(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetRunSpeed(float NewValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetSprintSpeed(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetSprintSpeed(float NewValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetWalkAcceleration(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetWalkAcceleration(float NewValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetRunAcceleration(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetRunAcceleration(float NewValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetWalkDeceleration(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetWalkDeceleration(float NewValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetRunDeceleration(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetRunDeceleration(float NewValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetWalkGroundFriction(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetWalkGroundFriction(float NewValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetRunGroundFriction(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetRunGroundFriction(float NewValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetRotationMode(ERotationMode NewMode);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetRotationMode(ERotationMode NewMode);

	UFUNCTION(BlueprintCallable, Category = "BattleMania")
	void SetCustomAcceleration();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float BaseTurnRate;


protected:
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetInputVector(const FVector& Input);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetControlRotation();


protected:
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float CrouchSpeed;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float WalkSpeed;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float RunSpeed;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float SprintSpeed;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float WalkAcceleration;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float RunAcceleration;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float WalkDeceleration;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float RunDeceleration;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float WalkGroundFriction;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterMovement: BattleMania")
	float RunGroundFriction;


protected:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "CharacterMovement: BattleMania|Internal")
	FVector_NetQuantize100 MovementInput;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "CharacterMovement: BattleMania|Internal")
	FRotator ControlRotation;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "CharacterMovement: BattleMania|Internal")
	ERotationMode RotationMode;

private:
	UPROPERTY(Replicated)
	uint8 bWantsToRun : 1;

	UPROPERTY(Replicated)
	uint8 bWantsToSprint : 1;

	UPROPERTY(Replicated)
	uint8 bWantsToAim : 1;

};

class FSavedMove_BattleManiaCharacter : public FSavedMove_Character
{

public:

	typedef FSavedMove_Character Super;

	/** Resets all saved variables */
	virtual void Clear() override;

	/** Store input commands in the compressed flags */
	virtual uint8 GetCompressedFlags() const override;

	/** This is used to check whether or not two moves can be combined into one
	    Basically you just check to make sure that the saved variables are the same */
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;

	/** Sets up the move before sending it to the server */
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
	
	/** Sets variables on character movement component before making a predictive correction */
	virtual void PrepMoveFor(class ACharacter* Character) override;

	uint8 bSavedWantsToRun : 1;
	uint8 bSavedWantsToSprint : 1;
	uint8 bSavedWantsToAim : 1;
};



class FNetworkPredictionData_Client_BattleManiaCharacter : public FNetworkPredictionData_Client_Character 
{
public:

	typedef FNetworkPredictionData_Client_Character Super;

	FNetworkPredictionData_Client_BattleManiaCharacter(const UCharacterMovementComponent& ClientMovement);

	virtual FSavedMovePtr AllocateNewMove() override;
};



class FNetworkPredictionData_Server_BattleManiaCharacter : public FNetworkPredictionData_Server_Character
 {
public:
	typedef FNetworkPredictionData_Server_Character Super;

	FNetworkPredictionData_Server_BattleManiaCharacter(const UCharacterMovementComponent& ServerMovement);
};

