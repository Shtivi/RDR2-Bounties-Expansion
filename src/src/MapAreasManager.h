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
	MapArea* createRhodes();
	MapArea* createValentine();
	MapArea* createStrawberry();
	MapArea* createTumbleweed();
	MapArea* createArmadillo();
	MapArea* createSaintDenis();
};