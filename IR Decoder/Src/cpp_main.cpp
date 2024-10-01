/*
 * Malachi Henry
 * This is the firmware for an IR decoder.
 * This decoder uses a VS1838B to recieve an NEC encoded command, then display it
 * on an SSD1308 OLED.
 */

// Library includes
#include "stdint.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_hal_cortex.h"

// Custom includes
#include "../Inc/cpp_main.h"
#include "../Inc/NEC_Driver.h"
#include "../Inc/queue.h"
#include "../Inc/I2C_Driver_Malachi.h"

// Global declarations
queue recieved_commands;
extern I2C_HandleTypeDef hi2c1;


//=============================================================
// Notable hardware setup:

// Enabled EXTI2 on pin PB7 (IR_IN)
// Falling edge trigger detection
// Enabled corresponding NVIC setting EXTI line[9:5] interrupts

// Enabled TIM1
// Clock source: Internal
// Channel 1: Output compare no output
// Global clock: 32000000Hz
// Prescalar: /1
// Top: 7999
// (Period: 0.25ms)
// Trigger event selection TRG0: Update event

// Enabled I2C1
//=============================================================

// True main function
void main_cpp_loop()
{
	// Class definitions
	Display MainDisplay(&recieved_commands);

	__HAL_I2C_ENABLE(&hi2c1);						// Enable I2C interface

	MainDisplay.init();								// Display initialization

	while(1)
	{
		MainDisplay.checkForData();					// Keep display updated with the most
	}

	return;
}

