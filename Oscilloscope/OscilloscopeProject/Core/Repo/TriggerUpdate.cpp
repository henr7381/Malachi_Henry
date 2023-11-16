/*
 * Malachi Henry
 *
 * Updates the trigger level based on the knob's count. I've been fighting with
 * getting increments correct, by that I mean get the scale of the code to the
 * point where you don't have to spin the knob 400 times to get the output
 * to change.
 */
#include "../Repo/TriggerUpdate.h"

extern uint16_t ISRFLAG;

TriggerUpdater::TriggerUpdater(Knob_FSM *knob, DataStore* triggerObj)
{
	this -> knob = knob;
	this -> triggerObj = triggerObj;
}


TriggerUpdater::~TriggerUpdater() {
	// TODO Auto-generated destructor stub
}

void TriggerUpdater::updateTrigger()
{
	count = knob -> get_count();
	//0 - 4095
	uint32_t newTrigger = count * 20.475 * 2;

	if(newTrigger > 4095)
	{
		newTrigger = 4095;
	}
	else if (newTrigger < 0)
	{
		newTrigger = 0;
	}
	else
	{
		triggerObj -> setTrigger(newTrigger);
	}

}
