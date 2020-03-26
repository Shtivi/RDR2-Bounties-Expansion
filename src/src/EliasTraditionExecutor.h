#pragma once

class EliasTraditionExecutor : public BaseMissionExecutor
{
private:
	vector<Ped> enemies;
	Ped horse;
	Ped killer;
	Ped victim;
	bool executedVictim;
	bool enemiesAlerted;

public:
	EliasTraditionExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	void update();

protected:
	void prepareSet();
	Ped spawnTarget();

private:
	void onTargetLocated();
	void createEnemyBlips();
	Ped addGuard(Vector3 position);
	void addGuard(Ped guard);
	void updateEnemies();
	void playVictimExecution();
	void releaseUnnecessaryEntities();
	void cleanup();
};