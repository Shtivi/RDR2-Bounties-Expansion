#pragma once

class BountyMissionsFactory
{
private:
	MapAreasManager* areasMgr;;
	std::map<int, BaseMissionExecutor*> executorsCache;

public:
	BountyMissionsFactory(MapAreasManager* areasMgr);

	bool doesMissionExist(int missionId);
	BaseMissionExecutor* fromMissionId(int missionId);
	std::vector<int> getAllMissionIds();

private:
	void initializeCache();
	EliasTraditionExecutor* eliasTraditionExecutor();
	TurkishRunnerExecutor* turkishRunnerExecutor();
	GushkalaInataExecutor* gushkalaInataExecutor();
	JacobSeedExecutor* jacobSeedExecutor();
	AndrewClarkExecutor* andrewClarkExecutor();
	ChesterBurnettExecutor* chesterBurnettExecutor();
	JesseHillExecutor* jesseHillExecutor();
	QuentinChigurhExecutor* quentinChigurhExecutor();
	TucoVillaExecutor* tucoVillaExecutor();
	ArchStantonExecutor* archStantonExecutor();
	RichardMooreExecutor* richardMooreExecutor();
	JuanCortezExecutor* juanCortezExecutor();
	ClintonvonHagenExecutor* clintonvonHagenExecutor();
	TreasuryPeteExecutor* treasuryPeteExecutor();
	RobertCorbucciExecutor* robertCorbucciExecutor();
	JaneBullionExecutor* janeBullionExecutor();
};