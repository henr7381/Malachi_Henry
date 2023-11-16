/*
 * knobFSM.h
 *
 *  Created on: Aug 17, 2023
 *      Author: docca
 */

#ifndef SRC_KNOBFSM_H_
#define SRC_KNOBFSM_H_

#include "../Repo/Edgedetector.h"
#include "../Repo/Sean_queue.h"

enum {KNOB_STEADY, KNOB_CW, KNOB_CCW};  // I do not think that I'll need STEADY, but it's here just-in-case.

class Knob_FSM {
public:
	Knob_FSM(GPIO_TypeDef *A_gpio_port, uint16_t A_pin_mask,GPIO_TypeDef *B_gpio_port, uint16_t B_pin_mask, volatile uint8_t* READYFLAG);
	virtual ~Knob_FSM();
	Knob_FSM(const Knob_FSM &other);
	void update(void);

	uint32_t get_count(void);

private:
	Sean_queue *q_in;
	Edge_detector pinA_debounced_edge;
	Edge_detector pinA_old_debounced_edge;
	Edge_detector pinB_debounced_edge;
	Edge_detector pinB_old_debounced_edge;
	uint32_t count;
	volatile uint8_t* READYFLAG;
};

#endif /* SRC_KNOBFSM_H_ */
