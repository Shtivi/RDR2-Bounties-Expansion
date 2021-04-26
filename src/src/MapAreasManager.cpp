#include "Main.h";


MapAreasManager::MapAreasManager()
{
	cache[MapAreas::Blackwater] = createBlackwater();
	cache[MapAreas::Rhodes] = createRhodes();
	cache[MapAreas::Valentine] = createValentine();
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

	Vector3 moneyCoords = toVector3(-762.495, -1267.61, 43.8441);

	Vector3 cellCoords = toVector3(-762.69, -1263.44, 43.0245);

	Vector3 posterCoords;
	posterCoords.x = -756.9555;
	posterCoords.y = -1270.587;
	posterCoords.z = 44.17991;
	int cellnumber = 2167775834;

	return new MapArea("Blackwater", policeDeptCoords, posterCoords, moneyCoords, cellCoords, cellnumber, 90.4);
}

MapArea* MapAreasManager::createRhodes()
{
	Vector3 policeDeptCoords = toVector3(1358.17, -1308.19, 76.7296);
	Vector3 cellCoords = toVector3(1356.16, -1301.41, 76.7606);
	Vector3 posterCoords = toVector3(1234.58, -1293.13, 77.2681);
	Vector3 moneyCoords = toVector3(1361.9, -1304.21, 77.5413);
	int cellnumber = 1878514758;

	return new MapArea("Rhodes", policeDeptCoords, posterCoords, moneyCoords, cellCoords, cellnumber, 136);
}

MapArea* MapAreasManager::createValentine()
{
	Vector3 policeDeptCoords = toVector3(-275.256, 801.303, 118.397);
	Vector3 cellCoords = toVector3(-272.71, 809.093, 118.371);
	Vector3 posterCoords = toVector3(-272.777, 799.70, 119.412);
	Vector3 moneyCoords = toVector3(-277.1, 805.486, 119.17);
	int cellnumber = 535323366;

	return new MapArea("Valentine", policeDeptCoords, posterCoords, moneyCoords, cellCoords, cellnumber, 11);
}

MapArea* MapAreasManager::createStrawberry()
{
	Vector3 policeDeptCoords = toVector3(-1804.106, -352.3542, 164.1339);
	Vector3 cellCoords = toVector3(-1813.23, -355.196, 160.43);
	Vector3 posterCoords = toVector3(-1805.729, -348.1523, 164.342);
	Vector3 moneyCoords = toVector3(-1807.99, -348.587, 164.448);
	int cellnumber = 902070893;

	return new MapArea("Strawberry", policeDeptCoords, posterCoords, moneyCoords, cellCoords, cellnumber, 66.03);
}

MapArea* MapAreasManager::createTumbleweed()
{
	Vector3 policeDeptCoords = toVector3(-5527.188, -2927.814, -1.360926);
	Vector3 cellCoords = toVector3(-5531.63, -2919.28, -2.36093);
	Vector3 posterCoords = toVector3(-5531.614, -2934.285, -1.772461);
	Vector3 moneyCoords = toVector3(-5530.2, -2929.55, -1.57704);
	int cellnumber = 2984805596;

	return new MapArea("Tumbleweed", policeDeptCoords, posterCoords, moneyCoords, cellCoords, cellnumber, 82.30);
}

MapArea* MapAreasManager::createArmadillo()
{
	Vector3 policeDeptCoords = toVector3(-3619.911, -2605.103, -13.33457);
	Vector3 cellCoords = toVector3(-3617.92, -2604.87, -14.3378);
	Vector3 posterCoords = toVector3(-3625.664, -2603.477, -13.42546);
	Vector3 moneyCoords = toVector3(-3623.91, -2602.77, -13.5533);
	int cellnumber = 4235597664;

	return new MapArea("Armadillo", policeDeptCoords, posterCoords, moneyCoords, cellCoords, cellnumber, 293.79);
}

MapArea* MapAreasManager::createSaintDenis()
{
	Vector3 policeDeptCoords = toVector3(2502.79, -1308.546, 47.95366);
	Vector3 cellCoords = toVector3(2503.68, -1307.05, 47.9537);
	Vector3 posterCoords = toVector3(2516.739, -1305.577, 49.26161);
	Vector3 moneyCoords = toVector3(2507.4, -1309.02, 48.7525);
	int cellnumber = 1711767580;

	return new MapArea("SaintDenis", policeDeptCoords, posterCoords, moneyCoords, cellCoords, cellnumber, 91.36);
}