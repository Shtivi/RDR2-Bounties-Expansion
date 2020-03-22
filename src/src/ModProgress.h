#pragma once

class ModProgress
{
private:
	bool hasChanges;
	const char* dataFile;
	std::map<int, BountyMissionStatus> cache;

public:
	ModProgress(const char* dataFile);

	BountyMissionStatus getMissionProgress(int missionId);
	void completeMission(int missionId);
	void collectMission(int missionId);
	void allowMission(int missionId);
	void save();

private:
	void setMissionProgress(int missionId, BountyMissionStatus status);
	void readFromDataFile();
	void parseToCache(std::string inputLine);
};