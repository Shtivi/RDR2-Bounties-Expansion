#include "Main.h";

TurkishRunnerExecutor::TurkishRunnerExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	isFleeing = false;
	setTargetAreaRadius(120);
}

void TurkishRunnerExecutor::update()
{
	BaseMissionExecutor::update();

	Ped player = PLAYER::PLAYER_PED_ID();
	if (target && !isFleeing && distanceBetweenEntities(horse, player) < 10)
	{
		isFleeing = true;
		AI::CLEAR_PED_TASKS(target, 0, 0);
		//AI::CLEAR_PED_TASKS(horse, 0, 0);
		AI::TASK_SMART_FLEE_PED(target, player, 20, -1, 0, 0, 0);
		//AI::TASK_COMBAT_PED(target, player, 0, 16);
	}

	if (isFleeing)
		displayDebugText("should flee");
}

void TurkishRunnerExecutor::prepareSet()
{

}

Ped TurkishRunnerExecutor::spawnTarget()
{
	horse = createPed("A_C_Horse_Turkoman_DarkBay", toVector3(-963.288, -950.602, 59.2778));
	Ped target = createPedOnHorse("G_M_M_UniBanditos_01", horse);

	return target;
}

void TurkishRunnerExecutor::cleanup()
{
	releaseEntitySafe(&horse);
}