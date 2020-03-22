#pragma once

class MapAreasManager
{
private:
	std::map<MapAreas, MapArea*> cache;

public:
	MapAreasManager();
	MapArea* getMapArea(MapAreas areaId);

private:
	MapArea* createBlackwater();
};