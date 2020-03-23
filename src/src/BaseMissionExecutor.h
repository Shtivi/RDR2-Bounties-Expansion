#pragma once

const int AREA_RADIUS = 90;

class BaseMissionExecutor
{
private:
	BountyMissionData* missionData;
	BountyMissionStage stage;
	BountyMissionStatus status;
	MapAreasManager* areasMgr;

	int targetAreaRadius;
	Blip posterBlip;
	Object poster;
	Blip targetAreaBlip;
	Ped target;
	Blip policeLocBlip;

public:
	BaseMissionExecutor(BountyMissionData missionData, MapAreasManager* areasMgr);

	BountyMissionData* getMissionData();
	BountyMissionStage getMissionStage();
	BountyMissionStatus getMissionStatus();
	void setMissionStatus(BountyMissionStatus status);
	virtual void update();

protected:
	MapArea* getArea();
	Ped getTarget();
	void setTargetAreaRadius(int radius);
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
	virtual void onFinished();
	virtual void cleanup();

private:
	void decorateTarget();
};