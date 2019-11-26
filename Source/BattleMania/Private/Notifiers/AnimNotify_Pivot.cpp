

#include "AnimNotify_Pivot.h"
#include "BattleManiaAnimInstance.h"


void UAnimNotify_Pivot::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) 
{
	UBattleManiaAnimInstance* AInst = Cast<UBattleManiaAnimInstance>(MeshComp->GetAnimInstance());
	if (!AInst) { return; }

	AInst->Pivot_Notify(PivotParams);
}
 