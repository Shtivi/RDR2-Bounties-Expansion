#include "Main.h";

BountiesManager::BountiesManager(ModProgress* progress, MapAreasManager* areasMgr)
{
	this->progress = progress;
	this->areasMgr = areasMgr;

	createEliasTradition();
}

void BountiesManager::update()
{
	std::vector<BaseMissionExecutor*>::iterator it;
	BaseMissionExecutor* curr;
	BountyMissionStatus currStatus;
	int currId;

	for (it = missionExecutors.begin(); it != missionExecutors.end(); ++it)
	{
		curr = *it;
		currStatus = curr->getMissionStatus();
		currId = curr->getMissionData()->id;
		
		if (currStatus == BountyMissionStatus::Completed)
		{
			progress->completeMission(currId);
			progress->save();

			continue;
		}
		else if (currStatus == BountyMissionStatus::CollectedPoster)
		{
			progress->collectMission(currId);
			progress->save();
		}

		(*it)->update();
	}
}


void BountiesManager::createEliasTradition()
{
	BountyMissionData data;
	EliasTraditionExecutor* executor;

	data.id = 1;
	data.area = Blackwater;
	data.missionName = "Elias's Tradition";
	data.crime = "Murder";
	data.description = "He is the brother of Elias Green,\nboth are members of the infamous Skinner Brothers.\nWanted for murdering a nearby farmers.";
	data.requiredTargetCondition = DeadOrAlive;
	data.reward = 120;
	data.rewardStr = "120$";
	data.startPosition.x = -2032.61;
	data.startPosition.y = -1909.63;
	data.startPosition.z = 110.051;
	data.isTargetMale = true;
	data.targetName = "Elsie Green";
	
	executor = new EliasTraditionExecutor(data, areasMgr);
	executor->setMissionStatus(progress->getMissionProgress(data.id));
	areasMgr->getMapArea(data.area)->linkMission(data.id);

	missionExecutors.push_back(executor);
}