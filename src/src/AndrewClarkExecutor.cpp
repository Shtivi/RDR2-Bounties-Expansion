#include "Main.h";

AndrewClarkExecutor::AndrewClarkExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{

}

void AndrewClarkExecutor::update()
{
	BaseMissionExecutor::update();
}

Ped AndrewClarkExecutor::spawnTarget()
{
	return 0;
}

void AndrewClarkExecutor::prepareSet()
{

}

void AndrewClarkExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
}

void AndrewClarkExecutor::cleanup()
{
	BaseMissionExecutor::cleanup();

}