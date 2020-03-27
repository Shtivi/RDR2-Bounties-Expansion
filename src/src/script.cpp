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

			//Vector3 vehPos;
			//vehPos.x = playerPos.x + 4;
			//vehPos.y = playerPos.y + 4;
			//vehPos.z = playerPos.z;
			//getGroundPos(vehPos, &vehPos);
			////createProp("P_CAMPFIRE05X", vehPos);
			//Ped horse = createPed("A_C_Horse_Turkoman_DarkBay", vehPos);
			//PED::_0xD3A7B003ED343FD9(horse, 0x8FFCF06B, true, false, false); // give saddle

			//Ped target = createPed("G_M_M_UniBanditos_01", toVector3(playerPos.x + 6, playerPos.y + 6, playerPos.z));
			////Ped target = createPedOnHorse("G_M_M_UniBanditos_01", horse);
			////PED::REGISTER_TARGET(target, player, 1);
			////WEAPON::GIVE_DELAYED_WEAPON_TO_PED(target, 0xA84762EC, 120, false, 0);


			//Object seq;
			//PED::_0xFE07FF6495D52E2A(target, 3, 0, 0);
			//AI::OPEN_SEQUENCE_TASK(&seq);
			//AI::_0x524B54361229154F(0, GAMEPLAY::GET_HASH_KEY("WORLD_HUMAN_SIT_GROUND"), 5000, true, true, 3, true);
			//AI::_0x92DB0739813C5186(0, horse, -1, -1, 2.0f, 1, 0, 0);
			////AI::TASK_AIM_GUN_AT_ENTITY(0, player, 3000, 1, 1);
			////AI::TASK_COMBAT_HATED_TARGETS_AROUND_PED(0, 15, 0, 0);
			////AI::TASK_COMBAT_PED(0, player, 0, 16);
			////AI::_0xFD45175A6DFD7CE9(0, player, 2, 0, -1.0f, -1, 0);
			//AI::_0xFD45175A6DFD7CE9(0, player, 4, 0, -999.0f, -1, 0); // FLEE
			//AI::CLOSE_SEQUENCE_TASK(seq);

			//Object horseSeq;
			//AI::OPEN_SEQUENCE_TASK(&horseSeq);
			//AI::TASK_STAND_STILL(0, 4000);
			//AI::_0xFD45175A6DFD7CE9(0, player, 3, 0, -6.0f, -1, 0); // FLEE
			//AI::CLOSE_SEQUENCE_TASK(horseSeq);

			//WAIT(1000);


			//WEAPON::SET_CURRENT_PED_WEAPON(target, WEAPON::GET_BEST_PED_WEAPON(target, 0, 0), true, 0, false, false);
			//AI::CLEAR_PED_TASKS(target, 0, 0);
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(target, 1);
			//AI::TASK_PERFORM_SEQUENCE(target, seq);

			//AI::CLEAR_PED_TASKS(horse, 1, 1);
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);
			//AI::TASK_PERFORM_SEQUENCE(horse, horseSeq);

			//AI::TASK_SMART_FLEE_PED(target, player, 2000, -1, 0, 0, 0);
			//PED::REGISTER_TARGET(target, player, 1);
			//AI::TASK_AIM_GUN_AT_ENTITY(target, player, 1000, 0, 0);
			//AI::TASK_COMBAT_HATED_TARGETS_AROUND_PED(target, 20, 0, 0);
			//s1 a;
			////a.f1 = 10000;
			//a.f2 = 10000;
			//a.f3 = 0;
			//a.f4 = 1;
			//
			//s2 b;
			//b.s = (char*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", "HELLO WORLD");

			//UIUNK::_0x049D5C615BD38BAD((Any*)&a, (Any*)&b, 1);

			//GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(vehPos.x, vehPos.y, vehPos.z, &vehPos.z, false);
			//Vehicle veh = createVehicle(0x276DFE5E, vehPos);

			//Vector3 pedPos;
			//pedPos.x = playerPos.x + 2;
			//pedPos.y = playerPos.y + 2;
			//pedPos.z = playerPos.z;
			//Ped ped = createPed("G_M_M_UniBanditos_01", pedPos);
			//PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);

			//Vector3 pedPos2;
			//pedPos2.x = playerPos.x + 6;
			//pedPos2.y = playerPos.y + 6;
			//pedPos2.z = playerPos.z;
			//Ped ped2 = createPed(SKINNER_BROTHER_MODEL, pedPos2);
			//WEAPON::REMOVE_ALL_PED_WEAPONS(ped2, true, 0);
			////WEAPON::_0x5E3BDDBCB83F3D84(ped2, 0x28950C71, 10, false, false, 1, false, 1056964608, 1065353216, false, 1, false, false);
			//WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped2, 0x28950C71, 0, true, 0);
			////PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped2, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
			//PED::REGISTER_TARGET(ped2, ped, false);

			//WAIT(1000);
			//Object seq;
			//AI::OPEN_SEQUENCE_TASK(&seq);
			//AI::TASK_TURN_PED_TO_FACE_ENTITY(0, ped, 2000, 0, 0, 0);
			////AI::TASK_COMBAT_HATED_TARGETS_AROUND_PED(0, 8, 0, 0);
			//AI::TASK_COMBAT_PED(0, ped, 0, 16);
			//AI::_0x502EC17B1BED4BFA(0, ped);
			////AI::_0x6D3D87C57B3D52C7(0, ped, veh, 2000);
			//AI::CLOSE_SEQUENCE_TASK(seq);

			//AI::CLEAR_PED_TASKS(ped2, true, true);
			//PED::SET_PED_KEEP_TASK(ped2, true);
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped2, true);
			//AI::TASK_PERFORM_SEQUENCE(ped2, seq);

			////PED::SET_PED_KEEP_TASK(ped, true);
			//////AI::_0x524B54361229154F(ped, GAMEPLAY::GET_HASH_KEY("PROP_HUMAN_SEAT_CHAIR_PLAY_KNIFE"), 10000, true, true, 10000, true);
			////PED::_0x4A48B6E03BABB4AC(ped, (Any*)"Aaron");
			////Blip blip = RADAR::_0x23F74C2FDA6E7C61(0x38CDE89D, ped); // Bounty target
			////RADAR::SET_BLIP_SPRITE(blip, 0x9E6FEC8F, true); // poster
			//ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped);
			//ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped2);

			//GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(pedPos.x, pedPos.y, pedPos.z, &pedPos.z, false);
			//OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("p_cs_cratetnt01x"), pedPos.x, pedPos.y, pedPos.z, true, true, true, 1, 1);

			//Vector3 startPos = add(&playerPos, &toVector3(0, 0, -0.8f));
			//if (ray.didHit)
			//{
			//	log(ray.hitPos);
			//	//Vector3 topPos = add(&add(&ray.hitPos, &multiply(&forwardVec, 0.5f), &toVector3(0, 0, 10));
			//	ray = raycast(topPos, toVector3(0, 0, -1), 10);

			//	//Vector3 bill = add(&playerPos, &multiply(&forwardVec, 3.0f));
			//	Vector3 bill = ray.hitPos;
			//	//getGroundPos(ray, &bill);
			//	log(bill);
			//	//createProp("p_cs_billstack01x", bill);
			//	OBJECT::CREATE_PICKUP(0xFE18F3AF, bill.x, bill.y, bill.z, 0, 1000, 0, 0, 0, 0);
			//}
			//else
			//{
			//	log("didnt hit");
			//}

			Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);
			RaycastResult ray = raycast(playerPos, forwardVec, 10);
			if (ray.didHit)
			{
				log(to_string(ENTITY::GET_ENTITY_HEADING(player)));
				log(ray.hitPos);
			}
			

		}
		else if (IsKeyJustUp(VK_KEY_X))
		{
			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			float ground;
			GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(playerPos.x, playerPos.y, playerPos.z, &ground, false);

			std::stringstream output;
			output << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << "\n"
				   << playerPos.x << ", " << playerPos.y << ", " << ground << "\n";

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