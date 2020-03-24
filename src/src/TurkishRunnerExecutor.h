#pragma once

class TurkishRunnerExecutor : public BaseMissionExecutor
{
private:
	Vector3 campfirePos;
	Object campfire;
	Ped horse;
	std::vector<Ped> enemies;
	std::vector<Ped> horses;

	bool enemiesAlerted;

public:
	TurkishRunnerExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
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
};