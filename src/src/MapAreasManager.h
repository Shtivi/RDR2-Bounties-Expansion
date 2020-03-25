#pragma once

using namespace std;

class MapAreasManager
{
private:
	map<MapAreas, MapArea*> cache;

public:
	MapAreasManager();
	MapArea* getMapArea(MapAreas areaId);
	vector<MapArea*> getMapAreas();

private:
	MapArea* createBlackwater();
};