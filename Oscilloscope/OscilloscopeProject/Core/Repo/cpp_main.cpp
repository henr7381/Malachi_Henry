/*
 * Malachi Henry, Francesca Queary, Nathan Leap
 *
 * Project initialized 20230919
 *
 * Oscilloscope project. This is a working "proof of concept" level oscilloscope, including
 * an adjustable trigger level and adjustable sampling rate for basic control of the output.
 *
 */

// includes -=====================================================================
#include "main.h"
#include "cpp_main.h"
#include "../Repo/Display.h"
#include "../Repo/KnobFSM.h"
#include "../Repo/Sean_queue.h"
#include "../Repo/Cheka_adc.h"
#include "../Repo/Ram_Health.h"
#include "../Repo/PeriodUpdate.h"
#include "../Repo/RawToPixel.h"
#include "../Repo/Mal_queue.h"
#include "../Repo/DataStore.h"
#include "../Repo/TriggerUpdate.h"
#include "stm32g0xx_hal_tim.h"
#include "stm32g0xx_hal_def.h"
#include "stm32g0xx_hal_tim_ex.h"
#include "stm32g0xx_hal_adc.h"

// Timers -=====================================================================
extern TIM_HandleTypeDef htim17;

// Queues -=====================================================================
Sean_queue q_volt;						// Contains raw voltage readings from the ADC. [Convert_ADC ADC_con] enqueues, [DataStore goodData] dequeues.
Sean_queue q_raw;						// Contains good raw ADC voltages that have been vetted by the trigger level. [DataStore goodData] enqueues, [rawDataToPixelConverter pixelUpdate] dequeues.
Mal_queue q_video_buffer;				// Contains packets, which contain a pixel height. [rawDataToPixelConverter pixelUpdate] enqueues, [Display display] dequeues.

// Flags -=====================================================================
volatile uint16_t ISRFLAG = 0;			// Informs the TIM16 update fuction that it is safe to autoreload preload
volatile bool ADC_FLAG = 0;				// Informs the ADC function that it's time to pull a reading
volatile uint8_t KNOB1FLAG = 0;			// Informs the knob 1 state machine that it should check the state of it's pins
volatile uint8_t KNOB2FLAG = 0;			// Informs the knob 1 state machine that it should check the state of it's pins

/*****************************************************************************/

/* USER CODE BEGIN 0 */


// Unfortunately there isn't a function for each interrupt, so they must be handled
// like this.
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim -> Instance == TIM17)
	{
		KNOB1FLAG = 1;
		KNOB2FLAG = 1;
	}
	else if (htim -> Instance == TIM16)
	{
		ADC_FLAG = 1;
		ISRFLAG = 1;
	}
}


void do_cpp_loop()
{
	// Must initialize the RAM protection function.
	Ram_init();

	// Initialize all the objects -===================================================================
	Convert_ADC ADC_con(&q_volt);														// This object is in charge of generating ADC values on demand
	DataStore goodData;																	// This object takes ADC readings, applies a trigger level, and sends out good readings
	Knob_FSM knob1(GPIOC, Quad_1_PC10_Pin, GPIOC, Quad_1_PC12_Pin, &KNOB1FLAG);			// This object is a state machine for a knob that controls the period of timer 16
	Knob_FSM knob2(GPIOC, Quad_2_PC2_Pin, GPIOC, Quad_2_PC3_Pin, &KNOB2FLAG);			// This object is a state machine for a knob that controls the trigger level
	rawDataToPixelConverter pixelUpdate(&q_raw, &q_video_buffer);						// This object takes raw ADC readings and converts them to packets containing a pixel height
	PeriodUpdater tim16(&knob1);														// This object takes information from [Knob_FSM knob1] and uses it to update the period of TIM16
	TriggerUpdater Trig(&knob2, &goodData);												// This object takes information from [Knob_FSM knob1] and uses it to update the trigger level in [DataStore goodData]
	Display display(&q_video_buffer);													// This object takes packets from [rawDataToPixelConverter pixelUpdate] and renders and displays frames

	// Must initialize the display before a frame is displayed
	display.init();
	display.clearSRAM();

	while(1)
	{
		// Must run to ensure RAM is healthy. Runs once per loop cycle.
		Ram_Health();

		// Gets an ADC voltage and enqueues into [q_volt]
		ADC_con.get_ADC_VAL();

		// Get readings from [q_volt], if trigger level requirements are met, enqueues into [q_raw]
		goodData.updatedata();

		// Pulls a value from q_raw, processes into a height and column, then enqueues into q_video_buffer.
		pixelUpdate.rawDataToPixel();

		// Updates the knob value
		knob1.update();

		// Updates the knob value
		knob2.update();

		// Updates the period of TIM16 based on the knob value of knob1
		tim16.updatePeriod();
		
		// Updates the trigger level of [DataStore goodData] based on the knob value of knob1
		Trig.updateTrigger();

		// Gets packets from rawDataToPixelConverter pixelUpdate
		display.CheckForData();
	}
}
