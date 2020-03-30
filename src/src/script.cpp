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

GameStopwatch* stopwatch;

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

	stopwatch = new GameStopwatch();
	stopwatch->start();

	while (true)
	{
		bountiesMgr->update();
		menu->update();
		printHelpMessage();

		if (IsKeyJustUp(VK_KEY_Z))
		{

			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);

			Vector3 vehPos = add(&playerPos, &(multiply(&forwardVec, 3)));
			getGroundPos(vehPos, &vehPos);
			
			Vector3 pos2 = add(&playerPos, &(multiply(&forwardVec, 10)));
			getGroundPos(&pos2);

			//Ped target = createPed("A_C_Bear_01", pos2);
			//giveWeaponToPed(target, WeaponHash::MeleeMachete, 0, true);
			Ped ped = createPed(F_LOWER_TOWN_FOLK, vehPos);
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(target, 1);
			WAIT(1000);
			AI::_0x779A2FFACEFAEA7B(ped, player, 0, 1, 3.0f, 1, 0);
			//AI::_0x779A2FFACEFAEA7B(target, ped, -754963320, 1, 2.0f, 1, 0);
			WAIT(10000);
			//ENTITY::SET_ENTITY_HEALTH(target, 0, 0);
			/*AUDIO::SET_AMBIENT_VOICE_NAME(target, "1021_G_M_M_UNIBANDITOS_01_HISPANIC_03");
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(target, 1);
			Conversation conv;
			conv.addLine(target, "GET_LOST");
			conv.addDelay(500);
			conv.addLine(target, "FINAL_WARNING");
			conv.addDelay(1000);
			conv.addLine(target, "ITS_MALE_EXTREME");
			WAIT(1000);
			pedEquipBestWeapon(target);
			AI::TASK_AIM_GUN_AT_ENTITY(target, player, 90000, 0, 0);
			conv.play();
			PED::EXPLODE_PED_HEAD(target, WeaponHash::ShotgunDoublebarrel);*/

			//Vector3 pedPos = getRandomPositionInRange(playerPos, 6);
			//Vector3 realPos;
			//if (!PATHFIND::GET_SAFE_COORD_FOR_PED(pedPos.x, pedPos.y, pedPos.z, true, &realPos, 16))
			//{
			//	Ped ped = createPed("G_M_M_BountyHunters_01", pedPos);
			//	AUDIO::SET_AMBIENT_VOICE_NAME(ped, "0740_G_M_M_BOUNTYHUNTERS_01_WHITE_02");
			//	playAmbientSpeech(ped, "ITS_THEM_EXTREME");
			//}
			//else
			//{
			//	showSubtitle("wasnt found");
			//}

			//Vector3 enemiesSourcePos = getRandomPedPositionInRange(playerPos, 45);

			//Ped horse1 = createPed("A_C_Horse_TennesseeWalker_DappleBay", getRandomPedPositionInRange(enemiesSourcePos, 3));
			//Ped horse2 = createPed("A_C_Horse_TennesseeWalker_DappleBay", getRandomPedPositionInRange(enemiesSourcePos, 3));
			//giveSaddleToHorse(horse1, HorseSaddleHashes::MCCLELLAN_01_STOCK_NEW_SADDLE_004);
			//giveSaddleToHorse(horse2, HorseSaddleHashes::MCCLELLAN_01_STOCK_NEW_SADDLE_002);

			//vector<Ped> bountyHunters;
			//Ped driver1 = createPedOnHorse("G_M_M_BountyHunters_01", horse1, -1);
			//Ped driver2 = createPedOnHorse("G_M_M_BountyHunters_01", horse2, -1);
			//bountyHunters.push_back(createPedOnHorse("G_M_M_BountyHunters_01", horse1, 0));
			//bountyHunters.push_back(driver1);
			//bountyHunters.push_back(driver2);

			//vector<Ped>::iterator pedItr;
			//for (pedItr = bountyHunters.begin(); pedItr != bountyHunters.end(); pedItr++)
			//{
			//	Ped curr = *pedItr;
			//	createBlip(curr, BLIP_STYLE_ENEMY);
			//	giveWeaponToPed(curr, WeaponHash::RepeaterCarbine, 60);
			//	pedEquipBestWeapon(curr);
			//	AI::TASK_COMBAT_PED(curr, player, 0, 16);
			//}

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