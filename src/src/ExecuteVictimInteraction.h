#include "Main.h";

class ExecuteVictimInteraction : public SyncPlayable
{
private:
	Ped victim;
	Ped killer;

public:
	ExecuteVictimInteraction(Ped victim, Ped killer)
	{
		this->victim = victim;
		this->killer = killer;
	}

	void play()
	{
		Vector3 position = ENTITY::GET_ENTITY_COORDS(killer, 1, 1);

		Object seq;
		AI::OPEN_SEQUENCE_TASK(&seq);
		/*AI::TASK_GO_TO_ENTITY(0, victim, 10000, 1.0f, 1, 0, 0);
		AI::TASK_COMBAT_PED(0, victim, 0, 16);*/
		AI::_0x779A2FFACEFAEA7B(0, victim, 0, 1, 1.0f, 1, 0);
		AI::CLOSE_SEQUENCE_TASK(seq);
		AI::CLEAR_PED_TASKS(killer, 1, 1);
		AI::TASK_PERFORM_SEQUENCE(killer, seq);
		AI::CLEAR_SEQUENCE_TASK(&seq);
	}
};