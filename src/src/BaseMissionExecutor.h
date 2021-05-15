#pragma once

const int AREA_RADIUS = 90;
const int REQUIRED_DIST_TO_LOCATE = 20;

class BaseMissionExecutor
{
private:
	Prompt* inspectPosterPrompt;
	BountyMissionData* missionData;
	BountyMissionStage stage;
	BountyMissionStatus status;
	MapAreasManager* areasMgr;

	int requiredDistanceToLocate;
	bool mustBeCloseToLocate;
	bool seen;
	bool stopped;
	int targetAreaRadius;
	bool spawnedBountyHunters;
	int spawnchance;

	Object poster;
	Object dummyProp;
	Pickup money;
	Blip posterBlip;
	Blip targetAreaBlip;
	Blip policeLocBlip;
	Blip cellBlip;
	Blip targetBlip;
	Blip moneyBlip;
	vector<Ped> bountyHunters;
	vector<Ped> bountyhorses;

protected:
	Ped target;

public:
	BaseMissionExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);
	BountyMissionData* getMissionData();
	BountyMissionStage getMissionStage();
	BountyMissionStatus getMissionStatus();
	void releaseEntitySafe(Entity* entity);
	void setMissionStatus(BountyMissionStatus status);
	virtual void update();

protected:
	MapArea* getArea();
	Ped getTarget();
	void setTargetAreaRadius(int radius);
	void setRequiredDistanceToLocateTarget(int distance);
	void setMustBeCloseToLocate(bool toggle);
	virtual void prepareSet() = 0;
	virtual Ped spawnTarget() = 0;
	void nextStage();

	void fail(const char* reason = NULL);
	virtual void initialize();
	virtual void onPosterCollected();
	virtual void onArrivalToArea();
	virtual void onTargetLocated();
	virtual void onTargetCaptured();
	virtual void onArrivalToPoliceStation();
	virtual void onTargetHandedOver();
	virtual void onRewardCollected();
	virtual void onFinished(bool shouldCleanup = true);
	virtual void cleanup();

private:
	void decorateTarget();
	void spawnBountyHunters();
	void addBountyHunter(Ped horse, bool isDriver);
	void releaseUnnecessaryEntities();
};