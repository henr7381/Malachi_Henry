/*
 * DataStore.cpp
 *
 *  Created on: Oct 8, 2023
 *      Author: Franc
 *
 * Malachi Henry
 *
 * THis class contains the logic for the trigger level. It recieves a stream
 * of raw voltages from the ADC class and uses a trigger level to filter the
 * number of readings allowed through the system.
 */
#include "../Repo/DataStore.h"
#include "../Repo/Sean_queue.h"
#include <string.h> //------------TODAY
#include <stdio.h> //-----------------TODAY
#include "main.h"

// IPCs -=======================================
extern Sean_queue q_volt;
extern Sean_queue q_raw;
extern volatile uint8_t DISPLAYFLAG;


DataStore::DataStore()
{
	trigger_level = 2048; 		// The trigger level ranges from 0 - 4095, same as the values for the ADC
	checkspot = 1; 				// This variable tracks the state of the state machine across runs.
	bucket = 0;
	DATAREADY = 0;
}


void DataStore::updatedata()
{
	int16_t volt = 0;
	if (q_volt.dequeue(&volt))
	{
		switch(checkspot)
		{
			case 1:
			{
				if (volt < trigger_level)
				{
					checkspot=2;
				}
				break;
			}
			case 2:
			{
				if (volt < trigger_level)
				{
					checkspot=3;
				}
				else
				{
					checkspot = 1;
				}
				break;
			}
			case 3:
			{
				if (volt > trigger_level)
				{
					checkspot=4;
				}
				else
				{
					checkspot = 1;
				}
				break;
			}
			case 4:
			{
				if (volt > trigger_level)
				{
					checkspot=5;
				}
				else
				{
					checkspot = 1;
				}
				break;
			}
			case 5:							// Once in the final state of the machine, the state will lock for a set number of runs
			{
				uint8_t check = q_raw.enqueue(volt);
				assert(check);
				bucket++;

				if (bucket >= 102)
				{
					bucket = 0;
					checkspot = 1;
				}
				break;
			}
		}
	}
}


void DataStore::setTrigger(int16_t newTrigger)
{
	trigger_level = newTrigger;
}




