#include "Main.h"

const char BOUNTY_COMPLETED[] = "Bounty completed!";

BaseMissionExecutor::BaseMissionExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
{
	this->areasMgr = areasMgr;
	this->missionData = new BountyMissionData(missionData);
	this->stage = BountyMissionStage::MissionInitialization;
	this->status = BountyMissionStatus::Unavailable;

	inspectPosterPrompt = new Prompt("Inspect bounty", GAMEPLAY::GET_HASH_KEY("INPUT_MERCY_KILL"), SemiHold);
	inspectPosterPrompt->hide();
	setTargetAreaRadius(AREA_RADIUS);
	setRequiredDistanceToLocateTarget(REQUIRED_DIST_TO_LOCATE);
	setMustBeCloseToLocate(false);

	poster = NULL;
	posterBlip = NULL;
	targetAreaBlip = NULL;
	target = NULL;
	policeLocBlip = NULL;
}

BountyMissionData* BaseMissionExecutor::getMissionData()
{
	return missionData;
}

BountyMissionStage BaseMissionExecutor::getMissionStage()
{
	return stage;
}

BountyMissionStatus BaseMissionExecutor::getMissionStatus()
{
	return status;
}

void BaseMissionExecutor::setMissionStatus(BountyMissionStatus status)
{
	this->status = status;

	switch (status)
	{
	case BountyMissionStatus::Pending:
		stage = BountyMissionStage::MissionInitialization;
		break;

	case BountyMissionStatus::CollectedPoster:
		stage = BountyMissionStage::GoToArea;
		onPosterCollected();
		break;

	case BountyMissionStatus::Completed:
		stage = BountyMissionStage::Finished;
		onFinished(false);
		break;
	}
}

void BaseMissionExecutor::update()
{
	if (GAMEPLAY::GET_MISSION_FLAG())
	{
		if (RADAR::DOES_BLIP_EXIST(posterBlip) || RADAR::DOES_BLIP_EXIST(targetAreaBlip) || stage == BountyMissionStage::CaptureTarget)
		{
			if (stage == BountyMissionStage::CaptureTarget)
			{
				cleanup();
				stage = BountyMissionStage::GoToArea;
			}
			deleteBlipSafe(&posterBlip);
			deleteBlipSafe(&targetAreaBlip);
			stopped = true;
		}
	}
	else
	{
		if (stopped == true)
		{
			if (stage == BountyMissionStage::CollectPoster)
			{
				posterBlip = createBlip(poster, 0xB04092F8, -1636832113);
				setBlipLabel(posterBlip, "Bounty Poster");
			}
			else if (stage == BountyMissionStage::GoToArea)
			{
				targetAreaBlip = createBlip(missionData->startPosition, targetAreaRadius, 0xB04092F8, -907204276 /* Bounty sprite */);
				const char* condition = missionData->requiredTargetCondition == TargetCondition::Alive ? "Alive" : "Dead or Alive";
				std::stringstream label;
				label << "Bounty Hunting: "
					<< missionData->targetName << ", "
					<< missionData->reward << "$, "
					<< condition;
				setBlipLabel(targetAreaBlip, label.str().c_str());
			}
			stopped = false;
		}
		Ped player = PLAYER::PLAYER_PED_ID();
		Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);
		float distanceToPolice = distanceBetween(ENTITY::GET_ENTITY_COORDS(player, 1, 1), *(getArea()->policeDeptCoords));
		Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(target, true, false);
		releaseUnnecessaryEntities();

		//if (IsKeyJustUp(VK_KEY_N))
		//{
		//	nextStage();
		//	if (stage == BountyMissionStage::CaptureTarget)
		//	{
		//		if (missionData->requiredTargetCondition == TargetCondition::Alive)
		//		{
		//			//ENTITY::SET_ENTITY_COORDS(target, getArea()->cellCoords->x, getArea()->cellCoords->y, getArea()->cellCoords->z, 0, 0, 0, 0);
		//			ENTITY::SET_ENTITY_COORDS(target, playerPos.x, playerPos.y, playerPos.z, 0, 0, 0, 0);
		//		}
		//		else
		//		{
		//			ENTITY::SET_ENTITY_HEALTH(target, 0, 0);
		//		}
		//	}
		//}

		switch (stage)
		{
		case BountyMissionStage::MissionInitialization:
			initialize();
			seen = false;
			nextStage();
			break;

		case BountyMissionStage::CollectPoster:
			if (distanceBetween(playerPos, *getArea()->bountyPostersCoords) <= 3.0f &&
				PED::IS_PED_ON_FOOT(player))
			{
				inspectPosterPrompt->show();

				if (inspectPosterPrompt->isActivatedByPlayer())
				{
					nextStage();
				}
			}
			else
			{
				inspectPosterPrompt->hide();
			}
			break;

		case BountyMissionStage::GoToArea:
			if (distanceBetween(playerPos, missionData->startPosition) <= targetAreaRadius)
			{
				nextStage();
			}
			break;

		case BountyMissionStage::LocateTarget:
			if (mustBeCloseToLocate)
			{
				if (distanceBetweenEntities(player, target) <= requiredDistanceToLocate)
				{
					nextStage();
				}
			}
			else if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(player, target, 1))
			{
				nextStage();
			}
			if (distanceBetween(playerPos, missionData->startPosition) > targetAreaRadius)
			{
				cleanup();
				stage = BountyMissionStage::GoToArea;
			}
			break;

		case BountyMissionStage::CaptureTarget:
			if (isPedHogtied(target) ||
				(missionData->requiredTargetCondition == TargetCondition::DeadOrAlive && ENTITY::IS_ENTITY_DEAD(target)))
			{
				spawnedBountyHunters = false;
				spawnchance = rand() % 2 + 1;
				nextStage();
			}
			if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(player, target, 1) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(target, player, 1) && seen == false)
			{
				deleteBlipSafe(&targetBlip);
				targetBlip = createBlip(target, BLIP_TYPE_BOUNTY_TARGET, BLIP_SPRITE_BOUNTY_TARGET);
				seen = true;
			}
			break;

		case BountyMissionStage::ArriveToPoliceStation:
			if (distanceBetween(playerPos, missionData->startPosition) > 250 && spawnchance == 1 && !spawnedBountyHunters && missionData->area != MapAreas::Armadillo)
			{
				spawnBountyHunters();
			}
			if (distanceBetween(targetPos, *getArea()->policeDeptCoords) < 20)
			{
				nextStage();
			}
			break;

		case BountyMissionStage::HandOverTarget:
			if (distanceBetween(targetPos, *getArea()->cellCoords) < 3 &&
				ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(target) <= 1.1)
			{
				nextStage();
			}
			break;

		case BountyMissionStage::CollectReward:
			nextStage();
			break;

		}
		if (ENTITY::IS_ENTITY_DEAD(target) && !RADAR::DOES_BLIP_EXIST(targetBlip))
		{
			deleteBlipSafe(&targetBlip);
			targetBlip = createBlip(target, BLIP_TYPE_BOUNTY_TARGET, BLIP_SPRITE_BOUNTY_TARGET);
		}
		/*if (stage == BountyMissionStage::MissionInitialization)
		{
			initialize();
			nextStage();
		}
		else if (stage == BountyMissionStage::CollectPoster)
		{
			if (distanceBetween(playerPos, *getArea()->bountyPostersCoords) <= 3.0f &&
				PED::IS_PED_ON_FOOT(player))
			{
				inspectPosterPrompt->show();

				if (inspectPosterPrompt->isActivatedByPlayer())
				{
					nextStage();
				}
			}
			else
			{
				inspectPosterPrompt->hide();
			}
		}
		else if (stage == BountyMissionStage::GoToArea)
		{
			if (distanceBetween(playerPos, missionData->startPosition) <= targetAreaRadius)
			{
				nextStage();
			}
		}
		else if (stage == BountyMissionStage::LocateTarget)
		{
			if (mustBeCloseToLocate)
			{
				if (distanceBetweenEntities(player, target) <= requiredDistanceToLocate)
				{
					nextStage();
				}
			}
			else if	(ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(player, target, 0))
			{
				nextStage();
			}
			if (distanceBetweenEntities(player, target) <= requiredDistanceToLocate + 30 && !yellow)
			{
				RADAR::REMOVE_BLIP(&targetAreaBlip);
				targetAreaBlip = createBlip(ENTITY::GET_ENTITY_COORDS(target, true, false), targetAreaRadius - 40, 0xC19DA63, 0);
				yellow = true;
			}
			if (distanceBetween(playerPos, missionData->startPosition) > targetAreaRadius)
			{
				cleanup();
				releaseEntitySafe(&target);
				stage = BountyMissionStage::GoToArea;
				if (yellow == true)
				{
					fail("Bounty failed, target lost");
				}
			}
			if (yellow == true)
			{
				if (distanceBetweenEntities(target, player) > 100)
				{
					PED::DELETE_PED(&target);
					fail("Bounty failed, target lost");
				}
			}
		}
		else if (stage == BountyMissionStage::CaptureTarget)
		{
			if (isPedHogtied(target) ||
				(missionData->requiredTargetCondition == TargetCondition::DeadOrAlive && ENTITY::IS_ENTITY_DEAD(target)))
			{
				nextStage();
			}
		}
		else if (stage == BountyMissionStage::ArriveToPoliceStation)
		{
			float distanceToPolice = distanceBetween(ENTITY::GET_ENTITY_COORDS(player, 1, 1), *(getArea()->policeDeptCoords));
			if (distanceToPolice < 500 && !spawnedBountyHunters)
			{
				spawnBountyHunters();
			}
			Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(target, true, false);
			if (distanceBetween(targetPos, *getArea()->policeDeptCoords) < 20)
			{
				nextStage();
			}
		}
		else if (stage == BountyMissionStage::HandOverTarget)
		{
			Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(target, true, false);
			if (distanceBetween(targetPos, *getArea()->cellCoords) < 3 &&
				ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(target) <= 1.1)
			{
				nextStage();
			}
		}
		else if (stage == BountyMissionStage::CollectReward)
		{
			nextStage();
		}*/

		if (stage >= BountyMissionStage::LocateTarget && stage <= BountyMissionStage::CollectReward)
		{
			if (missionData->requiredTargetCondition == TargetCondition::Alive && ENTITY::IS_ENTITY_DEAD(target))
			{
				fail("Bounty failed. The target was wanted alive!");
			}
			else if (ENTITY::IS_ENTITY_DEAD(player) || !ENTITY::DOES_ENTITY_EXIST(target))
			{
				fail();
			}
		}

		if (stage > BountyMissionStage::CaptureTarget && stage < BountyMissionStage::CollectReward)
		{
			if (!ENTITY::IS_ENTITY_DEAD(target) && !isPedHogtied(target))
			{
				deleteBlipSafe(&policeLocBlip);
				deleteBlipSafe(&cellBlip);

				stage = BountyMissionStage::CaptureTarget;

				std::stringstream text;
				text << "Capture ~COLOR_RED~" << missionData->targetName;
				showSubtitle(text.str().c_str());
			}
		}
	}
}

MapArea* BaseMissionExecutor::getArea()
{
	return areasMgr->getMapArea(missionData->area);
}

Ped BaseMissionExecutor::getTarget()
{
	return target;
}

void BaseMissionExecutor::setTargetAreaRadius(int radius)
{
	this->targetAreaRadius = radius;
}

void BaseMissionExecutor::setRequiredDistanceToLocateTarget(int distance)
{
	requiredDistanceToLocate = distance;
}

void BaseMissionExecutor::setMustBeCloseToLocate(bool toggle)
{
	mustBeCloseToLocate = toggle;
}

void BaseMissionExecutor::nextStage()
{
	switch (stage)
	{
		case BountyMissionStage::MissionInitialization:	
			stage = BountyMissionStage::CollectPoster; 
			break;

		case BountyMissionStage::CollectPoster:			
			onPosterCollected();
			stage = BountyMissionStage::GoToArea; 
			break;

		case BountyMissionStage::GoToArea:				
			onArrivalToArea();
			stage = BountyMissionStage::LocateTarget; 
			break;

		case BountyMissionStage::LocateTarget:			
			onTargetLocated();
			stage = BountyMissionStage::CaptureTarget; 
			break;

		case BountyMissionStage::CaptureTarget:			
			onTargetCaptured();
			stage = BountyMissionStage::ArriveToPoliceStation; 
			break;

		case BountyMissionStage::ArriveToPoliceStation:	
			onArrivalToPoliceStation();
			stage = BountyMissionStage::HandOverTarget; 
			break;

		case BountyMissionStage::HandOverTarget:		
			onTargetHandedOver();
			stage = BountyMissionStage::CollectReward; 
			break;

		case BountyMissionStage::CollectReward:			
			onRewardCollected();
			onFinished(true);
			stage = BountyMissionStage::Finished; 
			break;
	}
}

void BaseMissionExecutor::fail(const char* reason)
{
	status = BountyMissionStatus::Failed;
	seen = false;

	if (reason)
	{
		showSubtitle(reason);
	}

	cleanup();
}

void BaseMissionExecutor::initialize()
{
	status = BountyMissionStatus::Pending;

	Vector3* posterPos = getArea()->bountyPostersCoords;
	if (missionData->requiredTargetCondition == TargetCondition::Alive)
	{
		poster = createProp("p_pos_wantedalive01x", *posterPos, true);
	}
	else
	{
		poster = createProp("p_pos_wanteddead01x", *posterPos, true);
	}
	ENTITY::SET_ENTITY_HEADING(poster, getArea()->bountyPosterHeading);
	posterBlip = createBlip(poster, 0xB04092F8, -1636832113);
	setBlipLabel(posterBlip, "Bounty Poster");
}

void BaseMissionExecutor::onPosterCollected()
{
	status = BountyMissionStatus::CollectedPoster;

	if (poster)
	{
		Ped player = PLAYER::PLAYER_PED_ID();
		Vector3 posterCoords = *getArea()->bountyPostersCoords;
		Object seq;
		AI::OPEN_SEQUENCE_TASK(&seq);
		AI::TASK_TURN_PED_TO_FACE_COORD(0, posterCoords.x, posterCoords.y, posterCoords.z, 1000);
		AI::_0x524B54361229154F(0, GAMEPLAY::GET_HASH_KEY("WORLD_HUMAN_WRITE_NOTEBOOK"), 5000, true, true, 0, true);
		AI::CLOSE_SEQUENCE_TASK(seq);
		AI::CLEAR_PED_TASKS(player,1,1);
		AI::TASK_PERFORM_SEQUENCE(player, seq);
		AI::CLEAR_SEQUENCE_TASK(&seq);
		inspectPosterPrompt->hide();

		WAIT(8000);

		menu->showMissionDetails(missionData);
		ENTITY::DELETE_ENTITY(&poster);
	}

	targetAreaBlip = createBlip(missionData->startPosition, targetAreaRadius, 0xB04092F8, -907204276 /* Bounty sprite */);

	const char* condition = missionData->requiredTargetCondition == TargetCondition::Alive ? "Alive" : "Dead or Alive";
	std::stringstream label;
	label << "Bounty Hunting: "
		<< missionData->targetName << ", "
		<< missionData->reward << "$, "
		<< condition;
	setBlipLabel(targetAreaBlip, label.str().c_str());

	log(string("collected poster for: ").append(getMissionData()->targetName).append(" in ").append(getArea()->name));
}

void BaseMissionExecutor::onArrivalToArea()
{
	status = BountyMissionStatus::InProgress;
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);
	setBlipLabel(targetAreaBlip, "Bounty Hunting");

	target = spawnTarget();
	prepareSet();

	const char* gender = missionData->isTargetMale ? "He" : "She";
	const char* condition = missionData->requiredTargetCondition == TargetCondition::Alive ? "alive" : "dead or alive";
	std::stringstream text;
	text << "Locate ~COLOR_WHITE~" << missionData->targetName << "~COLOR_WHITE~ - " << gender << " is wanted " << condition ;
	showSubtitle(text.str().c_str());

	log(string("mission started: ").append(getMissionData()->targetName).append(" in ").append(getArea()->name));
}

void BaseMissionExecutor::onTargetLocated()
{
	decorateTarget();
	RADAR::REMOVE_BLIP(&targetAreaBlip);

	/*const char* gender = missionData->isTargetMale ? "He" : "She";
	const char* condition = missionData->requiredTargetCondition == TargetCondition::Alive ? "Alive" : "Dead or Alive";
	std::stringstream text;
	text << "Capture ~COLOR_RED~" << missionData->targetName << "~COLOR_WHITE~. " << gender << " is wanted " << condition << ".";
	showSubtitle(text.str().c_str());*/
}

void BaseMissionExecutor::onTargetCaptured()
{
	Vector3* posterPos = getArea()->policeDeptCoords;
	dummyProp = createProp("p_shotGlass01x", *posterPos, true, false, false);
	policeLocBlip = createBlip(dummyProp, 0x1857A152);
	std::stringstream text;
	text << "Take ~COLOR_RED~" << missionData->targetName << "~COLOR_WHITE~ to the ~COLOR_YELLOW~Police Department";
	showSubtitle(text.str().c_str());
}

void BaseMissionExecutor::onArrivalToPoliceStation()
{
	OBJECT::DELETE_OBJECT(&dummyProp);
	deleteBlipSafe(&policeLocBlip);
	Vector3* posterPos = getArea()->cellCoords;
	dummyProp = createProp("p_shotGlass01x", *posterPos, true, false, false);
	cellBlip = createBlip(dummyProp, 0x1857A152);//0xC19DA63
	vector<Ped>::iterator pedItr;
	for (pedItr = bountyHunters.begin(); pedItr != bountyHunters.end(); pedItr++)
	{
		releaseEntitySafe(&(*pedItr));
	}
	for (pedItr = bountyhorses.begin(); pedItr != bountyhorses.end(); pedItr++)
	{
		releaseEntitySafe(&(*pedItr));
	}
	
	std::stringstream text;
	text << "Drop ~COLOR_RED~" << missionData->targetName << "~COLOR_WHITE~ in the ~COLOR_YELLOW~Cell";
	showSubtitle(text.str().c_str());
}

void BaseMissionExecutor::onTargetHandedOver()
{
	deleteBlipSafe(&targetBlip);
	OBJECT::DELETE_OBJECT(&dummyProp);
	deleteBlipSafe(&cellBlip);
}

void BaseMissionExecutor::onRewardCollected()
{
	CASH::PLAYER_ADD_CASH(missionData->reward * 100, 1831944558);
	showSubtitle(BOUNTY_COMPLETED);
}

void BaseMissionExecutor::onFinished(bool shouldCleanup)
{
	status = BountyMissionStatus::Completed;

	if (shouldCleanup)
	{
		cleanup();
	}
}

void BaseMissionExecutor::spawnBountyHunters()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 enemiesSourcePos = getRandomPedPositionInRange(playerPos, 60);
	log(playerPos);
	log(enemiesSourcePos);

	Ped horse1 = createPed("A_C_Horse_TennesseeWalker_DappleBay", getRandomPedPositionInRange(playerPos, 60));
	Ped horse2 = createPed("A_C_Horse_TennesseeWalker_DappleBay", getRandomPedPositionInRange(playerPos, 60));
	Ped horse3 = createPed("A_C_Horse_TennesseeWalker_DappleBay", getRandomPedPositionInRange(playerPos, 60));
	bountyhorses.push_back(horse1);
	bountyhorses.push_back(horse2);
	bountyhorses.push_back(horse3);
	giveSaddleToHorse(horse1, HorseSaddleHashes::MCCLELLAN_01_STOCK_NEW_SADDLE_004);
	giveSaddleToHorse(horse2, HorseSaddleHashes::MCCLELLAN_01_STOCK_NEW_SADDLE_002);
	giveSaddleToHorse(horse3, HorseSaddleHashes::MCCLELLAN_01_STOCK_NEW_SADDLE_002);

	addBountyHunter(horse1, true);
	addBountyHunter(horse2, true);
	addBountyHunter(horse3, true);
	WAIT(1000);

	vector<Ped>::iterator pedItr;
	for (pedItr = bountyHunters.begin(); pedItr != bountyHunters.end(); pedItr++)
	{
		Ped curr = *pedItr;
		AI::TASK_COMBAT_PED(curr, player, 0, 16);
	}
	spawnedBountyHunters = true;
}

void BaseMissionExecutor::addBountyHunter(Ped horse, bool isDriver)
{
	Ped bh = createPedOnHorse("G_M_M_BountyHunters_01", horse, isDriver ? -1 : 0);
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(bh, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
	DECORATOR::DECOR_SET_INT(bh, "honor_override", 0);
	bountyHunters.push_back(bh);
	createBlip(bh, BLIP_STYLE_ENEMY);
	pedEquipBestWeapon(bh);
}

void BaseMissionExecutor::releaseUnnecessaryEntities()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	std::vector<Ped>::iterator it;

	if (getMissionStage() >= BountyMissionStage::ArriveToPoliceStation)
	{
		for (it = bountyhorses.begin(); it != bountyhorses.end(); it++)
		{
			if (distanceBetweenEntitiesHor(*it, player) > 250 || ENTITY::IS_ENTITY_DEAD(*it))
			{
				releaseEntitySafe(&(*it));
			}
		}
		for (it = bountyHunters.begin(); it != bountyHunters.end(); ++it)
		{
			if (distanceBetweenEntitiesHor(*it, player) > 250 || ENTITY::IS_ENTITY_DEAD(*it))
			{
				releaseEntitySafe(&(*it));
			}
		}
	}
}

void BaseMissionExecutor::releaseEntitySafe(Entity* entity)
{
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS((PLAYER::PLAYER_PED_ID()), true, false);
	if ((*entity) && ENTITY::DOES_ENTITY_EXIST(*entity))
	{
		if (stage == BountyMissionStage::LocateTarget && distanceBetween(playerPos, missionData->startPosition) > targetAreaRadius)
		{
			ENTITY::DELETE_ENTITY(entity);
		}
		else
		{
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(entity);
		}
	}
}

void BaseMissionExecutor::cleanup()
{
	if (status == BountyMissionStatus::Completed || status == BountyMissionStatus::Failed)
	{
		deleteBlipSafe(&targetBlip);
		deleteBlipSafe(&targetAreaBlip);
		deleteBlipSafe(&policeLocBlip);
		deleteBlipSafe(&cellBlip);
		releaseEntitySafe(&target);
	}
	vector<Ped>::iterator pedItr;
	for (pedItr = bountyHunters.begin(); pedItr != bountyHunters.end(); pedItr++)
	{
		releaseEntitySafe(&(*pedItr));
	}
	for (pedItr = bountyhorses.begin(); pedItr != bountyhorses.end(); pedItr++)
	{
		releaseEntitySafe(&(*pedItr));
	}
}

void BaseMissionExecutor::decorateTarget()
{
	PED::_0x4A48B6E03BABB4AC(target, (Any*)missionData->targetName); // Set ped name
	targetBlip = createBlip(target, BLIP_STYLE_ENEMY);
}