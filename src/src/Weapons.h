#pragma once

enum WeaponHash
{
	Unarmed = 0xA2719263,
	Animal = 0xF9FBAEBE,
	Alligator = 0xB5C5D8F1,
	Badger = 0xD872AB0A,
	Bear = 0x1EC181D9,
	Beaver = 0x30E5211A,
	Horse = 0x8BD282A4,
	Cougar = 0x8D4BE52,
	Coyote = 0x453467D1,
	Deer = 0xF4C67A9E,
	Fox = 0x33B2D208,
	Muskrat = 0x2D880572,
	Raccoon = 0x356951B,
	Snake = 0xD8EFBC17,
	Wolf = 0x238A339,
	WolfMedium = 0x88394C06,
	WolfSmall = 0xC80FDF53,
	RevolverCattleman = 0x169F59F7,
	MeleeKnife = 0xDB21AC8C,
	ShotgunDoublebarrel = 0x6DFA071B,
	MeleeLantern = 0xF62FB3A3,
	RepeaterCarbine = 0xF5175BA1,
	RevolverSchofieldBill = 0x6DFE44AB,
	RifleBoltactionBill = 0xD853C801,
	MeleeKnifeBill = 0xCE3C31A4,
	ShotgunSawedoffCharles = 0xBE8D2666,
	BowCharles = 0x791BBD2C,
	MeleeKnifeCharles = 0xB4774D3D,
	ThrownTomahawk = 0xA5E972D7,
	RevolverSchofieldDutch = 0xFA4B2D47,
	RevolverSchofieldDutchDualwield = 0xD44A5A04,
	MeleeKnifeDutch = 0x2C8DBB17,
	RevolverCattlemanHosea = 0xA6FE9435,
	RevolverCattlemanHoseaDualwield = 0x1EAA7376,
	ShotgunSemiautoHosea = 0xFD9B510B,
	MeleeKnifeHosea = 0xCACE760E,
	RevolverDoubleactionJavier = 0x514B39A1,
	ThrownThrowingKnivesJavier = 0x39B815A2,
	MeleeKnifeJavier = 0xFA66468E,
	RevolverCattlemanJohn = 0xC9622757,
	RepeaterWinchesterJohn = 0xBE76397C,
	MeleeKnifeJohn = 0x1D7D0737,
	RevolverCattlemanKieran = 0x8FAE73BB,
	MeleeKnifeKieran = 0x2F3ECD37,
	RevolverCattlemanLenny = 0xC9095426,
	SniperrifleRollingblockLenny = 0x21556EC2,
	MeleeKnifeLenny = 0x9DD839AE,
	RevolverDoubleactionMicah = 0x2300C65,
	RevolverDoubleactionMicahDualwield = 0xD427AD,
	MeleeKnifeMicah = 0xE9245D38,
	RevolverCattlemanSadie = 0x49F6BE32,
	RevolverCattlemanSadieDualwield = 0x8384D5FE,
	RepeaterCarbineSadie = 0x7BD9C820,
	ThrownThrowingKnives = 0xD2718D48,
	MeleeKnifeSadie = 0xAF5EEF08,
	RevolverCattlemanSean = 0x3EECE288,
	MeleeKnifeSean = 0x64514239,
	RevolverSchofieldUncle = 0x99496406,
	ShotgunDoublebarrelUncle = 0x8BA6AF0A,
	MeleeKnifeUncle = 0x46E97B10,
	RevolverDoubleaction = 0x797FBF5,
	RifleBoltaction = 0x772C8DD6,
	RevolverSchofield = 0x7BBD1FF6,
	RifleSpringfield = 0x63F46DE6,
	RepeaterWinchester = 0xA84762EC,
	RifleVarmint = 0xDDF7BC1E,
	PistolVolcanic = 0x20D13FF,
	ShotgunSawedoff = 0x1765A8F8,
	PistolSemiauto = 0x657065D6,
	PistolMauser = 0x8580C63E,
	Pistol1899 = 0x5B78B8DD,
	RepeaterHenry = 0x95B24592,
	ShotgunPump = 0x31B7B9FE,
	WeaponBow = 0x88A8505C,
	ThrownMolotov = 0x7067E7A7,
	MeleeHatchetHewing = 0x1C02870C,
	MeleeMachete = 0x28950C71,
	RevolverDoubleactionExotic = 0x23C706CD,
	RevolverSchofieldGolden = 0xE195D259,
	ThrownDynamite = 0xA64DAA5E,
	MeleeDavyLantern = 0x4A59E501,
	WeaponLasso = 0x7A8A724A,
	KitBinoculars = 0xF6687C5A,
	KitCamera = 0xC3662B7D,
	Fishingrod = 0xABA87754,
	SniperrifleRollingblock = 0xE1D2B317,
	ShotgunSemiauto = 0x6D9BB970,
	ShotgunRepeating = 0x63CA782A,
	SniperrifleCarcano = 0x53944780,
	MeleeBrokenSword = 0xF79190B4,
	MeleeKnifeBear = 0x2BC12CDA,
	MeleeKnifeCivilWar = 0xDA54DD53,
	MeleeKnifeJawbone = 0x1086D041,
	MeleeKnifeMiner = 0xC45B2DE,
	MeleeKnifeVampire = 0x14D3F94D,
	MeleeTorch = 0x67DC3FDE,
	MeleeLanternElectric = 0x3155643F,
	MeleeHatchet = 0x9E12A01,
	MeleeAncientHatchet = 0x21CCCA44,
	MeleeCleaver = 0xEF32A25D,
	MeleeHatchetDoubleBit = 0xBCC63763,
	MeleeHatchetDoubleBitRusted = 0x8F0FDE0E,
	MeleeHatchetHunter = 0x2A5CF9D6,
	MeleeHatchetHunterRusted = 0xE470B7AD,
	MeleeHatchetViking = 0x74DC40ED,
	RevolverCattlemanMexican = 0x16D655F7,
	RevolverCattlemanPig = 0xF5E4207F,
	RevolverSchofieldCalloway = 0x247E783,
	PistolMauserDrunk = 0x4AAE5FFA,
	ShotgunDoublebarrelExotic = 0x2250E150,
	SniperrifleRollingblockExotic = 0x4E328256,
	ThrownTomahawkAncient = 0x7F23B6C7,
	MeleeTorchCrowd = 0xCC4588BD,
	MeleeHatchetMeleeonly = 0x76D4FAB
};

enum WeaponGroup
{
	GroupRevolver = 0xBE5B8969,
	GroupPistol = 0x18D5FA97,
	GroupAnimal = 0xA00FC1E4,
	GroupMelee = 0xD49321D4,
	GroupMeleeThrowable = 0x5C4C5883,
	GroupShotgun = 0x33431399,
	GroupSniperRifle = 0xB7BBD827,
	GroupKit = 0xC715F939,
	GroupRifle = 0x39D5C192,
	GroupGroupBow = 0xB5FD67CD,
	GroupLasso = 0x126210C3,
	GroupRepeater = 0xDC8FB3E9,
	GroupFishingRod = 0x60B51DA4
};

enum AmmoType
{
	AmmoUnusable = 0x0,
	AmmoRevolver = 0x64356159,
	AmmoPistol = 0x743D4F54,
	AmmoHatchetThrowable = 0x194631D6,
	AmmoShotgun = 0x90083D3B,
	AmmoHatchetHewingThrowable = 0x8507C1F7,
	AmmoSniperRifle = 0xD05319F,
	AmmoHatchetAncientThrowable = 0xA9708E57,
	AmmoHatchetHunterThrowable = 0x1AA32EB0,
	AmmoJavierThrowingKnives = 0xF51D1AC7,
	AmmoMolotov = 0x5633F9D5,
	AmmoHatchetVikingThrowable = 0xE501537B,
	AmmoBow = 0x38E6F55F,
	AmmoLasso = 0xEAD00129,
	AmmoRepeater = 0xB0B80B9A,
	AmmoAncientTomahawk = 0xF25D45BC,
	AmmoHatchetDoubleBitRustedThrowable = 0xCABE0C0F,
	AmmoTomahawk = 0x49A985D7,
	AmmoDynamite = 0x1C9D6E9D,
	AmmoHatchetDoubleBitThrowable = 0x63A5047F,
	AmmoThrowingKnives = 0x9E4AD291,
	AmmoRifleVarmint = 0x7DF4D025,
	AmmoHatchedHunterRustedThrowable = 0xBEDC8EB6,
	AmmoCleaverThrowable = 0xB925EC32
};

void giveWeaponToPed(Ped ped, WeaponHash hash, int ammo, bool equipNow = false);
void pedEquipBestWeapon(Ped ped);
