#include "Main.h";

AndrewClarkExecutor::AndrewClarkExecutor(BountyMissionData missionData, MapAreasManager* areasMgr)
	: BaseMissionExecutor(missionData, areasMgr)
{
	setTargetAreaRadius(120);
	setRequiredDistanceToLocateTarget(15);
	setMustBeCloseToLocate(true);
	isTargetAlerted = false;
}

void AndrewClarkExecutor::update()
{
	BaseMissionExecutor::update();
	Ped player = PLAYER::PLAYER_PED_ID();

	if (distanceBetweenEntities(player, target) < 12 && !isTargetAlerted)
	{
		isTargetAlerted = true;
		//PED::_0xFE07FF6495D52E2A(target, 0, 0, 0);
		AI::TASK_TURN_PED_TO_FACE_ENTITY(target, player, 8000, 0, 0, 0);
	}
}

Ped AndrewClarkExecutor::spawnTarget()
{
	Ped target = createPed("A_M_M_GriFancyTravellers_01", toVector3(-311.059, 1355.05, 158.291), 283.609);
	PED::SET_PED_RELATIONSHIP_GROUP_HASH(target, GAMEPLAY::GET_HASH_KEY("REL_CRIMINALS"));
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(target, true);
	return target;
}

void AndrewClarkExecutor::prepareSet()
{	
	wagon = createVehicle(VehicleHash::Wagon02X, toVector3(-310.107, 1360.19, 158.084), 94.2345);
	setVehicleCargo(wagon, VehicleCargoHash::CampCargo1);

	Object campfire = createProp("p_campfire05x", toVector3(-308.143, 1355.59, 158.132));
	campProps.push_back(campfire);

	float tentHeading = 347.298;
	Vector3 tentPos = toVector3(-307.515, 1349.5, 158.023);
	campProps.push_back(createProp("p_amb_tent01x", tentPos, tentHeading));
	campProps.push_back(createProp("p_bedrollopen03x", tentPos, tentHeading));

	AI::_0x524B54361229154F(target, GAMEPLAY::GET_HASH_KEY("WORLD_HUMAN_SIT_GROUND"), -1, true, true, 0, true);
}

void AndrewClarkExecutor::onTargetLocated()
{
	BaseMissionExecutor::onTargetLocated();
	
	Ped player = PLAYER::PLAYER_PED_ID();

	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	if (PED::IS_PED_ON_MOUNT(player))
	{
		AI::_0x48E92D3DDE23C23A(0, PED::GET_MOUNT(player), 0, 0, 0, 0);
	}
	else if (PED::IS_PED_ON_VEHICLE(player, 0))
	{
		AI::TASK_LEAVE_ANY_VEHICLE(0, 0, 0);
	}
	AI::TASK_GO_TO_ENTITY(0, target, 10000, 5, 1, 0, 0);
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(player, seq);
}

void AndrewClarkExecutor::cleanup()
{
	BaseMissionExecutor::cleanup();

	vector<Object>::iterator propsItr;
	for (propsItr = campProps.begin(); propsItr != campProps.end(); propsItr++)
	{
		releaseEntitySafe(&(*propsItr));
	}

	releaseEntitySafe(&wagon);
}