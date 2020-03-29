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

		//autosaveModProgress(modProgress);

		if (IsKeyJustUp(VK_KEY_Z))
		{
			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);

			Vector3 vehPos = add(&playerPos, &(multiply(&forwardVec, 3)));
			getGroundPos(vehPos, &vehPos);

			//setVehicleCargo(createVehicle(VehicleHash::Wagon02X, vehPos), VehicleCargoHash::CampCargo1);

			//Ped target = createPed("A_M_M_GriFancyTravellers_01", vehPos);
			//PED::_0x4A48B6E03BABB4AC(target, (Any*)"Sheep"); // Set ped name
			//AUDIO::SET_AMBIENT_VOICE_NAME(target, "0044_A_M_M_BYNROUGHTRAVELLERS_01_WHITE_01");
			//PED::SET_PED_RELATIONSHIP_GROUP_HASH(target, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(target, true);
			//AI::TASK_HANDS_UP(target, -1, player, -1, 0);


			//playAmbientSpeech(player, "ROB_AGAIN_THREATEN");

			//Ped horse = createPed("A_C_Horse_Morgan_BayRoan", toVector3(-308.29, 1359.79, 157.94), 139.169);
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(horse, true);

			//Vector3 propPos = add(&playerPos, &(multiply(&forwardVec, 3)));
			//getGroundPos(propPos, &propPos);
			//Object chest = createProp("p_boxmeddeposit01x", propPos);
			//createProp("p_moneystack01x", propPos);
			//createProp("p_moneystack01x", propPos);

			//Object box = createProp("s_lootablemoneybox", propPos);
			//float heading = 90 + ENTITY::GET_ENTITY_HEADING(box);
			//createProp("p_foldedbills01x", propPos, heading);
			//createProp("p_moneystack01x", propPos, heading);
			//Object obj = OBJECT::CREATE_PICKUP(0xFE18F3AF, propPos.x, propPos.y, propPos.z, 0, 100, 0, GAMEPLAY::GET_HASH_KEY("p_foldedbills01x"), -1, 2);

			/*char* modelName = "p_moneystack02x";
			Hash model = GAMEPLAY::GET_HASH_KEY(modelName);
			STREAMING::REQUEST_MODEL(model, false);
			while (!STREAMING::HAS_MODEL_LOADED(model))
			{
				WAIT(0);
			}

			Object obj = OBJECT::CREATE_PICKUP(0xFE18F3AF, propPos.x, propPos.y, propPos.z + 0.08, 0, 100, 0, model, -1, 2);
			OBJECT::PLACE_OBJECT_ON_GROUND_PROPERLY(obj, true);*/
			//createProp("p_moneystack02x", propPos);
			//OBJECT::CREATE_PICKUP(0xFE18F3AF, propPos.x, propPos.y, propPos.z, 0, 100, 0, GAMEPLAY::GET_HASH_KEY("p_foldedbills01x"), -1, 2);
			//createProp("p_moneystack01x", propPos);
			//createProp("p_safe_ser", propPos);


			//RaycastResult ray = raycast(playerPos, forwardVec, 10);
			//if (ray.didHit)
			//{
			//	log(to_string(ENTITY::GET_ENTITY_HEADING(player)));
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
			output << "\n" 
				<< playerPos.x << ", " << playerPos.y << ", " << playerPos.z << "\n"
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