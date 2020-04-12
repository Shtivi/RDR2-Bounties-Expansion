#pragma once

enum BountiesMenuMode
{
	Closed,
	MissionDetails,
	MissionsList
};

class BountiesMenu
{
private:
	BountiesMenuMode mode;
	Prompt* closePrompt;
	BountyMissionData* displayedMission;

public:
	BountiesMenu();

	void open();
	void close();
	void showMissionDetails(BountyMissionData* missionData);
	void update();

private:
	void printMission();
	void printMissionsList();
	char* deadOrAlive(TargetCondition condition);
};