#include "Main.h";

RobberyAimAtVictim::RobberyAimAtVictim(Ped robber, Ped victim)
{
	this->robber = robber;
	this->victim = victim;
}

void RobberyAimAtVictim::play()
{
	pedEquipBestWeapon(robber);
	AI::TASK_HANDS_UP(victim, -1, robber, -1, 0);
	AI::TASK_AIM_GUN_AT_ENTITY(robber, victim, -1, 0, 0);
}