/*
 * Malachi Henry
 * IR Decoder
 */

// Library includes
#include "stm32l4xx.h"
#include "stdint.h"
#include <cstring>

// Custom includes
#include "../Inc/NEC_Driver.h"
#include "../Inc/queue.h"

// Variables/data storage
extern TIM_HandleTypeDef htim1;					// Global tick timer
volatile uint32_t global_tick_count;			// Global tick count. Ticks occur every quarter ms.
volatile uint32_t global_fall_edge_count; 		// Global falling edge count
extern queue recieved_commands;					// Queue for recieved commands


// Start function for TIM1. Resets the count, resets global tick count, begins timer.
void start_timer(void)
{
	TIM1 -> CNT &= 0;
	global_tick_count = 0;
	HAL_TIM_Base_Start_IT(&htim1);
	return;
}


// Stop function for TIM1.
void stop_timer(void)
{
	HAL_TIM_Base_Stop_IT(&htim1);
	return;
}


// ISR for TIM1. Configured to fire once every quarter ms.
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim)
{
	if(htim -> Instance == TIM1)
	{
		if(global_tick_count < INCOMING_RX_TIMEOUT)
		{
			global_tick_count++;
		}
		else
		{
			stop_timer();
			message.fullRx = 0;
			global_tick_count = 0;
			global_fall_edge_count = 0;
		}
	}
}


// Fires once per falling edge of the sensor pin.
void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_7)
	{
			stop_timer();
			global_fall_edge_count++;

			if(global_fall_edge_count >= 35)												// Message complete, 32 bits shifted in.
			{
				if (message.decodedMessage.cmd == (~message.decodedMessage.Ncmd & 0xFF))
				{
					recieved_commands.enqueue((message.decodedMessage.addr << 8) | message.decodedMessage.cmd);
				}

				global_fall_edge_count = 0;
				message.fullRx = 0;
			}
			else if(global_fall_edge_count >= 3)											// Bit detected. Excludes the setup pulse.
			{
				message.fullRx >>= 1;
				message.fullRx |= (global_tick_count >= 7) ? (1 << 31) : (0 << 31);
			}

			start_timer();
	}

	return;
}



