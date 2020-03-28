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
	return AI::GET_IS_TASK_ACTIVE(ped, 399);
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