#include "Main.h";

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
	std::vector<BaseMissionExecutor*> finishedMissions;
	std::vector<BaseMissionExecutor*>::iterator it = missionExecutors.begin();

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
			finishedMissions.push_back(curr);
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
}

void BountiesManager::loadActiveMissions()
{
	std::vector<int> missionsData = missionsFactory->getAllMissionIds();
	std::vector<int>::iterator it;
	BaseMissionExecutor* executor;

	for (it = missionsData.begin(); it != missionsData.end(); it++)
	{
		executor = missionsFactory->fromMissionId(*it);

		if (!executor)
		{
			log("Executor not found in factory for mission:");
			log(std::to_string(*it).c_str());
			continue;
		}

		bool shouldAdd = true;
		std::vector<BaseMissionExecutor*>::iterator execItr = missionExecutors.begin();
		while (execItr != missionExecutors.end() && shouldAdd)
		{
			if ((*execItr)->getMissionData()->area == executor->getMissionData()->area)
			{
				shouldAdd = false;
			}
			execItr++;
		}

		if (!shouldAdd)
		{
			continue;
		}

		executor->setMissionStatus(progress->getMissionProgress(*it));
		if (executor->getMissionStatus() >= BountyMissionStatus::Pending)
		{
			std::string msg = "loaded mission: ";
			msg = msg.append(executor->getMissionData()->targetName);
			log(msg);

			missionExecutors.push_back(executor);
		}
	}
}

void BountiesManager::startNextMission(BaseMissionExecutor* after)
{
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

//
//void BountiesManager::addMission(BaseMissionExecutor* executor)
//{
//	areasMgr->getMapArea(executor->getMissionData()->area)->linkMission(executor->getMissionData()->id);
//	
//	BountyMissionStatus status = progress->getMissionProgress(executor->getMissionData()->id);
//	executor->setMissionStatus(status);
//
//	if (status == BountyMissionStatus::Completed || status == BountyMissionStatus::Unavailable)
//	{
//		return;
//	}
//
//	missionExecutors.push_back(executor);
//}