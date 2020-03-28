#pragma once

class AndrewClarkExecutor : public BaseMissionExecutor
{
private:
	Vehicle wagon;
	vector<Object> campProps;
	bool isTargetAlerted;

public:
	AndrewClarkExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	void update();

private:
	Ped spawnTarget();
	void prepareSet();
	void onTargetLocated();
	void cleanup();
};