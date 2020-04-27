/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019
*/

#include "Main.h"

using namespace std;

ModProgress* modProgress;
MapAreasManager* areasMgr;
BountyMissionsFactory* missionsFactory;
BountiesManager* bountiesMgr;



GuardsGroup* group;
Ped temp = 0;

void initialize()
{
	initializeLogger();
	log("### Starting initialization ###");
	modProgress = new ModProgress("BountiesExpansion.dat");
	areasMgr = new MapAreasManager();
	missionsFactory = new BountyMissionsFactory(areasMgr);
	log("initializing bounties manager");
	bountiesMgr = new BountiesManager(modProgress, areasMgr, missionsFactory);
	initializeUI();
	log("### Initialization completed ###");
}

void main()
{
	initialize();

	while (true)
	{
		bountiesMgr->update();
		menu->update();
		printHelpMessage();

		if (group)
		{
			group->update();
		}

		if (temp && ENTITY::DOES_ENTITY_EXIST(temp) && !ENTITY::IS_ENTITY_DEAD(temp))
		{
			displayDebugText(to_string(AI::GET_SEQUENCE_PROGRESS(temp)).c_str());
		}

		if (IsKeyJustUp(VK_KEY_Z))
		{
			if (group)
			{
				group->stop();
				delete group;
			}

			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);
			Vector3 pos = playerPos + forwardVec * 60;
			getGroundPos(&pos);
			group = new GuardsGroup(toVector3(1117.49, -1988.06, 54.3471), 25);
			
			Ped ped1 = createPed("g_m_y_uniexconfeds_01", toVector3(1107.74, -1984.7, 53.8183));
			Ped ped2 = createPed("g_m_y_uniexconfeds_01", toVector3(1122.45, -1984.45, 53.0666));
			group->add(ped1, IdlingModifier::Scout);

			RoutineParams routine2;
			routine2.patrolRoute.push_back(toVector3(1114.12, -1983.69, 53.9669));
			routine2.patrolRoute.push_back(toVector3(1120.18, -1982.46, 53.348));
			routine2.patrolRoute.push_back(toVector3(1125.8, -1990.2, 52.0249));
			group->add(ped2, IdlingModifier::Patrol, routine2);
			WAIT(1000);
			group->start();

			//Vector3 vehPos = playerPos + (forwardVec * 5);
			//Ped ped = createPed("g_m_y_uniexconfeds_01", vehPos);
			//Vector3 secPos = vehPos + forwardVec * 3;
			//Vector3 thirdPos = playerPos + forwardVec * -3;
			//Vector3 forthPos = playerPos + (getRightVector(player) * 4);
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
			//AI::OPEN_PATROL_ROUTE("miss_brob1_patrolLM02");
			//AI::ADD_PATROL_ROUTE_NODE(0, "WORLD_HUMAN_GUARD_SCOUT", secPos.x, secPos.y, secPos.z, 0, 0, 0, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(1000, 3000), 0);
			//AI::ADD_PATROL_ROUTE_NODE(1, "WORLD_HUMAN_SMOKE", thirdPos.x, thirdPos.y, thirdPos.z, 0, 0, 0, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(1000, 3000), 0);
			//AI::ADD_PATROL_ROUTE_NODE(2, "WORLD_HUMAN_SMOKE", forthPos.x, forthPos.y, forthPos.z, 0, 0, 0, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(1000, 3000), 0);
			//AI::ADD_PATROL_ROUTE_LINK(0, 1);
			//AI::ADD_PATROL_ROUTE_LINK(1, 2);
			//AI::ADD_PATROL_ROUTE_LINK(2, 0);
			//AI::CLOSE_PATROL_ROUTE();
			//AI::CREATE_PATROL_ROUTE();
			//pedEquipBestWeapon(ped);
			//AI::TASK_PATROL(ped, "miss_brob1_patrolLM02", 1, 1, 1);

			//PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
			//getGroundPos(vehPos, &vehPos);
			////Ped ped = createPed(F_LOWER_TOWN_FOLK, vehPos);
			//Entity ped = createProp("p_decapitated_head01x", vehPos);
			//Vector3 camPos = playerPos + (-3 * forwardVec  + 2 * getUpVector(player));
			////Vector3 camPos = playerPos + forwardVec;
			//GameCamera camera(camPos, 20);
			//camera.setIsActive(true);
			//camera.pointAt(ped);
			//GameCamera::setScriptCamsRendering(true);
			//WAIT(5000);
			//camera.destroy();
			//GameCamera::setScriptCamsRendering(false);
			/*RaycastResult ray = raycast(playerPos, forwardVec, 10);
			if (ray.didHit)
			{
				log(to_string(ENTITY::GET_ENTITY_HEADING(player)));
				log(ray.hitPos);
			}
			else
			{
				log("didnt hit");
			}*/
		}

		else if (IsKeyJustUp(VK_KEY_X))
		{
			Ped player = PLAYER::PLAYER_PED_ID();
			//Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			//float ground;
			//GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(playerPos.x, playerPos.y, playerPos.z, &ground, false);
			//std::stringstream output;
			//output << "\n"
			//	<< playerPos.x << ", " << playerPos.y << ", " << playerPos.z << "\n"
			//	<< playerPos.x << ", " << playerPos.y << ", " << ground << "\n"
			//	<< "heading: " << ENTITY::GET_ENTITY_HEADING(player);

			//log(output.str().c_str());


			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);
			Vector3 pos = playerPos + forwardVec * 4;
			Vector3 aimPos = pos + forwardVec * 100;
			Ped ped = createPed("g_m_y_uniexconfeds_01", pos);
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
			//AI::TASK_STAND_GUARD(ped, pos.x, pos.y, pos.z, 0, "WORLD_HUMAN_SMOKE");
			WAIT(2000);
			//pedEquipBestWeapon(ped);
			//PED::SET_PED_KEEP_TASK(ped, true);
			//AI::CLEAR_PED_TASKS(ped, 1, 1);
			//AI::_0xC4C32C31920E1B70(ped, player, playerPos.x, playerPos.y, playerPos.z, (Any*)"DEFAULT_SCARED", 10.0f, 10.0f, 0);
			Conversation conv;
			conv.addLine(ped, "GENERIC_CURSE_HIGH");
			conv.addDelay(500);
			conv.addLine(ped, "GET_SUSPECT_MALE");
			conv.addDelay(500);
			conv.addLine(ped, "COME_SEE_THIS");
			conv.addDelay(500);
			conv.addLine(ped, "CALLOUT_GET_FLEEING_MALE");
			conv.addDelay(500);
			conv.addLine(ped, "CALLOUT_EASY_PICKINGS_MALE");
			conv.addDelay(500);
			conv.addLine(ped, "CALL_FOR_SUPPORT");
			conv.play();
			//AI::TASK_AIM_GUN_AT_COORD(ped, aimPos.x, aimPos.y, aimPos.z, -1, 1, 1);
			temp = ped;
		}


		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}