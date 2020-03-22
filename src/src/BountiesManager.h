#pragma once

class BountiesManager
{
private:
	std::vector<BaseMissionExecutor*> missionExecutors;
	ModProgress* progress;
	MapAreasManager* areasMgr;

public:
	BountiesManager(ModProgress* progress, MapAreasManager* areasMgr);
	void update();

private:
	void createEliasTradition();
};
