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
	HankEnepayExecutor* hankEnepayExecutor();
	NateNashobaExecutor* nateNashobaExecutor();
	CharlesMoonExecutor* charlesMoonExecutor();
	JacobSeedExecutor* jacobSeedExecutor();
	JaneBullionExecutor* janeBullionExecutor();
	BufordDukeExecutor* bufordDukeExecutor();
	HarperConnorExecutor* harperConnorExecutor();
	WallaceKnoxExecutor* wallaceKnoxExecutor();
	EmmettDavisExecutor* emmettDavisExecutor();
	AndrewClarkExecutor* andrewClarkExecutor();
	ChesterBurnettExecutor* chesterBurnettExecutor();
	CullenBakerExecutor* cullenBakerExecutor();
	JohnBullExecutor* johnBullExecutor();
	MarquisRussellExecutor* marquisRussellExecutor();
	PeteEatonExecutor* peteEatonExecutor();
	JesseHillExecutor* jesseHillExecutor();
	QuentinChigurhExecutor* quentinChigurhExecutor();
	TucoVillaExecutor* tucoVillaExecutor();
	BillyWilsonExecutor* billyWilsonExecutor();
	JoseChavezExecutor* joseChavezExecutor();
	PanchoDanielExecutor* panchoDanielExecutor();
	ArchStantonExecutor* archStantonExecutor();
	RichardMooreExecutor* richardMooreExecutor();
	JuanCortezExecutor* juanCortezExecutor();
	ClintonvonHagenExecutor* clintonvonHagenExecutor();
	CarlMartinExecutor* carlMartinExecutor();
	TreasuryPeteExecutor* treasuryPeteExecutor();
	RobertCorbucciExecutor* robertCorbucciExecutor();
	MikeSandersExecutor* mikeSandersExecutor();
	ChrisJaniceExecutor* chrisJaniceExecutor();
	JustusBarnesExecutor* justusBarnesExecutor();
	WilliamRogersExecutor* williamRogersExecutor();
	BobLaneExecutor* bobLaneExecutor();
	GeorgeCoenExecutor* georgeCoenExecutor();
	BuckHicoxExecutor* buckHicoxExecutor();
	JohnEastwoodExecutor* johnEastwoodExecutor();
};