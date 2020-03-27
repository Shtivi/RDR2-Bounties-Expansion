#include "Main.h";

JacobSeedExecutor::JacobSeedExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
}

void JacobSeedExecutor::update()
{
	BaseMissionExecutor::update();
}

void JacobSeedExecutor::prepareSet()
{

}

Ped JacobSeedExecutor::spawnTarget()
{
	return 0;
}