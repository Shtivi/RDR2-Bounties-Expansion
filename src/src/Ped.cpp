#include "Main.h";

struct SpeechArgs
{
	alignas(8) char* speechName;
	alignas(8) char* voiceName;
	alignas(8) int unk1;
	alignas(8) int unk2;
	alignas(8) int ped;
	alignas(8) int unk3;
	alignas(8) int unk4;
};

Ped createPed(char* modelName, Vector3 pos, float heading)
{
	Hash model = GAMEPLAY::GET_HASH_KEY(modelName);
	STREAMING::REQUEST_MODEL(model, false);
	while (!STREAMING::HAS_MODEL_LOADED(model))
	{
		WAIT(0);
	}

	Ped ped = PED::CREATE_PED(model, pos.x, pos.y, pos.z, heading, false, false, false, false);
	PED::SET_PED_VISIBLE(ped, true);

	return ped;
}

Ped createPedOnHorse(char* modelName, Ped horse, int seatIndex)
{
	Hash model = GAMEPLAY::GET_HASH_KEY(modelName);
	STREAMING::REQUEST_MODEL(model, false);
	while (!STREAMING::HAS_MODEL_LOADED(model))
	{
		WAIT(0);
	}

	Ped ped = PED::_0xF89AA2BD01FC06B7(horse, model, seatIndex, 0, 0, 0, 0);

	PED::SET_PED_VISIBLE(ped, true);
	return ped;
}

bool isPedHogtied(Ped ped)
{
	return AI::GET_IS_TASK_ACTIVE(ped, 400);
}

void playAmbientSpeech(Ped ped, char* speechName, char* voice)
{
	SpeechArgs args;
	args.speechName = speechName;
	args.voiceName = voice;
	args.unk1 = 1;
	args.unk2 = 1744022339;
	args.unk3 = 1;
	args.unk4 = 1;
	args.ped = ped;

	invoke<BOOL>(0x8E04FEDD28D42462, ped, &args);
}

void giveSaddleToHorse(Ped horse, HorseSaddleHashes saddleHash)
{
	PED::_0xD3A7B003ED343FD9(horse, (Hash)saddleHash, true, false, false); 
}

vector<Ped>* getPedGroupMembers(Group group)
{
	if (!PED::DOES_GROUP_EXIST(group))
	{
		return NULL;
	}
	else
	{
		vector<Ped>* results = new vector<Ped>;
		int count, val1;
		PED::GET_GROUP_SIZE(group, (Any*)&val1, &count);

		for (int i = 0; i < count; i++)
		{
			Ped current = PED::GET_PED_AS_GROUP_MEMBER(group, i);
			if (ENTITY::DOES_ENTITY_EXIST(current) && !ENTITY::IS_ENTITY_DEAD(current))
			{
				results->push_back(current);
			}
		}

		Ped leader = PED::_GET_PED_AS_GROUP_LEADER(group);
		if (ENTITY::DOES_ENTITY_EXIST(leader))
		{
			results->push_back(leader);
		}
	}
}

vector<Ped> getNearbyPeds(Ped origin, int limit)
{
	return getNearbyPeds(origin, limit, -1);
}

vector<Ped> getNearbyPeds(Ped origin, int limit, float radius)
{
	int arrSize = limit * 2 + 2;
	int total;
	Ped results[256];
	vector<Ped> asVector;

	results[0] = limit;
	total = PED::GET_PED_NEARBY_PEDS(origin, results, -1, 0);

	for (int i = 0; i < total; i++)
	{
		int offset = i * 2 + 2;
		Ped current = results[offset];
		if (ENTITY::DOES_ENTITY_EXIST(current))
		{
			if (radius == -1 || distanceBetweenEntities(origin, current) <= radius)
			{
				asVector.push_back(current);
			}
		}
	}

	return asVector;
}

vector<Ped> getNearbyDeadBodies(Ped origin, int limit, float radius)
{
	vector<Ped> results = getNearbyPeds(origin, limit, radius);
	vector<Ped>::iterator itr = results.begin();
	while (itr != results.end())
	{
		Ped current = *itr;
		if (!PED::IS_PED_HUMAN(current) || !ENTITY::IS_ENTITY_DEAD(current))
		{
			itr = results.erase(itr);
		}
		else
		{
			itr++;
		}
	}

	return results;
}