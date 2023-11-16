/*
 * Edgedetector.cpp
 *
 *  Created on: Aug 17, 2023
 *      Author: docca
 *
 *  Untouched from Dr. Carroll's repo
 */

#include "../Repo/Edgedetector.h"

Edge_detector::Edge_detector() {
	this->b = B_LOW;
	this->gpio_port = GPIOB;
	this->pin_mask = 0x0001;
}

Edge_detector::~Edge_detector() {
	// TODO Auto-generated destructor stub
}

Edge_detector::Edge_detector(const Edge_detector &other) {
	this->gpio_port = other.gpio_port;
	this->pin_mask = other.pin_mask;
	this->b = other.b;
}


void Edge_detector::config_pinout(GPIO_TypeDef *gpio_port, uint16_t pin_mask){
	this->gpio_port = gpio_port;
	this->pin_mask = pin_mask;
}


Edge_sense Edge_detector::update(void){
	Edge_sense e = EDGE_NONE_LOW;
	GPIO_PinState x = HAL_GPIO_ReadPin(this->gpio_port, this->pin_mask);
	switch (this->b)
	{

	case B_LOW:
		if (x == GPIO_PIN_SET){
			this->b = B_MAY_RISE;
			e = EDGE_NONE_LOW;
		}
		else {
			this->b = B_LOW;
			e = EDGE_NONE_LOW;
		}
		break;

	case B_MAY_RISE:
		if (x == GPIO_PIN_SET){
			this->b = B_HIGH;
			e = EDGE_RISING;
		}
		else {
			this->b = B_LOW;
			e = EDGE_NONE_LOW;
		}
		break;

	case B_HIGH:
		if (x == GPIO_PIN_RESET){
			this->b = B_MAY_FALL;
			e = EDGE_NONE_HIGH;
		}
		else {
			this->b = B_HIGH;
			e = EDGE_NONE_HIGH;
		}
		break;

	case B_MAY_FALL:
		if (x == GPIO_PIN_RESET){
			this->b = B_LOW;
			e = EDGE_FALLING;
		}
		else {
			this->b = B_HIGH;
			e = EDGE_NONE_HIGH;
		}
		break;

	}
	return e;
}
