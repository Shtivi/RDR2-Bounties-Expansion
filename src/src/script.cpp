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

			/*Vector3 vehPos = add(&playerPos, &(multiply(&forwardVec, 6)));
			getGroundPos(vehPos, &vehPos);
			createVehicle(0xAAFEA8AE, vehPos);*/

			Vector3 propPos = add(&playerPos, &(multiply(&forwardVec, 3)));
			getGroundPos(propPos, &propPos);

			showHelpMessage("Hello World");
			createProp("s_canapricots01x", propPos);
			//createProp("s_agedpiraterum01x", propPos);

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