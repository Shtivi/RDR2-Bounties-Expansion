#pragma once

class MarquisRussellExecutor : public BaseMissionExecutor
{

enum EnemiesMode
{
	IDLE,
	ALERTED,
	WARNING,
	COMBAT
};

private:
	Vector3 campfirePos;
	Object campfire;
	Ped horse;
	vector<Ped> enemies;
	vector<Ped> horses;
	EnemiesMode enemiesStatus;
	GameStopwatch stopwatch;
	bool toleratePlayer;
	bool weapon;

public:
	MarquisRussellExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	void update();

protected:
	void prepareSet();
	Ped spawnTarget();
	void onTargetLocated();
	void cleanup();

private:
	void releaseUnnecessaryEntities();
	void addEnemy(Vector3 pos);
	void addEnemy(Ped ped);
	void addHorse(const char* model, Vector3 pos);
	void addHorse(Ped horse);
	void enterIdleMode();
	void enterAlertMode();
	void enterWarningMode();
	void enterCombatMode();
	void createEnemyBlips();
};