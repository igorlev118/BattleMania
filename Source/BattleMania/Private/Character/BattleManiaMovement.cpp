#include "BattleManiaMovement.h"
#include <GameFramework/Character.h>
#include <UnrealNetwork.h>



UBattleManiaMovement::UBattleManiaMovement(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) 
{
	PrimaryComponentTick.bCanEverTick = true;
	bReplicates = true;

	BaseTurnRate = 150.0f;
	BaseLookUpRate = 150.0f;
	CrouchSpeed = 150.0f;
	WalkSpeed = 165.0;
	RunSpeed = 380.0f;
	SprintSpeed = 650.0f;
	WalkAcceleration = 800.0f;
	RunAcceleration = 1000.0f;
	WalkDeceleration = 800.0f;
	RunDeceleration = 800.0f;
	WalkGroundFriction = 8.0f;
	RunGroundFriction = 6.0f;
	RotationMode = ERotationMode::eLookingMode;

}

void UBattleManiaMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PawnOwner && PawnOwner->IsLocallyControlled()) 
	{
		ServerSetControlRotation();
	}

	MaxWalkSpeedCrouched = GetCrouchedSpeed();
	GroundFriction = GetGroundFriction();

	if (IsMovingOnGround() && !IsCrouching()) 
	{
		if (IsRunning() || IsSprinting()) 
		{
			SetCustomAcceleration();
		}
	}
}


void UBattleManiaMovement::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
 {
	DOREPLIFETIME(UBattleManiaMovement, bWantsToRun);
	DOREPLIFETIME(UBattleManiaMovement, bWantsToSprint);
	DOREPLIFETIME(UBattleManiaMovement, bWantsToAim);
	DOREPLIFETIME(UBattleManiaMovement, MovementInput);
	DOREPLIFETIME(UBattleManiaMovement, ControlRotation);
	DOREPLIFETIME(UBattleManiaMovement, CrouchSpeed);
	DOREPLIFETIME(UBattleManiaMovement, WalkSpeed);
	DOREPLIFETIME(UBattleManiaMovement, RunSpeed);
	DOREPLIFETIME(UBattleManiaMovement, SprintSpeed);
	DOREPLIFETIME(UBattleManiaMovement, WalkAcceleration);
	DOREPLIFETIME(UBattleManiaMovement, RunAcceleration);
	DOREPLIFETIME(UBattleManiaMovement, WalkDeceleration);
	DOREPLIFETIME(UBattleManiaMovement, RunDeceleration);
	DOREPLIFETIME(UBattleManiaMovement, WalkGroundFriction);
	DOREPLIFETIME(UBattleManiaMovement, RunGroundFriction);
	DOREPLIFETIME(UBattleManiaMovement, RotationMode);
}


void UBattleManiaMovement::UpdateFromCompressedFlags(uint8 Flags) 
{
	Super::UpdateFromCompressedFlags(Flags);

	bWantsToRun = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;
	bWantsToSprint = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
	bWantsToAim = (Flags & FSavedMove_Character::FLAG_Custom_2) != 0;
}


// Client prediction data
FNetworkPredictionData_Client* UBattleManiaMovement::GetPredictionData_Client() const 
{
	
	if (!ClientPredictionData) 
	{
		UBattleManiaMovement* MutableThis = const_cast<UBattleManiaMovement*>(this);

		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_BattleManiaCharacter(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}
	return ClientPredictionData;
}


// Server prediction data
FNetworkPredictionData_Server* UBattleManiaMovement::GetPredictionData_Server() const 
{
	if (!ServerPredictionData) 
	{
		UBattleManiaMovement* MutableThis = const_cast<UBattleManiaMovement*>(this);
		MutableThis->ServerPredictionData = new FNetworkPredictionData_Server_BattleManiaCharacter(*this);
	}
	return ServerPredictionData;
}


// Stores movement input before consuming 
FVector UBattleManiaMovement::ConsumeInputVector() 
{
	FVector Input = Super::ConsumeInputVector();

	if (PawnOwner && PawnOwner->IsLocallyControlled())
	{
		ServerSetInputVector(Input);
	}

	return Input;
}

float UBattleManiaMovement::GetMaxSpeed() const 
{
	if (!IsMovingOnGround()) { Super::GetMaxSpeed(); }
	return GetGroundSpeed();
}


float UBattleManiaMovement::GetMaxAcceleration() const 
{
	if (!IsMovingOnGround()) { return Super::GetMaxAcceleration(); }
	if (IsRunning() || IsSprinting()) { return RunAcceleration; }
	return WalkAcceleration;
}


// Max deceleration based on state 
float UBattleManiaMovement::GetMaxBrakingDeceleration() const 
{
	if (!IsMovingOnGround()) { return Super::GetMaxBrakingDeceleration(); }
	if (IsRunning() || IsSprinting()) { return RunDeceleration; }
	return WalkDeceleration;
}


float UBattleManiaMovement::GetGroundSpeed() const 
{
	
	if (IsCrouching()) { return GetCrouchedSpeed(); }
	
	if (IsAiming()) {
		if (IsSprinting()) { return RunSpeed; }
		return WalkSpeed;
	}
	
	if (IsSprinting()) { 
		if (RotationMode == ERotationMode::eVelocityMode) { return SprintSpeed; }
		return FMath::Abs((MovementInput.Rotation() - ControlRotation).GetNormalized().Yaw) > 50.0f ? RunSpeed : SprintSpeed;
	}
	
	if (IsRunning()) { return RunSpeed; }
	return WalkSpeed;
}



float UBattleManiaMovement::GetCrouchedSpeed() const 
{
	if (IsSprinting()) { return CrouchSpeed + 50.0f; }
	if (IsRunning()) { return CrouchSpeed; }
	return CrouchSpeed - 50.0f;
}
 

// Get character deceleration based on state
float UBattleManiaMovement::GetGroundFriction() const 
{
	if (IsRunning() || IsSprinting()) { return RunGroundFriction; }
	return WalkGroundFriction;
}


// Stance of character, depreciate
EStance UBattleManiaMovement::GetStance() const 
{
	if (IsCrouching()) { return EStance::eCrouching; }
	return EStance::eStanding;
}


// Get current gait mode based on state
EGaitMode UBattleManiaMovement::GetGaitMode() const 
{
	if (IsSprinting()) { return EGaitMode::eSprinting; }
	if (IsRunning()) { return EGaitMode::eRunning; }
	return EGaitMode::eWalking;
}


// Current locomotion mode based on state 
ELocomotionMode UBattleManiaMovement::GetLocomotionMode() const {
	
	// UE4 Movement mode conversion
	switch (MovementMode) {
	case EMovementMode::MOVE_None:
	case EMovementMode::MOVE_Flying:
	case EMovementMode::MOVE_Swimming:
	case EMovementMode::MOVE_Custom:
		break;
	case EMovementMode::MOVE_Walking:
	case EMovementMode::MOVE_NavWalking:
		return ELocomotionMode::eGrounded;
	case EMovementMode::MOVE_Falling:
		return ELocomotionMode::eFalling;
	}
	return ELocomotionMode::eNone;
}


ELocomotionMode UBattleManiaMovement::ConvertMovementMode(EMovementMode Mode) const
{
	switch (Mode) 
	{
	case EMovementMode::MOVE_None:
	case EMovementMode::MOVE_Flying:
	case EMovementMode::MOVE_Swimming:
	case EMovementMode::MOVE_Custom:
		break;
	case EMovementMode::MOVE_Walking:
	case EMovementMode::MOVE_NavWalking:
		return ELocomotionMode::eGrounded;
	case EMovementMode::MOVE_Falling:
		return ELocomotionMode::eFalling;
	}
	return ELocomotionMode::eNone;
}


void UBattleManiaMovement::ServerSetCrouchSpeed_Implementation(float NewValue) 
{
	CrouchSpeed = NewValue;
}


bool UBattleManiaMovement::ServerSetCrouchSpeed_Validate(float NewValue) 
{
	return true;
}


void UBattleManiaMovement::SetCrouchSpeed(float NewValue) 
{
	if (PawnOwner && PawnOwner->IsLocallyControlled())
	{
		ServerSetCrouchSpeed(NewValue);
	}
}


// Walk speed
void UBattleManiaMovement::ServerSetWalkSpeed_Implementation(float NewValue)
{
	WalkSpeed = NewValue;
}


bool UBattleManiaMovement::ServerSetWalkSpeed_Validate(float NewValue)
{
	return true;
}


void UBattleManiaMovement::SetWalkSpeed(float NewValue) 
{
	if (PawnOwner && PawnOwner->IsLocallyControlled()) 
	{
		ServerSetWalkSpeed(NewValue);
	}
}


void UBattleManiaMovement::ServerSetRunSpeed_Implementation(float NewValue) 
{
	RunSpeed = NewValue;
}


bool UBattleManiaMovement::ServerSetRunSpeed_Validate(float NewValue) 
{
	return true;

}


void UBattleManiaMovement::SetRunSpeed(float NewValue)
{
	if (PawnOwner && PawnOwner->IsLocallyControlled()) {
		ServerSetRunSpeed(NewValue);
	}
}


void UBattleManiaMovement::ServerSetSprintSpeed_Implementation(float NewValue) 
{
	SprintSpeed = NewValue;
}


bool UBattleManiaMovement::ServerSetSprintSpeed_Validate(float NewValue) {
	return true;
}


void UBattleManiaMovement::SetSprintSpeed(float NewValue) {
	if (PawnOwner && PawnOwner->IsLocallyControlled()) {
		ServerSetSprintSpeed(NewValue);
	}
}


// Walk acceleration
void UBattleManiaMovement::ServerSetWalkAcceleration_Implementation(float NewValue) 
{
	WalkAcceleration = NewValue;
}


bool UBattleManiaMovement::ServerSetWalkAcceleration_Validate(float NewValue) 
{
	return true;
}


void UBattleManiaMovement::SetWalkAcceleration(float NewValue) 
{
	if (PawnOwner && PawnOwner->IsLocallyControlled()) {
		ServerSetWalkAcceleration(NewValue);
	}
}


void UBattleManiaMovement::ServerSetRunAcceleration_Implementation(float NewValue) 
{
	RunAcceleration = NewValue;
}


bool UBattleManiaMovement::ServerSetRunAcceleration_Validate(float NewValue) 
{
	return true;
}


void UBattleManiaMovement::SetRunAcceleration(float NewValue) 
{
	if (PawnOwner && PawnOwner->IsLocallyControlled()) 
	{
		ServerSetRunAcceleration(NewValue);
	}
}


// Walk deceleration
void UBattleManiaMovement::ServerSetWalkDeceleration_Implementation(float NewValue) 
{
	WalkDeceleration = NewValue;
}


bool UBattleManiaMovement::ServerSetWalkDeceleration_Validate(float NewValue){
	return true;
}


void UBattleManiaMovement::SetWalkDeceleration(float NewValue) {
	if (PawnOwner && PawnOwner->IsLocallyControlled()) {
		ServerSetWalkDeceleration(NewValue);
	}
}


// Run deceleration
void UBattleManiaMovement::ServerSetRunDeceleration_Implementation(float NewValue) 
{
	RunDeceleration = NewValue;
}


bool UBattleManiaMovement::ServerSetRunDeceleration_Validate(float NewValue) 
{
	return true;

}


void UBattleManiaMovement::SetRunDeceleration(float NewValue) 
{
	if (PawnOwner && PawnOwner->IsLocallyControlled()) 
	{
		ServerSetRunDeceleration(NewValue);
	}
}


void UBattleManiaMovement::ServerSetWalkGroundFriction_Implementation(float NewValue)
{
	WalkGroundFriction = NewValue;
}


bool UBattleManiaMovement::ServerSetWalkGroundFriction_Validate(float NewValue) 
{
	return true;
}


void UBattleManiaMovement::SetWalkGroundFriction(float NewValue) {
	if (PawnOwner && PawnOwner->IsLocallyControlled()) {
		ServerSetWalkGroundFriction(NewValue);
	}
}


// Run ground friction
void UBattleManiaMovement::ServerSetRunGroundFriction_Implementation(float NewValue) 
{
	RunGroundFriction = NewValue;
}


bool UBattleManiaMovement::ServerSetRunGroundFriction_Validate(float NewValue) 
{
	return true;
}


void UBattleManiaMovement::SetRunGroundFriction(float NewValue) 
{
	if (PawnOwner && PawnOwner->IsLocallyControlled()) 
	{
		ServerSetRunGroundFriction(NewValue);
	}
}


// Get custom acceleration based on input and velocity for pivot 
void UBattleManiaMovement::SetCustomAcceleration() 
{

	float MovementDifferential = (MovementInput.Rotation() - Velocity.Rotation()).GetNormalized().Yaw;
	float Mult1 = FMath::GetMappedRangeValueClamped(FVector2D(45.0f, 130.0f), FVector2D(1.0, 0.2), FMath::Abs(MovementDifferential));
	float Mult2 = FMath::GetMappedRangeValueClamped(FVector2D(45.0f, 130.0f), FVector2D(1.0, 0.4), FMath::Abs(MovementDifferential));

	MaxAcceleration = GetRunAcceleration() * Mult1;
	GroundFriction = GetRunGroundFriction() * Mult2;
}


void UBattleManiaMovement::ServerSetRotationMode_Implementation(ERotationMode NewMode) 
{
	RotationMode = NewMode;
}


bool UBattleManiaMovement::ServerSetRotationMode_Validate(ERotationMode NewMode) 
{
	return true;
}


void UBattleManiaMovement::SetRotationMode(ERotationMode NewMode) 
{
	if (PawnOwner && PawnOwner->IsLocallyControlled()) {
		ServerSetRotationMode(NewMode);
	}
}


// Store current control rotation
bool UBattleManiaMovement::ServerSetControlRotation_Validate() 
{
	return true;
}


void UBattleManiaMovement::ServerSetControlRotation_Implementation() 
{
	ControlRotation = PawnOwner->GetControlRotation().GetNormalized();
}


// Store current movement input
bool UBattleManiaMovement::ServerSetInputVector_Validate(const FVector& Input) 
{
	return true;
}


void UBattleManiaMovement::ServerSetInputVector_Implementation(const FVector& Input) 
{
	MovementInput = Input;
}

// Resets all saved variables
void FSavedMove_BattleManiaCharacter::Clear() 
{
	Super::Clear();

	//Clear variables back to their default values.
	bSavedWantsToRun = false;
	bSavedWantsToSprint = false;
	bSavedWantsToAim = false;
}


// Store input commands in the compressed flags 
uint8 FSavedMove_BattleManiaCharacter::GetCompressedFlags() const 
{
	uint8 Result = Super::GetCompressedFlags();

	if (bSavedWantsToRun) 
	{
		Result |= FLAG_Custom_0;
	}

	if (bSavedWantsToSprint) 
	{
		Result |= FLAG_Custom_1;
	}

	if (bSavedWantsToAim) 
	{
		Result |= FLAG_Custom_2;
	}

	return Result;
}


// This is used to check whether or not two moves can be combined into one
bool FSavedMove_BattleManiaCharacter::CanCombineWith(const FSavedMovePtr & NewMove, ACharacter * Character, float MaxDelta) const 
{
	
	//This pretty much just tells the engine if it can optimize by combining saved moves. 
	//There doesn't appear to be any problem with leaving it out, but it seems that it's good practice to implement this anyways.

	if (bSavedWantsToRun != ((FSavedMove_BattleManiaCharacter*)& NewMove)->bSavedWantsToRun) {
		return false;
	}

	if (bSavedWantsToSprint != ((FSavedMove_BattleManiaCharacter*)& NewMove)->bSavedWantsToSprint) {
		return false;
	}

	if (bSavedWantsToAim != ((FSavedMove_BattleManiaCharacter*)& NewMove)->bSavedWantsToAim) {
		return false;
	}

	return Super::CanCombineWith(NewMove, Character, MaxDelta);
}


// Sets up the move before sending it to the server 
void FSavedMove_BattleManiaCharacter::SetMoveFor(ACharacter * Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) {
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	// Take the input from the player and store it in the saved move.
	UBattleManiaMovement* CharMov = Cast<UBattleManiaMovement>(Character->GetCharacterMovement());
	if (CharMov) {
		bSavedWantsToRun = CharMov->bWantsToRun;
		bSavedWantsToSprint = CharMov->bWantsToSprint;
		bSavedWantsToAim = CharMov->bWantsToAim;
	}
}


// Sets variables on character movement component before making a predictive correction 
void FSavedMove_BattleManiaCharacter::PrepMoveFor(class ACharacter* Character) 
{
	Super::PrepMoveFor(Character);

	UBattleManiaMovement* CharMov = Cast<UBattleManiaMovement>(Character->GetCharacterMovement());
	if (CharMov)
	{

	}
}


FNetworkPredictionData_Client_BattleManiaCharacter::FNetworkPredictionData_Client_BattleManiaCharacter(const UCharacterMovementComponent & ClientMovement)
	: Super(ClientMovement) {

}


FSavedMovePtr FNetworkPredictionData_Client_BattleManiaCharacter::AllocateNewMove() 
{
	return FSavedMovePtr(new FSavedMove_BattleManiaCharacter());
}


FNetworkPredictionData_Server_BattleManiaCharacter::FNetworkPredictionData_Server_BattleManiaCharacter(const UCharacterMovementComponent& ServerMovement)
	: Super(ServerMovement)
{

}

