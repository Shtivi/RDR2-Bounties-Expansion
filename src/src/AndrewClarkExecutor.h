#pragma once

class AndrewClarkExecutor : public BaseMissionExecutor
{
private:
	Prompt* threatPrompt;
	Vehicle wagon;
	vector<Object> campProps;
	bool isTargetAlerted;
	bool targetRobbed;
	Object stash;

public:
	AndrewClarkExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	void update();

private:
	Ped spawnTarget();
	void prepareSet();
	void onTargetLocated();
	void cleanup();

	void playTargetRobbery();
	void goToStash();
};