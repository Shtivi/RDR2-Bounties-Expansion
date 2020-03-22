#pragma once

class EliasTraditionExecutor : public BaseMissionExecutor
{
private:
	Ped target;
	std::vector<Ped> enemies;
	Ped horse;

public:
	EliasTraditionExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	void update();

protected:
	void prepareSet();
	Ped spawnTarget();

private:
	void onTargetLocated();
	void createEnemyBlips();
	void addGuard(Vector3 position);
	void addGuard(Ped guard);
	void updateEnemies();
	void releaseUnnecessaryEntities();
	void cleanup();
};