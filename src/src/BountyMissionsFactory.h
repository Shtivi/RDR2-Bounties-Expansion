#pragma once

class BountyMissionsFactory
{
private:
	MapAreasManager* areasMgr;;
	std::map<int, BaseMissionExecutor*> cache;

public:
	BountyMissionsFactory(MapAreasManager* areasMgr);

	bool doesMissionExist(int missionId);
	BaseMissionExecutor* fromMissionId(int missionId);

private:
	void initializeCache();
	EliasTraditionExecutor* eliasTraditionExecutor();
};