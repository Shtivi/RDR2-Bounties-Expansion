#include "Main.h";

using namespace std;

const char BOUNTY_FAILED_REPLAY[] = "You may restart failed bounty missions after a few game hours.";

BountiesManager::BountiesManager(ModProgress* progress, MapAreasManager* areasMgr, BountyMissionsFactory* missionsFactory)
{
	this->progress = progress;
	this->areasMgr = areasMgr;
	this->missionsFactory = missionsFactory;

	loadActiveMissions();
}

void BountiesManager::resetMissions(MapAreas areaId)
{
	MapArea* area = areasMgr->getMapArea(areaId);

	string msg("reseting missions in ");
	msg = msg.append(area->name);
	log(msg);

	set<int>::iterator missionsItr = area->getMissionIds()->begin();
	while (missionsItr != area->getMissionIds()->end())
	{
		BaseMissionExecutor* executor = missionsFactory->fromMissionId(*missionsItr);

		string msg("reseting: ");
		msg = msg.append(executor->getMissionData()->targetName);

		progress->allowMission(*missionsItr);
		executor->setMissionStatus(BountyMissionStatus::Pending);

		if (!isExecutorLoaded(executor))
		{
			missionExecutors.push_back(executor);
			msg = msg.append(", was not loaded");
		}

		log(msg);
		missionsItr++;
	}

	progress->save();
}

void BountiesManager::update()
{
	BaseMissionExecutor* curr;
	BountyMissionStatus currStatus;
	int currId;
	//vector<BaseMissionExecutor*> finishedMissions;
	vector<BaseMissionExecutor*>::iterator it = missionExecutors.begin();

	while (it != missionExecutors.end())
	{
		curr = *it;
		currStatus = curr->getMissionStatus();
		currId = curr->getMissionData()->id;

		if (currStatus == BountyMissionStatus::Completed)
		{
			std::string msg = "completed mission: ";
			msg = msg.append(curr->getMissionData()->targetName);
			log(msg);

			progress->completeMission(currId);
			progress->save();
			it = missionExecutors.erase(it);
			nextMissions[currId] = getGameTime();
			//finishedMissions.push_back(curr);

		}
		else if (currStatus == BountyMissionStatus::Failed)
		{
			it = missionExecutors.erase(it);
			failedMissions[currId] = getGameTime();

			std::string msg = "mission failed: ";
			msg = msg.append(curr->getMissionData()->targetName);
			log(msg);
			setHelpMessage(BOUNTY_FAILED_REPLAY);
		}
		else
		{
			if (currStatus >= BountyMissionStatus::CollectedPoster && currStatus <= BountyMissionStatus::Completed)
			{
				progress->collectMission(currId);
				progress->save();
			}

			(*it)->update();
			it++;
		}
	}
		tm gameTime = getGameTime();
		tm* missionNextTime;
		int missionId;
		map<int, tm>::iterator id = nextMissions.begin();
		while (id != nextMissions.end())
		{
			missionId = (*id).first;
			missionNextTime = &(*id).second;
			int diffInSecs = difftime(mktime(&gameTime), mktime(missionNextTime));
			if (diffInSecs >= NEXT_MISSION_TIME_WAITING_SECS)
			{
				curr = missionsFactory->fromMissionId(missionId);
				startNextMission(curr);
				id = nextMissions.erase(id);
			}
			else
			{
				id++;
			}
		}
	//for (it = finishedMissions.begin(); it != finishedMissions.end(); it++)
	//{
	//	startNextMission(*it);
	//}
			
	updateFailedMissions();
}

void BountiesManager::loadActiveMissions()
{
	vector<MapArea*> areas = areasMgr->getMapAreas();
	vector<MapArea*>::iterator areasItr;
	MapArea* currArea;

	log("loading missions:");

	for (areasItr = areas.begin(); areasItr != areas.end(); areasItr++)
	{
		currArea = *areasItr;
		set<int>* missionIds = currArea->getMissionIds();
		set<int>::iterator missionItr = missionIds->begin();
		int currMissionId;
		BaseMissionExecutor* executor;

		bool doneAreaHandling = false;;
		while (missionItr != missionIds->end() && !doneAreaHandling)
		{
			currMissionId = *missionItr;
			if (missionsFactory->doesMissionExist(currMissionId))
			{
				BountyMissionStatus missionProgress = progress->getMissionProgress(currMissionId);
				if (missionProgress > BountyMissionStatus::Unavailable && missionProgress < BountyMissionStatus::Completed)
				{
					executor = missionsFactory->fromMissionId(currMissionId);
					executor->setMissionStatus(missionProgress);
					missionExecutors.push_back(executor);
					doneAreaHandling = true;
					log(executor->getMissionData()->targetName);
				}
				executor = missionsFactory->fromMissionId(currMissionId);
				if (missionProgress == BountyMissionStatus::Completed)
				{
					loadNextMission(executor);
				}
			}
			else
			{
				string logTxt = string("could not find a registered executor for mission id: ").append(to_string(currMissionId));
				log(logTxt);
			}

			missionItr++;
		}
	}
}

void BountiesManager::loadNextMission(BaseMissionExecutor* after)
{
	MapArea* area = areasMgr->getMapArea(after->getMissionData()->area);
	int nextMissionId = area->nextMission(after->getMissionData()->id);

	if (nextMissionId == -1)
	{
		set<int>::iterator missionItr = area->getMissionIds()->begin();
		BaseMissionExecutor* executor = missionsFactory->fromMissionId(*missionItr);
		for (missionItr = area->getMissionIds()->begin(); missionItr != area->getMissionIds()->end();missionItr++)
		{
			executor->setMissionStatus(BountyMissionStatus::Pending);
			progress->allowMission(*missionItr);
		}
		missionExecutors.push_back(executor);
	}
}

void BountiesManager::startNextMission(BaseMissionExecutor* after)
{
	log((new string("starting next mission after: "))->append(after->getMissionData()->targetName));

	MapArea* area = areasMgr->getMapArea(after->getMissionData()->area);
	int nextMissionId = area->nextMission(after->getMissionData()->id);

	if (nextMissionId != -1)
	{
		BaseMissionExecutor* nextMission = missionsFactory->fromMissionId(nextMissionId);

		if (progress->getMissionProgress(nextMissionId) > BountyMissionStatus::Unavailable)
		{
			nextMission->setMissionStatus(progress->getMissionProgress(nextMissionId));
		}

		progress->allowMission(nextMissionId);
		missionExecutors.push_back(nextMission);

		std::string msg = "starting new mission: ";
		msg = msg.append(nextMission->getMissionData()->targetName);
		log(msg);
	}
	else
	{
		set<int>::iterator missionItr = area->getMissionIds()->begin();
		BaseMissionExecutor* executor = missionsFactory->fromMissionId(*missionItr);
		for (missionItr = area->getMissionIds()->begin(); missionItr != area->getMissionIds()->end();missionItr++)
		{
			executor->setMissionStatus(BountyMissionStatus::Pending);
			progress->allowMission(*missionItr);
		}
		missionExecutors.push_back(executor);
	}
}

void BountiesManager::updateFailedMissions()
{
	tm gameTime = getGameTime();
	tm* missionFailureTime;
	int missionId;
	BaseMissionExecutor* missionExecutor;

	map<int, tm>::iterator it = failedMissions.begin();

	while (it != failedMissions.end())
	{
		missionId = (*it).first;
		missionFailureTime = &(*it).second;

		int diffInSecs = difftime(mktime(&gameTime), mktime(missionFailureTime));
		if (diffInSecs >= RESTART_FAILED_MISSION_WAITING_SECS)
		{
			missionExecutor = missionsFactory->fromMissionId(missionId);
			missionExecutor->setMissionStatus(BountyMissionStatus::CollectedPoster);
			missionExecutors.push_back(missionExecutor);
			it = failedMissions.erase(it);
		}
		else
		{
			it++;
		}
	}
}

bool BountiesManager::isExecutorLoaded(BaseMissionExecutor* executor)
{
	vector<BaseMissionExecutor*>::iterator executorsItr = missionExecutors.begin();
	while (executorsItr != missionExecutors.end())
	{
		if ((*executorsItr)->getMissionData()->id == executor->getMissionData()->id)
		{
			return true;
		}

		executorsItr++;
	}

	return false;
}