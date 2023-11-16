/*
 * PeriodUpdate.h
 *
 *  Created on: Oct 9, 2023
 *      Author: mch73
 */

#ifndef REPO_PERIODUPDATE_H_
#define REPO_PERIODUPDATE_H_

#include "../Repo/Sean_Queue.h"
#include "../Repo/KnobFSM.h"

class PeriodUpdater
{
public:
	PeriodUpdater(Knob_FSM * knob);
	virtual ~PeriodUpdater();
	PeriodUpdater (const PeriodUpdater &other);

	void updatePeriod();

private:
	Knob_FSM *knob;
	uint32_t count;
	uint16_t newTop = 0;
};



#endif /* REPO_PERIODUPDATE_H_ */
