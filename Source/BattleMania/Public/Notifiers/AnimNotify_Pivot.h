

#pragma once

#include "BattleMania.h"
#include "BattleManiaStruct.h"

#include <Animation/AnimNotifies/AnimNotifyState.h>
#include "AnimNotify_Pivot.generated.h"


/**
 *  Implements custom pivot AnimNotify
 */
UCLASS()
class BATTLEMANIA_API UAnimNotify_Pivot : public UAnimNotifyState {

	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	FPivotParameters PivotParams;

};
