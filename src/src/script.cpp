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
		//printHelpMessage();

		//if (IsKeyJustUp(VK_KEY_Z))
		//{

		//	Ped player = PLAYER::PLAYER_PED_ID();
		//	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
		//	Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);

		//	Vector3 vehPos = add(&playerPos, &(multiply(&forwardVec, 3)));
		//	getGroundPos(vehPos, &vehPos);

		//	RaycastResult ray = raycast(playerPos, forwardVec, 10);
		//	if (ray.didHit)
		//	{
		//		log(to_string(ENTITY::GET_ENTITY_HEADING(player)));
		//		log(ray.hitPos);
		//	}
		//	else
		//	{
		//		log("didnt hit");
		//	}
		//}
		//else if (IsKeyJustUp(VK_KEY_X))
		//{
		//	Ped player = PLAYER::PLAYER_PED_ID();
		//	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
		//	float ground;
		//	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(playerPos.x, playerPos.y, playerPos.z, &ground, false);

		//	std::stringstream output;
		//	output << "\n"
		//		<< playerPos.x << ", " << playerPos.y << ", " << playerPos.z << "\n"
		//		<< playerPos.x << ", " << playerPos.y << ", " << ground << "\n"
		//		<< "heading: " << ENTITY::GET_ENTITY_HEADING(player);

		//	log(output.str().c_str());
		//}


		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}