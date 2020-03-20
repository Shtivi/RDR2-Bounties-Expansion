#pragma once

enum MapAreas
{
	Blackwater,
	Valentine,
	Strawberry,
	Annesburg,
	SaintDenis,
	Lemoyne
};

void initializeMapAreasCache();
MapArea* getMapArea(MapAreas area);