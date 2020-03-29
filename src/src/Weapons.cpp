#include "Main.h";

void giveWeaponToPed(Ped ped, WeaponHash hash, int ammo, bool equipNow)
{
	if (!WEAPON::HAS_PED_GOT_WEAPON(ped, (Hash)hash, 0, 0))
	{
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, (Hash)hash, ammo, equipNow, false);
	}
	else if (equipNow)
	{
		WEAPON::SET_CURRENT_PED_WEAPON(ped, (Hash)hash, true, 0, false, false);
	}
}

void pedEquipBestWeapon(Ped ped)
{
	WEAPON::SET_CURRENT_PED_WEAPON(ped, WEAPON::GET_BEST_PED_WEAPON(ped, 0, 0), true, 0, false, false);
}