#pragma once

class JacobSeedExecutor : public BaseMissionExecutor
{
private:
	Object campfire;
	Vehicle gatlingWagon;
	vector<Ped> enemies;
	Ped shooter;
	bool enemiesAlerted;
	bool finishedAlertingEnemies;

public:
	JacobSeedExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	void update();

private:
	Ped spawnTarget();
	void prepareSet();
	void onTargetLocated();
	void cleanup();
	void updateEnemies();
	void releaseUnnecessaryEntities();
	Ped addEnemy(Vector3 position, float heading = 0);
	void addEnemy(Ped enemy);
	void enemySitCamp(Ped enemy);
	void enemyScout(Ped enemy, float heading);
	void enemyShootGatling(Ped enemy);
	void enemyDriveGatling(Ped enemy);
};