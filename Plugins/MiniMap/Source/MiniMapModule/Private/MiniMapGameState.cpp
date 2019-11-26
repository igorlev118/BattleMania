#include "MiniMapGameState.h"
#include "PointOfInterest.h"
#include "MapWidget.h"



void AMiniMapGameState::RegisterPointOfInterest(UPointOfInterest* POI) 
{
	if (!POI) { return; }

	PointsOfInterest.Add(POI);
	for (UMapWidget* Map : Maps) 
	{
		Map->AddPointOfInterest(POI);
	}
}


void AMiniMapGameState::RegisterMap(UMapWidget* Map) 
{
	if (!Map) { return; }

	Maps.Add(Map);
	for (UPointOfInterest* POI : PointsOfInterest) 
	{
		Map->AddPointOfInterest(POI);
	}
}

