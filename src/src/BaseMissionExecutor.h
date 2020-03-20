#pragma once

const int AREA_RADIUS = 90;

enum BountyMissionStage
{
	MissionInitialization = -1,
	CollectPoster = 0,
	GoToArea = 1,
	LocateTarget = 2,
	CaptureTarget = 3,
	ArriveToPoliceStation = 4,
	HandOverTarget = 5,
	CollectReward = 6,
	Finished = 7

};

enum BountyMissionStatus {
	Pending = 0,
	CollectedPoster,
	InProgress,
	Completed,
	Failed
};

class BaseMissionExecutor
{
private:
	BountyMissionData* missionData;
	BountyMissionStage stage;
	BountyMissionStatus status;

	Blip posterBlip;
	Object poster;
	Blip targetAreaBlip;
	Ped target;
	Blip cellBlip;

public:
	BaseMissionExecutor(BountyMissionData missionData);

	BountyMissionData* getMissionData();
	BountyMissionStage getMissionStage();
	BountyMissionStatus getMissionStatus();

	void update();
	void nextStage(); // move to protected

protected:
	MapArea* getArea();
	Ped getTarget();
	virtual void prepareSet() = 0;
	virtual Ped spawnTarget() = 0;

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