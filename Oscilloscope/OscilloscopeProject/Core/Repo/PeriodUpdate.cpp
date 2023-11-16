/*
 * Malachi Henry
 *
 * Updates the period of TIM16 based on a knob's count
 *
 * Max top: 4099
 * Min top: 99
 */

#include "../Repo/PeriodUpdate.h"
#include "stm32g0xx_hal_def.h"
#include "../Repo/Cheka_adc.h"

extern TIM_HandleTypeDef htim16;
extern uint16_t ISRFLAG;

PeriodUpdater::PeriodUpdater(Knob_FSM *knob)
{
	this -> knob = knob;
}


PeriodUpdater::~PeriodUpdater() {
	// TODO Auto-generated destructor stub
}

void PeriodUpdater::updatePeriod()
{
	count = knob -> get_count();
	newTop = (20 * count) + 99;

	if (ISRFLAG)
	{
		__HAL_TIM_SET_AUTORELOAD(&htim16, newTop);
		ISRFLAG = 0;
	}
}
