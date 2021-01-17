#include "Main.h";


MapAreasManager::MapAreasManager()
{
	cache[MapAreas::Blackwater] = createBlackwater();
	cache[MapAreas::Rhodes]		= createRhodes();
	cache[MapAreas::Valentine]	= createValentine();
	cache[MapAreas::Strawberry] = createStrawberry();
	cache[MapAreas::Tumbleweed] = createTumbleweed();
	cache[MapAreas::Armadillo] = createArmadillo();
	cache[MapAreas::SaintDenis] = createSaintDenis();
}


MapArea* MapAreasManager::getMapArea(MapAreas area)
{
	if (cache.find(area) == cache.end())
	{
		return NULL;
	}

	return cache.find(area)->second;
}

vector<MapArea*> MapAreasManager::getMapAreas()
{
	vector<MapArea*> results;
	map<MapAreas, MapArea*>::iterator it;
	for (it = cache.begin(); it != cache.end(); it++)
	{
		results.push_back((*it).second);
	}

	return results;
}

MapArea* MapAreasManager::createBlackwater()
{
	Vector3 policeDeptCoords;
	policeDeptCoords.x = -756.347;
	policeDeptCoords.y = -1269.24;
	policeDeptCoords.z = 43.0285;

	Vector3 cellCoords = toVector3(-765.036, -1264.13, 44.0245);

	Vector3 posterCoords;
	posterCoords.x = -756.9555;
	posterCoords.y = -1270.587;
	posterCoords.z = 44.17991;

	return new MapArea("Blackwater", policeDeptCoords, posterCoords, cellCoords, 90.4);
}

MapArea* MapAreasManager::createRhodes()
{
	Vector3 policeDeptCoords = toVector3(1358.17, -1308.19, 76.7296);
	Vector3 cellCoords = toVector3(1357.97, -1301.96, 76.7606);
	Vector3 posterCoords = toVector3(1234.58, -1293.13, 77.2681);

	return new MapArea("Rhodes", policeDeptCoords, posterCoords, cellCoords, 136);
}

MapArea* MapAreasManager::createValentine()
{
	Vector3 policeDeptCoords = toVector3(-275.256, 801.303, 118.397);
	Vector3 cellCoords = toVector3(-275.918, 810.098, 118.376);
	Vector3 posterCoords = toVector3(-272.777, 799.70, 119.412);

	return new MapArea("Valentine", policeDeptCoords, posterCoords, cellCoords, 11);
}

MapArea* MapAreasManager::createStrawberry()
{
	Vector3 policeDeptCoords = toVector3(-1804.106, -352.3542, 164.1339);
	Vector3 cellCoords = toVector3(-1812.943, -352.3905, 160.3946);
	Vector3 posterCoords = toVector3(-1805.729, -348.1523, 164.342);

	return new MapArea("Strawberry", policeDeptCoords, posterCoords, cellCoords, 66.03);
}

MapArea* MapAreasManager::createTumbleweed()
{
	Vector3 policeDeptCoords = toVector3(-5527.188, -2927.814, -1.360926);
	Vector3 cellCoords = toVector3(-5527.188, -2927.814, -2.360926);
	Vector3 posterCoords = toVector3(-5531.614, -2934.285, -1.772461);

	return new MapArea("Tumbleweed", policeDeptCoords, posterCoords, cellCoords, 82.30);
}

MapArea* MapAreasManager::createArmadillo()
{
	Vector3 policeDeptCoords = toVector3(-3619.911, -2605.103, -13.33457);
	Vector3 cellCoords = toVector3(-3619.911, -2605.103, -14.33457);
	Vector3 posterCoords = toVector3(-3625.664, -2603.477, -13.42546);

	return new MapArea("Armadillo", policeDeptCoords, posterCoords, cellCoords, 293.79);
}

MapArea* MapAreasManager::createSaintDenis()
{
	Vector3 policeDeptCoords = toVector3(2502.79, -1308.546, 47.95366);
	Vector3 cellCoords = toVector3(2502.79, -1308.546, 47.95366);
	Vector3 posterCoords = toVector3(2516.739, -1305.577, 49.26161);

	return new MapArea("SaintDenis", policeDeptCoords, posterCoords, cellCoords, 91.36);
}