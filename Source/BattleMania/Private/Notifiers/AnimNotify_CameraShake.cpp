

#include "AnimNotify_CameraShake.h"
#include "BattleManiaCharacter.h"

#include <Camera/CameraShake.h>


void UAnimNotify_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
	ABattleManiaCharacter* MyOwner = Cast<ABattleManiaCharacter>(MeshComp->GetOwner());
	if (!MyOwner) { return; }

	MyOwner->CameraShake_Notify(ShakeClass, ShakeScale);
}
 