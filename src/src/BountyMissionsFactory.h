#pragma once

class BountyMissionsFactory
{
private:
	MapAreasManager* areasMgr;;
	std::map<int, BaseMissionExecutor*> executorsCache;

public:
	BountyMissionsFactory(MapAreasManager* areasMgr);

	bool doesMissionExist(int missionId);
	BaseMissionExecutor* fromMissionId(int missionId);
	std::vector<int> getAllMissionIds();

private:
	void initializeCache();
	EliasTraditionExecutor* eliasTraditionExecutor();
	TurkishRunnerExecutor* turkishRunnerExecutor();
	JacobSeedExecutor* jacobSeedExecutor();
};