

#include "AnimNotify_IdleEntry.h"
#include "BattleManiaAnimInstance.h"


void UAnimNotify_IdleEntry::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
	UBattleManiaAnimInstance* AInst = Cast<UBattleManiaAnimInstance>(MeshComp->GetAnimInstance());
	if (!AInst) { return; }

	AInst->IdleEntry_Notify(IdleEntryState);
}
 