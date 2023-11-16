/*
 * TriggerUpdate.h
 *
 *  Created on: Oct 28, 2023
 *      Author: mch73
 */

#ifndef REPO_TRIGGERUPDATE_H_
#define REPO_TRIGGERUPDATE_H_

#include "../Repo/Sean_Queue.h"
#include "../Repo/KnobFSM.h"
#include "../Repo/Datastore.h"

class TriggerUpdater
{
public:
	TriggerUpdater(Knob_FSM * knob, DataStore * triggerObj);
	virtual ~TriggerUpdater();
	TriggerUpdater (const TriggerUpdater &other);

	void updateTrigger();

private:
	Knob_FSM *knob;
	uint32_t count;
	uint16_t newTop = 0;
	DataStore *triggerObj;
};


#endif /* REPO_TRIGGERUPDATE_H_ */
