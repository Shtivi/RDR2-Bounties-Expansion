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
		printHelpMessage();

		if (IsKeyJustUp(VK_KEY_Z))
		{
			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			bountiesMgr->resetMissions(MapAreas::Rhodes);
			//Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);
			//Vector3 vehPos = add(&playerPos, &(multiply(&forwardVec, 5)));
			//Ped ped = createPed(F_LOWER_TOWN_FOLK, vehPos);
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
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