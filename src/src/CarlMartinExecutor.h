#pragma once

class CarlMartinExecutor : public BaseMissionExecutor
{
private:
	Vector3 campfirePos;
	Object campfire;
	Ped horse;
	GuardsGroup* enemiesGroup;
	vector<Ped> horses;

public:
	CarlMartinExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	void update();

protected:
	void prepareSet();
	Ped spawnTarget();
	void onTargetLocated();
	void cleanup();

private:
	void releaseUnnecessaryEntities();
	void addHorse(Ped horse);
	void addHorse(const char* model, Vector3 pos);
};