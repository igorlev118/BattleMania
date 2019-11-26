

#pragma once

#include "BattleMania.h"

#include <Animation/AnimNotifies/AnimNotifyState.h>
#include "AnimNotify_TurnInPlace.generated.h"

class UCurveFloat;


UCLASS()
class BATTLEMANIA_API UAnimNotify_TurnInPlace : public UAnimNotifyState 
{

	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


	UPROPERTY(EditAnywhere, Category = "Parameters")
	bool bIsRightTurn;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	UCurveFloat* CurveAsset;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	UAnimMontage* Montage;
};
