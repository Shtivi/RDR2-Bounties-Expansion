#pragma once

class EliasTraditionExecutor : public BaseMissionExecutor
{
private:
	Ped target;
	Ped killer;
	Ped victim;
	std::vector<Ped> enemies;
	Vehicle wagon;
	Ped horse;

public:
	EliasTraditionExecutor(BountyMissionData missionData);
	void update();

protected:
	void prepareSet();
	Ped spawnTarget();

private:
	void onTargetLocated();
	void createEnemyBlips();
	void addGuard(Vector3 position);
	void addGuard(Ped guard);
	void updateBlips(); // todo: remove
	void updateEnemies();
	void playVictimsExecution();
	void releaseUnnecessaryEntities();
	void cleanup();
};