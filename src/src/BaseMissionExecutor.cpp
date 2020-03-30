#include "Main.h"

const char BOUNTY_COMPLETED[] = "Bounty completed!";

BaseMissionExecutor::BaseMissionExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
{
	this->areasMgr = areasMgr;
	this->missionData = new BountyMissionData(missionData);
	this->stage = MissionInitialization;
	this->status = Unavailable;

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
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);

	// TODO: delete this code
	if (IsKeyJustUp(VK_KEY_N))
	{
		nextStage();

		if (stage == CaptureTarget)
		{
			if (missionData->requiredTargetCondition == Alive)
			{
				//ENTITY::SET_ENTITY_COORDS(target, getArea()->cellCoords->x, getArea()->cellCoords->y, getArea()->cellCoords->z, 0, 0, 0, 0);
				ENTITY::SET_ENTITY_COORDS(target, playerPos.x, playerPos.y, playerPos.z, 0, 0, 0, 0);
			}
			else
			{
				ENTITY::SET_ENTITY_HEALTH(target, 0, 0);
			}
		}
	}

	if (stage == BountyMissionStage::MissionInitialization)
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
	}

	if (stage >= BountyMissionStage::LocateTarget && stage <= BountyMissionStage::CollectReward)
	{
		if (missionData->requiredTargetCondition == TargetCondition::Alive && ENTITY::IS_ENTITY_DEAD(target))
		{
			fail("Bounty failed. The target was wanted alive!");
		}
		else if (ENTITY::IS_ENTITY_DEAD(player))
		{
			fail();
		}
	}

	if (stage > BountyMissionStage::CaptureTarget && stage < BountyMissionStage::CollectReward)
	{
		if (!ENTITY::IS_ENTITY_DEAD(target) && !isPedHogtied(target))
		{
			stage = BountyMissionStage::CaptureTarget;

			std::stringstream text;
			text << "Capture ~COLOR_RED~" << missionData->targetName;
			showSubtitle(text.str().c_str());
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
			onFinished();
			stage = BountyMissionStage::Finished; 
			break;
	}
}

void BaseMissionExecutor::fail(const char* reason)
{
	status = BountyMissionStatus::Failed;

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

	poster = createProp("p_cs_newspaper_01x", *posterPos, true);
	ENTITY::SET_ENTITY_HEADING(poster, getArea()->bountyPosterHeading);
	posterBlip = createBlip(poster, 0xEC972124, 0x9E6FEC8F);
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
		inspectPosterPrompt->hide();

		WAIT(5000);

		menu->showMissionDetails(missionData);
		ENTITY::DELETE_ENTITY(&poster);
	}

	targetAreaBlip = createBlip(missionData->startPosition, targetAreaRadius, 0xB04092F8, 0x7EAB2A55 /* Bounty sprite */);

	const char* condition = missionData->requiredTargetCondition == TargetCondition::Alive ? "Alive" : "Dead or Alive";
	std::stringstream label;
	label << "Bounty Hunting: "
		<< missionData->targetName << ", "
		<< missionData->reward << "$, "
		<< condition;
	setBlipLabel(targetAreaBlip, label.str().c_str());
}

void BaseMissionExecutor::onArrivalToArea()
{
	status = BountyMissionStatus::InProgress;

	RADAR::REMOVE_BLIP(&targetAreaBlip);
	targetAreaBlip = createBlip(missionData->startPosition, targetAreaRadius, 0xC19DA63, 0);
	setBlipLabel(targetAreaBlip, "Bounty Hunting");

	target = spawnTarget();
	prepareSet();

	const char* gender = missionData->isTargetMale ? "He" : "She";
	const char* condition = missionData->requiredTargetCondition == TargetCondition::Alive ? "Alive" : "Dead or Alive";
	std::stringstream text;
	text << "Locate and capture ~COLOR_RED~" << missionData->targetName << "~COLOR_WHITE~. " << gender << " is wanted " << condition << ".";
	showSubtitle(text.str().c_str());
}

void BaseMissionExecutor::onTargetLocated()
{
	decorateTarget();
	RADAR::REMOVE_BLIP(&targetAreaBlip);

	const char* gender = missionData->isTargetMale ? "He" : "She";
	const char* condition = missionData->requiredTargetCondition == TargetCondition::Alive ? "Alive" : "Dead or Alive";
	std::stringstream text;
	text << "Capture ~COLOR_RED~" << missionData->targetName << "~COLOR_WHITE~. " << gender << " is wanted " << condition << ".";
	showSubtitle(text.str().c_str());
}

void BaseMissionExecutor::onTargetCaptured()
{
	policeLocBlip = createBlip(*getArea()->policeDeptCoords, 0x1857A152);

	std::stringstream text;
	text << "Take ~COLOR_RED~" << missionData->targetName << "~COLOR_WHITE~ to the ~COLOR_YELLOW~Police Department";
	showSubtitle(text.str().c_str());
}

void BaseMissionExecutor::onArrivalToPoliceStation()
{
	deleteBlipSafe(&policeLocBlip);
	cellBlip = createBlip(*getArea()->cellCoords, 0xC19DA63);
	
	std::stringstream text;
	text << "Drop ~COLOR_RED~" << missionData->targetName << "~COLOR_WHITE~ in the ~COLOR_YELLOW~Cell";
	showSubtitle(text.str().c_str());
}

void BaseMissionExecutor::onTargetHandedOver()
{
	Blip targetBlip = RADAR::GET_BLIP_FROM_ENTITY(target);
	deleteBlipSafe(&targetBlip);
	deleteBlipSafe(&cellBlip);
}

void BaseMissionExecutor::onRewardCollected()
{
	CASH::PLAYER_ADD_CASH(missionData->reward * 100, 0);
	setHelpMessage(BOUNTY_COMPLETED);
}

void BaseMissionExecutor::onFinished(bool shouldCleanup)
{
	status = BountyMissionStatus::Completed;

	if (shouldCleanup)
	{
		cleanup();
	}
}

void BaseMissionExecutor::cleanup()
{
	deleteBlipSafe(&targetBlip);
	deleteBlipSafe(&targetAreaBlip);
	deleteBlipSafe(&policeLocBlip);
	deleteBlipSafe(&cellBlip);
	releaseEntitySafe(&target);
}

void BaseMissionExecutor::decorateTarget()
{
	PED::_0x4A48B6E03BABB4AC(target, (Any*)missionData->targetName); // Set ped name
	targetBlip = createBlip(target, BLIP_TYPE_BOUNTY_TARGET, BLIP_SPRITE_BOUNTY_TARGET);
}