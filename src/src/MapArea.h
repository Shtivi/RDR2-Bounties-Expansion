#pragma once

struct MapArea
{
	const char* name;
	Vector3* policeDeptCoords;
	Vector3* bountyPostersCoords;
	Vector3* cellCoords;

	MapArea(const char* name, Vector3 policeDeptCoords, Vector3 bountyPostersCoords, Vector3 cellCoords)
	{
		this->name = name;
		this->policeDeptCoords = new Vector3(policeDeptCoords);
		this->bountyPostersCoords = new Vector3(bountyPostersCoords);
		this->cellCoords = new Vector3(cellCoords);
	}
};