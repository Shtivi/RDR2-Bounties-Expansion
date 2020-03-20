#include "Main.h"

std::vector<AttachedRope*> attachedRopes;

void UpdateRopes() 
{
	int wait = 0;
	std::vector<AttachedRope*>::iterator it;

	for (it = attachedRopes.begin(); it != attachedRopes.end(); ++it) 
	{
		if (!(*it)->isExist())
		{
			attachedRopes.erase(it);
			continue;
		}

		wait = max(wait, (*it)->update());
	}

	WAIT(wait);
}

void addRope(AttachedRope* rope)
{
	attachedRopes.push_back(rope);
}

bool doesEntityAttachedToRope(Entity entity)
{
	std::vector<AttachedRope*>::iterator it;
	AttachedRope* curr;

	for (it = attachedRopes.begin(); it != attachedRopes.end(); ++it)
	{
		curr = *it;
		
		if (!curr->isExist())
		{
			return false;
		}

		return curr->getEntity1() == entity || curr->getEntity2() == entity;
	}
}