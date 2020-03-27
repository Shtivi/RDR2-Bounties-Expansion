#pragma once

class JacobSeedExecutor : public BaseMissionExecutor
{
public:
	JacobSeedExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	void update();

private:
	void prepareSet();
	Ped spawnTarget();
};