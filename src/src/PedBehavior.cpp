#include "Main.h";

PedBehavior::PedBehavior(Ped ped)
{
	_pedHandle = ped;
	_isActive = false;
}

Ped PedBehavior::ped()
{
	return _pedHandle;
}

bool PedBehavior::isActive()
{
	return _isActive;
}

void PedBehavior::start()
{
	_isActive = true;
}

void PedBehavior::update()
{
	if (ENTITY::IS_ENTITY_DEAD(ped()))
	{
		stop();
	}
}

void PedBehavior::stop()
{
	_isActive = false;
}