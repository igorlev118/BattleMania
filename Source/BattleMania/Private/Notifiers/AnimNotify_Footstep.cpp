

#include "AnimNotify_Footstep.h"

#include <Animation/AnimInstance.h>
#include <Components/AudioComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <UObject/ConstructorHelpers.h>



UAnimNotify_Footstep::UAnimNotify_Footstep() 
{
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundCueObject(TEXT("/Game/BattleMania/Audio/Footsteps/Footstep_Cue"));
	FootstepCue = SoundCueObject.Object;
}


void UAnimNotify_Footstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{

	auto AInst = MeshComp->GetAnimInstance();
	if (!AInst) { return; }

	if (!MeshComp->IsVisible()) { return; }

	auto Montage = AInst->GetCurrentActiveMontage();
	float PlayRate = AInst->Montage_GetPlayRate(Montage);

	if (PlayReversed) 
	{
		if (PlayRate >= 0.0f) { return; }
	}
	else 
	{
		if (PlayRate < 0.0f) { return; }
	}

	auto AudioComp = UGameplayStatics::SpawnSoundAttached(
		FootstepCue,
		MeshComp,
		AttachPointName,
		FVector(0.0f),
		EAttachLocation::KeepRelativeOffset,
		false,
		VolumeMultiplier,
		PitchMultiplier
	);

	if (!AudioComp) { return; }

	AudioComp->SetIntParameter("FootstepType", (int32)FootstepType);
}
 