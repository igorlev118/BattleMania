#pragma once

#include "CoreMinimal.h"
#include <Components/ActorComponent.h>
#include "PointOfInterest.generated.h"

class UTexture2D;



UCLASS( ClassGroup = (MiniMap), meta=(BlueprintSpawnableComponent))
class MINIMAPMODULE_API UPointOfInterest : public UActorComponent 
{

	GENERATED_BODY()

public:
	UPointOfInterest();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointOfInterest")
	bool bAlwaysShow = true; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointOfInterest")
	FColor IconTint = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PointOfInterest")
	UTexture2D* IconTexture = nullptr;
};
