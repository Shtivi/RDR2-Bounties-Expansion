#include "Main.h";

const char ROBBERY_HINT[] = "Hint: Andrew was found guilty of stealing money from the bank he had been working for...";
const char ROBBERY_ESCALATE_HINT[] = "Try to make Andrew understand that you're serious.";
const int OFFSET_FROM_TARGET = 4;
const int ROBBERY_DISTANCE = OFFSET_FROM_TARGET + 2;

AndrewClarkExecutor::AndrewClarkExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(120);
	setRequiredDistanceToLocateTarget(15);
	setMustBeCloseToLocate(true);
	isTargetAlerted = false;
	isTargetScared = false;
	spawnedBountyHunters = false;
	robberyAttempts = 0;
	robberyProgress = RobberyProgress::NONE;
	threatPrompt = new Prompt("Where Is The Money?", 0x9FA5AD07);
	stash = NULL;
}

void AndrewClarkExecutor::update()
{
	BaseMissionExecutor::update();
	Ped player = PLAYER::PLAYER_PED_ID();

	if (getMissionStage() >= BountyMissionStage::LocateTarget)
	{
		if (distanceBetweenEntities(player, target) < 12 && !isTargetAlerted)
		{
			isTargetAlerted = true;
			PED::_0xFE07FF6495D52E2A(target, 0, 0, 0);
			WAIT(500);
			AI::TASK_TURN_PED_TO_FACE_ENTITY(target, player, -1, 0, 0, 0);
			playAmbientSpeech(target, "GET_LOST");
		}

		if (isTargetAlerted)
		{
			Hash playerCurrWeapon;
			WEAPON::GET_CURRENT_PED_WEAPON(player, &playerCurrWeapon, true, 0, false);

			if (getMissionStage() == BountyMissionStage::CaptureTarget && playerCurrWeapon != GAMEPLAY::GET_HASH_KEY("WEAPON_LASSO"))
			{
				playTargetRobbery();
			}
			else
			{
				threatPrompt->hide();
			}
		}
	}

	if (getMissionStage() == BountyMissionStage::ArriveToPoliceStation)
	{
		float distanceToPolice = distanceBetween(ENTITY::GET_ENTITY_COORDS(player, 1, 1), *(getArea()->policeDeptCoords));
		if (distanceToPolice < 220 && !spawnedBountyHunters)
		{
			spawnBountyHunters();
			spawnedBountyHunters = true;
		}
	}
}

Ped AndrewClarkExecutor::spawnTarget()
{
	Ped target = createPed("A_M_M_GriFancyTravellers_01", toVector3(-311.059, 1355.05, 158.291), 283.609);
	AUDIO::SET_AMBIENT_VOICE_NAME(target, "0974_A_M_M_ROUGHTRAVELLERS_WHITE_05");
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(target, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(target, true);
	return target;
}

void AndrewClarkExecutor::prepareSet()
{	
	wagon = createVehicle(VehicleHash::Wagon02X, toVector3(-310.107, 1360.19, 158.084), 94.2345);
	setVehicleCargo(wagon, VehicleCargoHash::CampCargo1);

	Object campfire = createProp("p_campfire05x", toVector3(-308.143, 1355.59, 158.132));
	campProps.push_back(campfire);

	float tentHeading = 193.621;
	Vector3 tentPos = toVector3(-307.686, 1351.84, 158.326);
	campProps.push_back(createProp("p_amb_tent01x", tentPos, tentHeading));
	campProps.push_back(createProp("p_bedrollopen03x", tentPos, tentHeading));

	/*Vector3 stashPos = toVector3(-408.529, 1264.26, 159.21);
	stash = createProp("p_boxmeddeposit01x", stashPos, 141.608);*/
	Vector3 stashPos = toVector3(-345.296, 1362.1, 158.634);
	stash = createProp("p_boxmeddeposit01x", stashPos, 335.257);
	campProps.push_back(stash);
	campProps.push_back(createProp("p_moneystack01x", stashPos));
	campProps.push_back(createProp("p_moneystack01x", stashPos));

	AI::_0x524B54361229154F(target, GAMEPLAY::GET_HASH_KEY("WORLD_HUMAN_SIT_GROUND"), -1, true, true, 0, true);
}

void AndrewClarkExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
	Ped player = PLAYER::PLAYER_PED_ID();

	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	if (PED::IS_PED_ON_MOUNT(player))
	{
		AI::_0x48E92D3DDE23C23A(0, PED::GET_MOUNT(player), 0, 0, 0, 0);
	}
	else if (PED::IS_PED_ON_VEHICLE(player, 0))
	{
		AI::TASK_LEAVE_ANY_VEHICLE(0, 0, 0);
	}
	AI::TASK_GO_TO_ENTITY(0, target, 10000, OFFSET_FROM_TARGET, 1, 0, 0);
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(player, seq);

	setHelpMessage(ROBBERY_HINT);
}

void AndrewClarkExecutor::cleanup()
{
	BaseMissionExecutor::cleanup();
	releaseEntitySafe(&wagon);

	vector<Object>::iterator propsItr;
	for (propsItr = campProps.begin(); propsItr != campProps.end(); propsItr++)
	{
		releaseEntitySafe(&(*propsItr));
	}

	vector<Ped>::iterator pedItr;
	for (pedItr = horses.begin(); pedItr != horses.end(); pedItr++)
	{
		releaseEntitySafe(&(*pedItr));
	}

	for (pedItr = bountyHunters.begin(); pedItr != bountyHunters.end(); pedItr++)
	{
		releaseEntitySafe(&(*pedItr));
	}
}

void AndrewClarkExecutor::playTargetRobbery()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Conversation robberyInteraction;

	if (robberyProgress == RobberyProgress::NONE)
	{
		if (distanceBetweenEntities(player, target) < OFFSET_FROM_TARGET)
		{
			threatPrompt->show();
		}
		else
		{
			threatPrompt->hide();
		}

		if (threatPrompt->isActivatedByPlayer())
		{
			robberyProgress = RobberyProgress::TARGET_RESISTING;
			threatPrompt->hide();
		}
	}
	else if (robberyProgress == RobberyProgress::TARGET_RESISTING)
	{
		// conv.addLine(player, "RE_GP_MNT_V2_GREET_ROB_POST");
		robberyInteraction.addLine(new RobberyAimAtVictim(player, target));
		robberyInteraction.addLine(target, "WHOA");
		robberyInteraction.addLine(player, "RE_AMD_LWL_V2_ROB_DEALERS");
		robberyInteraction.addLine(target, "INTIMIDATED_ROB");
		robberyInteraction.play();
		robberyProgress = RobberyProgress::WAITING_FOR_INTIMIDATION;
		robberyAttempts = 0;
	}
	else if (robberyProgress == RobberyProgress::WAITING_FOR_INTIMIDATION)
	{
		threatPrompt->setText("Give Me The Money Or Else...");
		threatPrompt->show();

		if (threatPrompt->isActivatedByPlayer())
		{
			robberyAttempts++;
			threatPrompt->hide();
			if (robberyAttempts == 1)
			{
				robberyInteraction.addLine(player, "ROB_THREATEN");
				robberyInteraction.addLine(target, "RT_INTIMIDATED_ROB_NOT_INTIMIDATED");
			}
			else
			{
				robberyInteraction.play();robberyInteraction.addLine(player, "ROB_AGAIN_THREATEN");
				robberyInteraction.addLine(target, "STOP_THAT");
			}
			robberyInteraction.play();
			threatPrompt->show();

			if (robberyAttempts > 2)
			{
				setHelpMessage(ROBBERY_ESCALATE_HINT);
			}
		}

		if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(target, player, 0, 0))
		{
			robberyProgress = RobberyProgress::TARGET_GAVE_UP;
		}
	}
	else if (robberyProgress == RobberyProgress::TARGET_GAVE_UP)
	{
		if (threatPrompt->isActivatedByPlayer())
		{
			threatPrompt->hide();
			robberyInteraction.addLine(player, "ROB_PULL_GUN");
			robberyInteraction.addLine(target, "HAND_OVER_MONEY");
			robberyInteraction.play();
			goToStash();
			robberyProgress = RobberyProgress::FINISHED;
		}
	}
}

void AndrewClarkExecutor::goToStash()
{
	if (ENTITY::IS_ENTITY_DEAD(target))
	{
		return;
	}

	string msg = string("Follow ").append(getMissionData()->targetName).append(" to the stash.");
	showSubtitle(msg.c_str());
	
	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_GO_TO_ENTITY(0, stash, 30000, 0.3f, 2, 0, 0);
	AI::TASK_TURN_PED_TO_FACE_ENTITY(0, stash, 6000, 0, 0, 0);
	AI::_0xFD45175A6DFD7CE9(0, PLAYER::PLAYER_PED_ID(), 3, 0, -999.0f, -1, 0); // FLEE
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::CLEAR_PED_TASKS(target, 1, 1);
	AI::TASK_PERFORM_SEQUENCE(target, seq);
}

void AndrewClarkExecutor::spawnBountyHunters()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 enemiesSourcePos = getRandomPedPositionInRange(playerPos, 60);
	log(playerPos);
	log(enemiesSourcePos);

	Ped horse1 = createPed("A_C_Horse_TennesseeWalker_DappleBay", getRandomPedPositionInRange(playerPos, 60));
	Ped horse2 = createPed("A_C_Horse_TennesseeWalker_DappleBay", getRandomPedPositionInRange(playerPos, 60));
	horses.push_back(horse1);
	horses.push_back(horse2);
	giveSaddleToHorse(horse1, HorseSaddleHashes::MCCLELLAN_01_STOCK_NEW_SADDLE_004);
	giveSaddleToHorse(horse2, HorseSaddleHashes::MCCLELLAN_01_STOCK_NEW_SADDLE_002);

	addBountyHunter(horse1, true);
	addBountyHunter(horse1, false);
	addBountyHunter(horse2, true);
	WAIT(1000);

	vector<Ped>::iterator pedItr;
	for (pedItr = bountyHunters.begin(); pedItr != bountyHunters.end(); pedItr++)
	{
		Ped curr = *pedItr;
		AI::TASK_COMBAT_PED(curr, player, 0, 16);
	}
}

void AndrewClarkExecutor::addBountyHunter(Ped horse, bool isDriver)
{
	Ped bh = createPedOnHorse("G_M_M_BountyHunters_01", horse, isDriver ? -1 : 0);
	bountyHunters.push_back(bh);
	createBlip(bh, BLIP_STYLE_ENEMY);
	pedEquipBestWeapon(bh);
}