#include "Main.h";

RobberyWarningShot::RobberyWarningShot(Ped robber, Ped victim)
{
	this->robber = robber;
	this->victim = victim;
}

void RobberyWarningShot::play()
{
	//Vector3 aboveHead = PED::GET_PED_BONE_COORDS(victim, 55120, 0, 0, 0);
	Vector3 aboveHead = ENTITY::GET_ENTITY_COORDS(victim, 1, 0);
	aboveHead = add(&aboveHead, &toVector3(0, 0, 2.5f));
	log(aboveHead);
	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_AIM_GUN_AT_COORD(0, aboveHead.x, aboveHead.y, aboveHead.z, 500, 0, 0);
	AI::TASK_SHOOT_AT_COORD(0, aboveHead.x, aboveHead.y, aboveHead.z, 500, -957453492, 0);
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(robber, seq);
	AI::CLEAR_SEQUENCE_TASK(&seq);
	WAIT(1000);
}