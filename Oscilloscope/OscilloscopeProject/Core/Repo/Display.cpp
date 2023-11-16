/*
 * Display.cpp
 *
 *  Created on: Sep 18, 2023
 *      Author: Nathan
 *
 *  Malachi Henry
 *
 *  This is the class that facilitates the display of pixels. This class is fed packets containing pixel heights through a queue,
 *  then collects enough pixels for a frame, renders the frame, then displays the frame.
 */

#include "Display.h"
#include "main.h"

Display::Display(Mal_queue *q_buffer) : initCommands{
    0xE2, // System Reset
	0x40, // Set Scroll Line (Display start line 0)
    0xA1, // Set SEG direction (SEG reverse)
    0xC0, // Set COM direction (Normal COM0~COM63)
	0xA4, // Set All Pixel On (Disable -> Set All Pixel to ON)  Try to remove this
    0xA6, // Set Inverse Display (Display inverse off)
    0xA2, // Set LCD Bias Ratio (Set Bias 1/9, Duty 1/65)
    0x2F, // Set Power Control (Booster, Regulator and Follower on)
    0x27, // Set VLCD Resistor Ratio
    0x81, // Set Electronic Volume (Part 1)
    0x10, // Set Electronic Volume (Part 2)
    0xFA, // Set Adv. Program Control (Set Temperature compensation)
    0x93, // Set Adv. Program Control (curve to -0.11%/°C)
    0xAF  // Set Display Enable (Display on)
} {
	this -> framebuffer = q_buffer;

}

// This function sets the data line to allow the transmission of a command
void Display::sendCommand(uint8_t command)
{
    HAL_GPIO_WritePin(CD_GPIO_PORT, CD_PIN, GPIO_PIN_RESET); 	// Set CD pin low (command mode)
    HAL_SPI_Transmit(&hspi1, &command, 1, 100);					// Push command
}


// This function sets the data line to allow the transmission of data
void Display::sendData(uint8_t *data)
{
	HAL_GPIO_WritePin(CD_GPIO_PORT, CD_PIN, GPIO_PIN_SET);		// Set CD pin low (data mode)
	HAL_SPI_Transmit(&hspi1, data, 1, 100);						// Push data
}


// This function just pushes the commands to set up the screen upon initialization
void Display::init()
{
    for (size_t i = 0; i < sizeof(initCommands) / sizeof(initCommands[0]); i++)
    {
        sendCommand(initCommands[i]);
    }
}


// Turns display off
void Display::displayOff()
{
    sendCommand(0xAE); // Display Off command
}


// Turns display on
void Display::displayOn()
{
    sendCommand(0xAF); // Display On command
}


// This clears out the data contained in the buffers, setting everything to zero
void Display::clearFramebuffer()
{
    memset(fbuffer, 0, sizeof(fbuffer));
    memset(clearIndex, 0, sizeof(clearIndex));
}


// This function's job is to go through each page and clear out the screen's onboard RAM
void Display::clearSRAM()
{
	uint8_t pageCommand;
	uint8_t RAMClear = 0x00;
	uint8_t columnMSB_CMD = 0x10;
	uint8_t columnLSB_CMD = 0x00;

		// Iterates through the pages
		for(uint8_t pages = 0; pages < 9; pages++)
		{
			pageCommand = (0xB0 | (pages & 0x07));
			sendCommand(pageCommand);

			// Iterates through each column for each page
			for(uint8_t columns = 132; columns > 0; columns--)
			{
				sendData(&RAMClear);
			}

			// Moves the cursor back to the beginning
			sendCommand(columnLSB_CMD);
			sendCommand(columnMSB_CMD);
		}
}


// Once a frame has been collected, it is sent to the screen with this function
void Display::drawVoltage()
{
	uint8_t page;
	uint8_t pageCommand;
	uint8_t pixel;
	uint8_t columnMSB;
	uint8_t columnLSB;
	uint8_t currentcolumn = 0;

	// For each column, a page and bit have to calculated from a pixel height
	for (int8_t i = 0; i < 102; i++)
	{
		pixel = activeArray[i];

		page = (pixel / NUM_PAGE_BITS);
		pageCommand = (STARTPAGE | (page & 0x07));  // Ensure that only the lower 3 bits are used
		sendCommand(pageCommand);

		columnMSB = (0x10 | (currentcolumn >> 4));
		columnLSB = (0x00 | (currentcolumn & 0x0F));
		currentcolumn++;

		sendCommand(columnLSB);
		sendCommand(columnMSB);

		pixel = (0x01 << (pixel % 8));
		sendData(&pixel);
	}
}


// This is the function that is constantly called to attempt to dequeue and add a pixel to a render
void Display::CheckForData()
{
	static uint8_t bufferReverseIndex = SCREEN_WIDTH - 1;
	packet msg;
	uint8_t pixelHeight;

	if (framebuffer->Mdequeue(&msg))
	{
		pixelHeight = msg.height;

		if (bufferReverseIndex)
		{
			bufferArray[SCREEN_WIDTH - bufferReverseIndex] = pixelHeight;
			bufferReverseIndex--;
		}
		else
		{
			bufferArray[SCREEN_WIDTH - bufferReverseIndex] = pixelHeight;

			for(int8_t i = 0; i < SCREEN_WIDTH; i++)
			{
				activeArray[SCREEN_WIDTH - i] = bufferArray[SCREEN_WIDTH - i];
			}

			bufferReverseIndex = SCREEN_WIDTH - 1;

			clearSRAM();
			drawVoltage();

			for(int8_t i = 0; i < SCREEN_WIDTH; i++)
			{
				activeArray[SCREEN_WIDTH - i] = 0;
			}
		}
	}
}



