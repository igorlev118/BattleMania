#include "PointOfInterest.h"
#include "MiniMapGameState.h"


UPointOfInterest::UPointOfInterest() 
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts or spawn
void UPointOfInterest::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()) {
		auto GameState = Cast<AMiniMapGameState>(GetWorld()->GetGameState());
		if (GameState) {
			GameState->RegisterPointOfInterest(this);
		}
	}
}

