#include "Main.h";

BountiesManager::BountiesManager(ModProgress* progress, MapAreasManager* areasMgr, BountyMissionsFactory* missionsFactory)
{
	this->progress = progress;
	this->areasMgr = areasMgr;
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
			progress->completeMission(currId);
			progress->save();
			it = missionExecutors.erase(it);
			finishedMissions.push_back(curr);
		}
		else
		{
			if (currStatus == BountyMissionStatus::CollectedPoster)
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

void BountiesManager::startNextMission(BaseMissionExecutor* after)
{
	MapArea* area = areasMgr->getMapArea(after->getMissionData()->area);
	int nextMissionId = area->nextMission(after->getMissionData->id);
	if (nextMissionId != -1)
	{
		BaseMissionExecutor* nextMission = missionsFactory->fromMissionId(nextMissionId);
		nextMission->setMissionStatus(BountyMissionStatus::Pending);
		progress->allowMission(nextMissionId);
		missionExecutors.push_back(nextMission);
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