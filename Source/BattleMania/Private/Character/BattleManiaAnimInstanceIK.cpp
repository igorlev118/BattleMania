

#include "BattleManiaAnimInstanceIK.h"
#include "BattleManiaCharacter.h"
#include "BattleManiaMovement.h"

#include <DrawDebugHelpers.h>
#include <Engine/Engine.h>


UBattleManiaAnimInstanceIK::UBattleManiaAnimInstanceIK() 
{
	LeftFootBoneName = "foot_l";
	RightFootBoneName = "foot_r";
	bShowTraces = false;
	bIsRagdoll = false;
	bEnableFootIK = true;
	FootIKAlpha = 1.0f;;
	TraceHeightAboveFoot = 50.0f;
	TraceHeightBelowFoot = 75.0f;
	RotationInterpolationSpeed = 15.0f;
	Z_InterpolationSpeed = 15.0f;
	PelvisOffset = 0.0f;
	StandingMinLimits = FVector(-10.0f, -30.0f, -30.0f);
	StandingMaxLimits = FVector(10.0f, 30.0f, 20.0f);
	CrouchingMinLimits = FVector(-10.0f, -30.0f, -15.0f);
	CrouchingMaxLimits = FVector(10.0f, 30.0f, 10.0f);
}


void UBattleManiaAnimInstanceIK::NativeInitializeAnimation() 
{
	Character = Cast<ABattleManiaCharacter>(GetOwningActor());
	if (!Character) { return; }

	UpdateAnimationState();
}


void UBattleManiaAnimInstanceIK::NativeUpdateAnimation(float DeltaTimeX) 
{
	if (!Character) { return; }

	UpdateAnimationState();

	if (bIsRagdoll) 
	{
		RagdollIK();
		return;
	}

	switch (LocomotionMode)
	{
	case ELocomotionMode::eGrounded:
		FootIK();
		break;
	case ELocomotionMode::eFalling:
		bEnableFootIK = false;
		break;
	}
}

void UBattleManiaAnimInstanceIK::FootIK_Implementation() 
{
	if (!bEnableFootIK) { bEnableFootIK = true; }

	USkeletalMeshComponent* MyComponent = GetOwningComponent();
	if (!MyComponent) { return; }

	// Determine feet locations
	FVector RootLocation = MyComponent->GetComponentLocation();
	FVector LFLocation = MyComponent->GetSocketLocation(LeftFootBoneName);
	FVector RFLocation = MyComponent->GetSocketLocation(RightFootBoneName);

	// Line-trace start / end for left foot
	FVector LFStart = LFLocation;
	LFStart.Z = RootLocation.Z + TraceHeightAboveFoot;
		
	FVector LFEnd = LFLocation;
	LFEnd.Z = RootLocation.Z - TraceHeightBelowFoot;

	// Line-trace start / end for right foot
	FVector RFStart = RFLocation;
	RFStart.Z = RootLocation.Z + TraceHeightAboveFoot;

	FVector RFEnd = RFLocation;
	RFEnd.Z = RootLocation.Z - TraceHeightBelowFoot;

	// Setup line-trace parameters
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredComponent(MyComponent);
	QueryParams.bTraceComplex = true;

	// Trace world for left foot
	FHitResult Hit;
	FVector LFOffsetTarget, RFOffsetTarget;
	if (GetWorld()->LineTraceSingleByChannel(Hit, LFStart, LFEnd, ECC_Visibility, QueryParams)) {

		// Debug traces
		if (bShowTraces) 
		{
			DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 15.0f, FColor::Green);
			DrawDebugLine(GetWorld(), LFStart, Hit.ImpactPoint, FColor::Green, false, 0.0f, 0, 2.0f);
		}
		
		// Determine offset target left foot
		LFOffsetTarget = FVector(FMath::RadiansToDegrees(FMath::Atan2(Hit.Normal.Y, Hit.Normal.Z)), FMath::RadiansToDegrees(FMath::Atan2(Hit.Normal.X, Hit.Normal.Z)),
			Hit.Location.Z - RootLocation.Z);

		// Clamp based on stance
		LFOffsetTarget = (Stance == EStance::eCrouching) ? 
			ClampVector(LFOffsetTarget, CrouchingMinLimits, CrouchingMaxLimits) : 
			ClampVector(LFOffsetTarget, StandingMinLimits, StandingMaxLimits);
		LFOffsetTarget.Y *= -1.0f;
	}
	else if (bShowTraces) 
	{
		DrawDebugPoint(GetWorld(), LFEnd, 15.0f, FColor::Blue);
		DrawDebugLine(GetWorld(), LFStart, LFEnd, FColor::Blue, false, 0.0f, 0, 2.0f);
	}

	// Trace world for right foot
	if (GetWorld()->LineTraceSingleByChannel(Hit, RFStart, RFEnd, ECC_Visibility, QueryParams)) 
	{

		// Debug traces
		if (bShowTraces) 
		{
			DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 15.0f, FColor::Green);
			DrawDebugLine(GetWorld(), RFStart, Hit.ImpactPoint, FColor::Green, false, 0.0f, 0, 2.0f);
		}

		// Determine offset target left foot
		RFOffsetTarget = FVector(
			FMath::RadiansToDegrees(FMath::Atan2(Hit.Normal.Y, Hit.Normal.Z)),
			FMath::RadiansToDegrees(FMath::Atan2(Hit.Normal.X, Hit.Normal.Z)),
			Hit.Location.Z - RootLocation.Z
		);

		// Clamp based on stance
		RFOffsetTarget = (Stance == EStance::eCrouching) ?
			ClampVector(RFOffsetTarget, CrouchingMinLimits, CrouchingMaxLimits) :
			ClampVector(RFOffsetTarget, StandingMinLimits, StandingMaxLimits);
		RFOffsetTarget.Y *= -1.0f;
	}
	else if (bShowTraces) {
		DrawDebugPoint(GetWorld(), RFEnd, 15.0f, FColor::Blue);
		DrawDebugLine(GetWorld(), RFStart, RFEnd, FColor::Blue, false, 0.0f, 0, 2.0f);
	}

	float DeltaTime = GetWorld()->GetDeltaSeconds();
	// Interpolate left foot
	LeftFootOffset = FVector(
		FMath::Vector2DInterpTo(
			FVector2D(LeftFootOffset), 
			FVector2D(LFOffsetTarget), 
			DeltaTime,
			RotationInterpolationSpeed),
		FMath::FInterpTo(
			LeftFootOffset.Z, 
			LFOffsetTarget.Z, 
			DeltaTime,
			Z_InterpolationSpeed)
	);
	if (LeftFootOffset.ContainsNaN()) { LeftFootOffset = FVector(0.0f); }

	// Interpolate right foot
	RightFootOffset = FVector(
		FMath::Vector2DInterpTo(
			FVector2D(RightFootOffset),
			FVector2D(RFOffsetTarget),
			DeltaTime,
			RotationInterpolationSpeed),
		FMath::FInterpTo(
			RightFootOffset.Z,
			RFOffsetTarget.Z,
			DeltaTime,
			Z_InterpolationSpeed)
	);
	if (RightFootOffset.ContainsNaN()) { RightFootOffset = FVector(0.0f); }

	// Set pelvis offset
	PelvisOffset = (LeftFootOffset.Z < RightFootOffset.Z) ? LeftFootOffset.Z : RightFootOffset.Z;
}


void UBattleManiaAnimInstanceIK::RagdollIK_Implementation() 
{
	if (!bEnableFootIK) { bEnableFootIK = true; }

	USkeletalMeshComponent* MyComponent = GetOwningComponent();
	if (!MyComponent) { return; }

	FVector LFLocation, RFLocation;
	FQuat LFRotation, RFRotation;

	// Transforms based on socket
	MyComponent->GetSocketWorldLocationAndRotation(LeftFootBoneName, LFLocation, LFRotation);
	MyComponent->GetSocketWorldLocationAndRotation(RightFootBoneName, RFLocation, RFRotation);

	LeftFootTransform = FTransform(LFRotation, LFLocation, FVector(1.0f));
	RightFootTransform = FTransform(RFRotation, RFLocation, FVector(1.0f));
}

void UBattleManiaAnimInstanceIK::UpdateAnimationState()
 {
	if (!Character) { return; }

	IBattleManiaInterfaceABPIK::Execute_OnSetShowTraces((UObject*)this, Character->bShowTraces);
	IBattleManiaInterfaceABPIK::Execute_OnSetIsRagdoll((UObject*)this, Character->bIsRagdoll);
	
	auto CharMov = Character->GetBattleManiaMovement();
	if (!CharMov) { return; }

	IBattleManiaInterfaceABPIK::Execute_OnSetStance((UObject*)this, CharMov->GetStance());
	IBattleManiaInterfaceABPIK::Execute_OnSetLocomotionMode((UObject*)this, CharMov->GetLocomotionMode());
}

