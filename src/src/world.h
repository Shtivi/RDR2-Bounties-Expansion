#pragma once

using namespace std;

const Hash BLIP_STYLE_ENEMY = 0x318C617C;
const Hash BLIP_TYPE_BOUNTY_TARGET = 0x38CDE89D;
const Hash BLIP_SPRITE_BOUNTY_TARGET = 0x5846C31D;

char* const SKINNER_BROTHER_MODEL = "g_m_m_unimountainmen_01";
char* const F_LOWER_TOWN_FOLK = "A_F_M_LowerSDTownfolk_01";
char* const M_LOWER_TOWN_FOLK = "A_M_M_LowerSDTownfolk_01";

typedef struct RaycastResult
{
	bool didHit;
	Vector3 hitPos;
	Entity hitEntity;
	Vector3 normal;
};

enum RaycastIntersectionOptions
{
	Everything = -1,
	Map = 1,
	MissionEntities,
	Peds1 = 12,
	Objects = 16,
	Unk1 = 32,
	Unk2 = 64,
	Unk3 = 128,
	Vegetation = 256,
	Unk4 = 512
};

void getGroundPos(Vector3 originalPos, Vector3* outPos);
float getGroundPos(Vector3 originalPos);
float distanceBetweenEntities(Entity entity1, Entity entity2);
Ped createPed(char* model, Vector3 pos);
Ped createPedOnHorse(char* model, Ped horse, int seatIndex = 1);
bool isPedHogtied(Ped ped);
Vehicle createVehicle(char* model, Vector3 pos);
Vehicle createVehicle(Hash model, Vector3 pos);
Object createProp(char* model, Vector3 position, bool isStatic = false, bool isVisible = true);
RaycastResult raycast(Vector3 source, Vector3 direction, float maxDist, RaycastIntersectionOptions intersectionOptions = Everything);
void releaseEntitySafe(Entity* entity);
tm getGameTime();