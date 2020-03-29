#include "Main.h";

AndrewClarkExecutor::AndrewClarkExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(120);
	setRequiredDistanceToLocateTarget(15);
	setMustBeCloseToLocate(true);
	isTargetAlerted = false;
	isTargetScared = false;
	robberyProgress = RobberyProgress::NONE;
	threatPrompt = new Prompt("Where Is The Money?", 0x9FA5AD07);
	stash = NULL;
}

void AndrewClarkExecutor::update()
{
	BaseMissionExecutor::update();
	Ped player = PLAYER::PLAYER_PED_ID();

	if (distanceBetweenEntities(player, target) < 12 && !isTargetAlerted)
	{
		isTargetAlerted = true;
		AI::TASK_TURN_PED_TO_FACE_ENTITY(target, player, 3000, 0, 0, 0);
		playAmbientSpeech(target, "GET_LOST");
	}

	if (isTargetAlerted)
	{
		if (!isTargetScared && PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(PLAYER::PLAYER_ID(), target))
		{
			AI::TASK_HANDS_UP(target, -1, player, -1, 0);
			playAmbientSpeech(target, "WHOA");
			isTargetScared = true;
		}

		playTargetRobbery();
	}

	if (getMissionStage() == BountyMissionStage::ArriveToPoliceStation)
	{
		displayDebugText(to_string(distanceBetween(ENTITY::GET_ENTITY_COORDS(player, 1, 1), *(getArea()->policeDeptCoords))).c_str());
	}
}

Ped AndrewClarkExecutor::spawnTarget()
{
	Ped target = createPed("A_M_M_GriFancyTravellers_01", toVector3(-311.059, 1355.05, 158.291), 283.609);
	AUDIO::SET_AMBIENT_VOICE_NAME(target, "0971_a_m_m_roughtravellers_white_02");
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

	Vector3 stashPos = toVector3(-408.529, 1264.26, 159.21);
	stash = createProp("p_boxmeddeposit01x", stashPos, 141.608);
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
	AI::TASK_GO_TO_ENTITY(0, target, 10000, 5, 1, 0, 0);
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(player, seq);
}

void AndrewClarkExecutor::cleanup()
{
	BaseMissionExecutor::cleanup();

	vector<Object>::iterator propsItr;
	for (propsItr = campProps.begin(); propsItr != campProps.end(); propsItr++)
	{
		releaseEntitySafe(&(*propsItr));
	}

	releaseEntitySafe(&wagon);
}

void AndrewClarkExecutor::playTargetRobbery()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Conversation robberyInteraction;

	if (robberyProgress == RobberyProgress::NONE)
	{
		if (PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(PLAYER::PLAYER_ID(), target))
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
		robberyInteraction.addLine(player, "RE_AMD_LWL_V2_ROB_DEALERS");
		robberyInteraction.addLine(target, "RT_INTIMIDATED_ROB_NOT_INTIMIDATED");
		robberyInteraction.play();
		robberyProgress = RobberyProgress::WAITING_FOR_INTIMIDATION;
		threatPrompt->setText("Give Me The Money Or Else...");
	}
	else if (robberyProgress == RobberyProgress::WAITING_FOR_INTIMIDATION)
	{
		threatPrompt->show();

		if (threatPrompt->isActivatedByPlayer())
		{
			robberyInteraction.addLine(player, "ROB_AGAIN_THREATEN");
			robberyInteraction.addLine(target, "RT_NO_TIME_FOR_THIS");
			robberyInteraction.play();
		}

		if (PED::IS_PED_SHOOTING(player))
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
	AI::CLEAR_PED_TASKS(target, 1, 1);
	AI::TASK_GO_TO_ENTITY(target, stash, 30000, 0.3f, 2, 0, 0);
}

void AndrewClarkExecutor::spawnBountyHunters()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 enemiesSourcePos = getRandomPedPositionInRange(playerPos, 45);

	Ped horse1 = createPed("A_C_Horse_TennesseeWalker_DappleBay	", getRandomPedPositionInRange(enemiesSourcePos, 3));


	Ped horse2 = createPed("A_C_Horse_TennesseeWalker_DappleBay	", getRandomPedPositionInRange(enemiesSourcePos, 3));
}