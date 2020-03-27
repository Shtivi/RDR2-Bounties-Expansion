/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019
*/

#include "Main.h"

using namespace std;


struct s1 {
	//int f1;
	int f2;
	bool f3;
	bool f4;
};

struct s2
{
	char* s;
};


ModProgress* modProgress;
MapAreasManager* areasMgr;
BountyMissionsFactory* missionsFactory;
BountiesManager* bountiesMgr;

void initialize()
{
	initializeLogger();
	modProgress = new ModProgress("BountiesExpansion.dat");
	areasMgr = new MapAreasManager();
	missionsFactory = new BountyMissionsFactory(areasMgr);
	log("initializing bounties manager");
	bountiesMgr = new BountiesManager(modProgress, areasMgr, missionsFactory);
	initializeUI();
	log("initialization completed");
}

void main()
{
	initialize();

	while (true)
	{
		bountiesMgr->update();
		menu->update();

		//autosaveModProgress(modProgress);

		if (IsKeyJustUp(VK_KEY_Z))
		{
			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);

			Vector3 vehPos = toVector3(playerPos.x + forwardVec.x * 4, playerPos.y + forwardVec.y * 4, playerPos.z);
			GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(vehPos.x, vehPos.y, vehPos.z, &vehPos.z, false);
			Vehicle veh = createVehicle(0xB31F8075, vehPos);
			Vector3 vehForVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(veh);
			Ped enemy = createPed("g_m_y_uniexconfeds_01", toVector3(vehPos.x + 4, vehPos.y + 4, vehPos.z));
			Ped victim = createPed("RE_RALLYSETUP_MALES_01", toVector3(vehPos.x - vehForVec.x * 6, vehPos.y - vehForVec.y * 6, vehPos.z));
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(enemy, true);
			AI::CLEAR_PED_TASKS(enemy, 1, 1);
;			WAIT(2000);
			int seat = -2;
			VEHICLE::_0xFF5791B7639C2A46(veh, (Any*)&seat);
			Object seq;
			AI::OPEN_SEQUENCE_TASK(&seq);
			AI::TASK_ENTER_VEHICLE(0, veh, 20000, -1, 2, 1, 0);
			AI::_0xFD45175A6DFD7CE9(0, player, 3, 0, -999.0f, -1, 0); // FLEE
			AI::CLOSE_SEQUENCE_TASK(seq);
			AI::TASK_PERFORM_SEQUENCE(enemy, seq);

			//s1 a;
			////a.f1 = 10000;
			//a.f2 = 10000;
			//a.f3 = 0;
			//a.f4 = 1;
			//
			//s2 b;
			//b.s = (char*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", "HELLO WORLD");
			//UIUNK::_0x049D5C615BD38BAD((Any*)&a, (Any*)&b, 1);

			//GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(pedPos.x, pedPos.y, pedPos.z, &pedPos.z, false);
			//OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("p_cs_cratetnt01x"), pedPos.x, pedPos.y, pedPos.z, true, true, true, 1, 1);

			//RaycastResult ray = raycast(playerPos, forwardVec, 10);
			//if (ray.didHit)
			//{
			//	log(to_string(ENTITY::GET_ENTITY_HEADING(player)), "positions.txt");
			//	log(ray.hitPos);
			//}
			//else
			//{
			//	log("didnt hit");
			//}
			

		}
		else if (IsKeyJustUp(VK_KEY_X))
		{
			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			float ground;
			GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(playerPos.x, playerPos.y, playerPos.z, &ground, false);

			std::stringstream output;
			output << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << "\n"
				<< playerPos.x << ", " << playerPos.y << ", " << ground << "\n"
				<< "heading: " << ENTITY::GET_ENTITY_HEADING(player);

			log(output.str().c_str());
		}

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}