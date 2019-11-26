

#pragma once

#include "BattleMania.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_CameraShake.generated.h"

class UCameraShake;


UCLASS()
class BATTLEMANIA_API UAnimNotify_CameraShake : public UAnimNotify 
{

	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	float ShakeScale = 1.0f;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	TSubclassOf<UCameraShake> ShakeClass;
};
