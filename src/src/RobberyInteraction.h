#pragma once

class RobberyAimAtVictim : public SyncPlayable
{
private:
	Ped robber;
	Ped victim;

public:
	RobberyAimAtVictim(Ped robber, Ped victim);
	void play();
};


class RobberyWarningShot : public SyncPlayable
{
private:
	Ped robber;
	Ped victim;

public:
	RobberyWarningShot(Ped robber, Ped victim);
	void play();
};