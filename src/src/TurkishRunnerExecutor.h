#pragma once

class TurkishRunnerExecutor : public BaseMissionExecutor
{
private:
	Ped target;
	Ped horse;
	bool isFleeing;

public:
	TurkishRunnerExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	void update();

protected:
	void prepareSet();
	Ped spawnTarget();
	void cleanup();
};