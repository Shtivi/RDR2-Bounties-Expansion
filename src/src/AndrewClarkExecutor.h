#pragma once

enum RobberyProgress
{
	NONE,
	TARGET_RESISTING,
	WAITING_FOR_INTIMIDATION,
	TARGET_GAVE_UP,
	FINISHED
};

class AndrewClarkExecutor : public BaseMissionExecutor
{
private:
	Vehicle wagon;
	Object stash;
	vector<Object> campProps;
	Prompt* threatPrompt;
	bool isTargetAlerted;
	bool isTargetScared;
	bool spawnedBountyHunters;
	int robberyAttempts;
	RobberyProgress robberyProgress;

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