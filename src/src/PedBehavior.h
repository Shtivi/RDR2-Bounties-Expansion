#pragma once

class PedBehavior 
{
private:
	Ped _pedHandle;
	bool _isActive;

public:
	PedBehavior(Ped ped);
	
	Ped ped();
	virtual bool isActive();
	virtual void start();
	virtual void update();
	virtual void stop();
};

#include "GuardingDefinitions.h";