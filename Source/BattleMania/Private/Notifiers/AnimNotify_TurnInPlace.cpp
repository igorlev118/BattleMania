

#include "AnimNotify_TurnInPlace.h"
#include "BattleManiaCharacter.h"
#include "BattleManiaAnimInstance.h"

#include <Curves/CurveFloat.h>


void UAnimNotify_TurnInPlace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) 
{
	auto AInst = Cast<UBattleManiaAnimInstance>(MeshComp->GetAnimInstance());
	if (!AInst) { return; }

	AInst->TurnInPlace_Notify(Montage, true, true, bIsRightTurn);
}
 
void UAnimNotify_TurnInPlace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) 
{
	ABattleManiaCharacter* MyOwner = Cast<ABattleManiaCharacter>(MeshComp->GetOwner());
	if (!MyOwner) { return; }

	UAnimInstance* AInst = MeshComp->GetAnimInstance();
	if (!AInst) { return; }
	
	float Position = AInst->Montage_GetPosition(Montage);
	float PlayRate = AInst->Montage_GetPlayRate(Montage);
	
	float CurrentYaw = CurveAsset->GetFloatValue(Position);
	float NextYaw = CurveAsset->GetFloatValue((PlayRate * FrameDeltaTime) + Position);
	float Yaw = NextYaw - CurrentYaw;

	MyOwner->DelayedRotation_Notify(FRotator(0.0f, Yaw, 0.0f), 0.2f);

	if (!MyOwner->GetVelocity().Equals(FVector(0.0f), 0.001)) 
	{
		AInst->Montage_Stop(0.2f, Montage);
	}
}

void UAnimNotify_TurnInPlace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
	auto AInst = Cast<UBattleManiaAnimInstance>(MeshComp->GetAnimInstance());
	if (!AInst) { return; }

	AInst->TurnInPlace_Notify(nullptr, false, false, false);
}
