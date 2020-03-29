#include "Main.h";

using namespace std;

BountiesManager::BountiesManager(ModProgress* progress, MapAreasManager* areasMgr, BountyMissionsFactory* missionsFactory)
{
	this->progress = progress;
	this->areasMgr = areasMgr;
	this->missionsFactory = missionsFactory;

	loadActiveMissions();
}

void BountiesManager::update()
{
	BaseMissionExecutor* curr;
	BountyMissionStatus currStatus;
	int currId;
	vector<BaseMissionExecutor*> finishedMissions;
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
			finishedMissions.push_back(curr);
		}
		else if (currStatus == BountyMissionStatus::Failed)
		{
			it = missionExecutors.erase(it);
			failedMissions[currId] = getGameTime();

			std::string msg = "mission failed: ";
			msg = msg.append(curr->getMissionData()->targetName);
			log(msg);
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

	for (it = finishedMissions.begin(); it != finishedMissions.end(); it++)
	{
		startNextMission(*it);
	}

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
			}
			else
			{
				string logTxt = string("could not find a registered executor for mission id: ").append(to_string(currMissionId));
				log(logTxt);
			}

			missionItr++;
		}

		if (missionItr == missionIds->end())
		{
			string msg = "no available missions in: ";
			msg = msg.append(currArea->name);
			log(msg);
		}
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
		else
		{
			nextMission->setMissionStatus(BountyMissionStatus::Pending);
		}

		progress->allowMission(nextMissionId);
		missionExecutors.push_back(nextMission);

		std::string msg = "starting new mission: ";
		msg = msg.append(nextMission->getMissionData()->targetName);
		log(msg);
	}
	else
	{
		std::string msg = "no mission after: ";
		msg = msg.append(after->getMissionData()->targetName);
		log(msg);
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