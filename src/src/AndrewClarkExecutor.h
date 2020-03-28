#pragma once

class AndrewClarkExecutor : public BaseMissionExecutor
{
public:
	AndrewClarkExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	void update();

private:
	Ped spawnTarget();
	void prepareSet();
	void onTargetLocated();
	void cleanup();
};