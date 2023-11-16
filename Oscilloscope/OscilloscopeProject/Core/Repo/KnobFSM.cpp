/*
 * knobFSM.cpp
 *
 *  Created on: Aug 17, 2023
 *      Author: docca
 *
 *  Malachi Henry
 *
 * This file has been modified from Carroll's code. Because our knobs are only controlling quantities
 * that are based around a user dependent counter, I have added a counter variable. This counter
 * variable holds a value for that knob, which can be used to update a value elsewhere, instead of a
 * insert a value into a queue.
 */

#include "../Repo/KnobFSM.h"

Knob_FSM::Knob_FSM(GPIO_TypeDef *A_gpio_port, uint16_t A_pin_mask, GPIO_TypeDef *B_gpio_port, uint16_t B_pin_mask, volatile uint8_t* READYFLAG) {
	this->pinA_debounced_edge.config_pinout(A_gpio_port, A_pin_mask);
	this->pinB_debounced_edge.config_pinout(B_gpio_port, B_pin_mask);
	//this->pinA_old_debounced_edge.config_pinout(A_gpio_port, A_pin_mask);
	//this->pinB_old_debounced_edge.config_pinout(B_gpio_port, B_pin_mask);
	count = 100;
	this -> READYFLAG = READYFLAG;
}

void Knob_FSM::update(void){
	// AWAIT a message. If none, abort this call.
	if (*READYFLAG)
	{
		Edge_sense A_edge = this->pinA_debounced_edge.update();
		Edge_sense B_edge = this->pinB_debounced_edge.update();

		// Intended: Pin A is pulled up, so when the knob turns CW, the A switch
		// opens first (thus rising), and the B opens & rises while A is still
		// high.
		if ((A_edge == EDGE_NONE_HIGH) && (B_edge == EDGE_RISING))
		{
			if (count < 200)
			{
				count++;
			}
		}
		else if ((A_edge == EDGE_RISING) && (B_edge == EDGE_NONE_HIGH))
		{
			if (count > 0)
			{
				count--;
			}
		}

		*READYFLAG = 0;
	}
	else
	{

	} // ABORT
}

Knob_FSM::~Knob_FSM() {
	// TODO Auto-generated destructor stub
}

uint32_t Knob_FSM::get_count(void)
{
	return this -> count;
}


