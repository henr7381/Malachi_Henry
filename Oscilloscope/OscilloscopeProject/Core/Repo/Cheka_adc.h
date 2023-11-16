/*
 * Cheka_adc.h
 *
 *  Created on: Sep 24, 2023
 *      Author: Franc
 */

#include "main.h"
#include "../Repo/Sean_queue.h"
#ifndef REPO_CHEKA_ADC_H_
#define REPO_CHEKA_ADC_H_

#ifdef __cplusplus
extern "C"
{
#endif

class Convert_ADC
{
private:
	Sean_queue * q_volt;
	uint16_t voltage;
public:
	Convert_ADC(Sean_queue*);
	void get_ADC_VAL();
};

#ifdef __cplusplus
}
#endif

#endif /* REPO_CHEKA_ADC_H_ */
