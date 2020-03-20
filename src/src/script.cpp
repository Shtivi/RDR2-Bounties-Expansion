/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019
*/

#include "Main.h"

using namespace std;

void Initialize() 
{
	initializePrompts();
	initializeMapAreasCache();
	initializeBounties();
}

void main()
{
	Initialize();

	while (true)
	{
		updateMissions();

		if (IsKeyJustUp(VK_KEY_Z))
		{
			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);

			//Vector3 vehPos;
			//vehPos.x = playerPos.x + 8;
			//vehPos.y = playerPos.y + 4;
			//vehPos.z = playerPos.z;
			//GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(vehPos.x, vehPos.y, vehPos.z, &vehPos.z, false);
			//Vehicle veh = createVehicle(0x276DFE5E, vehPos);

			//Vector3 pedPos;
			//pedPos.x = playerPos.x + 2;
			//pedPos.y = playerPos.y + 2;
			//pedPos.z = playerPos.z;
			//Ped ped = createPed("RE_TORTURINGCAPTIVE_MALES_01", pedPos);
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
			////AI::_0x524B54361229154F(ped, GAMEPLAY::GET_HASH_KEY("PROP_HUMAN_SEAT_CHAIR_PLAY_KNIFE"), 10000, true, true, 10000, true);
			////PED::_0x4A48B6E03BABB4AC(ped, (Any*)"Aaron");
			////Blip blip = RADAR::_0x23F74C2FDA6E7C61(0x38CDE89D, ped); // Bounty target
			////RADAR::SET_BLIP_SPRITE(blip, 0x9E6FEC8F, true); // poster
			//ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped);
			//ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped2);

			//GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(pedPos.x, pedPos.y, pedPos.z, &pedPos.z, false);
			//OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("p_cs_cratetnt01x"), pedPos.x, pedPos.y, pedPos.z, true, true, true, 1, 1);

			//Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);
			//Vector3 startPos = add(&playerPos, &toVector3(0, 0, -0.8f));
			//RaycastResult ray = raycast(startPos, forwardVec, 10);
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
		if (IsKeyJustUp(VK_KEY_N))
		{
			mission->nextStage();
		}


		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}