

#pragma once

#include "BattleMania.h"
#include "BattleManiaEnum.h"

#include <Animation/AnimNotifies/AnimNotify.h>
#include "AnimNotify_IdleEntry.generated.h"


UCLASS()
class BATTLEMANIA_API UAnimNotify_IdleEntry : public UAnimNotify {

	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	EIdleEntryState IdleEntryState;

};
