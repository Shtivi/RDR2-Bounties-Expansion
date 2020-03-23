#pragma once

class BountiesManager
{
private:
	std::vector<BaseMissionExecutor*> missionExecutors;
	ModProgress* progress;
	MapAreasManager* areasMgr;
	BountyMissionsFactory* missionsFactory;

public:
	BountiesManager(ModProgress* progress, MapAreasManager* areasMgr, BountyMissionsFactory* missionsFactory);
	void update();

private:
	void loadActiveMissions();
	void startNextMission(BaseMissionExecutor* after);
	//void addMission(BaseMissionExecutor* executor);
};
