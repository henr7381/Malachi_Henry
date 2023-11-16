/*
 * Malachi Henry, ???
 *
 * This class has a function to get ADC values.
 * ACD readings range from 0 - 4095
 *
 */

// Includes -=========================================
#include "../repo/Cheka_adc.h"
#include <string.h> //------------TODAY
#include <stdio.h> //-----------------TODAY
#include "main.h"
#include "stm32g0xx_hal_tim.h"
#include "stm32g0xx_hal_def.h"
#include "stm32g0xx_hal_tim_ex.h"
#include "Sean_queue.h"

// Timer / ADC definitions -==========================
extern TIM_HandleTypeDef htim16;
extern ADC_HandleTypeDef hadc1;

// Flags -============================================
extern volatile bool ADC_FLAG;


Convert_ADC::Convert_ADC(Sean_queue *q_volt)
{
	this -> q_volt = q_volt;
	this -> voltage = 0;
}


void Convert_ADC::get_ADC_VAL()
{
	// Only runs if told to
	if (ADC_FLAG)
	{
		// Getting ADC value by polling -========================
		HAL_ADC_Start_IT(&hadc1);
		HAL_ADC_ConvCpltCallback(&hadc1);
		voltage = HAL_ADC_GetValue(&hadc1);
		//=======================================================

		// enqueues the raw voltage to a queue, resets storage value to 0 (just in case) and acknowledges flag
		uint8_t check = q_volt -> enqueue(voltage);
		assert(check);

		voltage = 0;
		ADC_FLAG = 0;

	}

}
