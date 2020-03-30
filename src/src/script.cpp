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

		if (IsKeyJustUp(VK_KEY_Z))
		{

			Ped player = PLAYER::PLAYER_PED_ID();
			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);

			Vector3 vehPos = add(&playerPos, &(multiply(&forwardVec, 3)));
			getGroundPos(vehPos, &vehPos);

			Ped target = createPed("A_M_M_GriFancyTravellers_01", vehPos);
			AUDIO::SET_AMBIENT_VOICE_NAME(target, "0974_A_M_M_ROUGHTRAVELLERS_WHITE_05");
			PED::SET_PED_RELATIONSHIP_GROUP_HASH(target, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(target, true);
			Conversation conv;
			//conv.addLine(player, "RE_AMD_LWL_V2_ROB_DEALERS");
			//conv.addLine(target, "INTIMIDATED_ROB");
			//conv.addLine(player, "ROB_THREATEN");
			//conv.addLine(target, "RT_INTIMIDATED_ROB_NOT_INTIMIDATED");
			//conv.addLine(player, "ROB_AGAIN_REJECT_OFFER");
			//conv.addLine(target, "HAND_OVER_MONEY");
			//conv.addDelay(1000);
			//conv.addLine(player, "ROB_AGAIN_REJECT_OFFER");
			conv.addLine(target, "FINAL_WARNING");
			conv.addDelay(500);
			conv.addLine(target, "GENERIC_INSULT_HIGH_NEUTRAL");
			conv.addDelay(500);
			conv.addLine(target, "GENERIC_FRIGHTENED_HIGH");
			conv.addDelay(500);
			conv.addLine(target, "PLEAD_HOGTIED");
			WAIT(1000);
			conv.play();

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