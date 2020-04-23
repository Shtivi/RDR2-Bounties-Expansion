#pragma once

using namespace std;

const int RESTART_FAILED_MISSION_WAITING_HOURS = 12;
const int RESTART_FAILED_MISSION_WAITING_SECS = RESTART_FAILED_MISSION_WAITING_HOURS * 60 * 60;

class BountiesManager
{
private:
	ModProgress* progress;
	MapAreasManager* areasMgr;
	BountyMissionsFactory* missionsFactory;
	
	vector<BaseMissionExecutor*> missionExecutors;
	map<int, tm> failedMissions;

public:
	BountiesManager(ModProgress* progress, MapAreasManager* areasMgr, BountyMissionsFactory* missionsFactory);
	void update();
	void resetMissions(MapAreas area);

private:
	void loadActiveMissions();
	void startNextMission(BaseMissionExecutor* after);
	void updateFailedMissions();
	bool isExecutorLoaded(BaseMissionExecutor* executor);
};
