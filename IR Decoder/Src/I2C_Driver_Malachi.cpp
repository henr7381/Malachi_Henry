/*
 * Malachi Henry
 * IR Decoder
 * Display rendering + driver
 * The target display is an SSD1306 128x64 OLED
 */

// Library includes
#include "stdint.h"
#include <cstring>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_hal_cortex.h"
#include "stm32l4xx_hal_i2c.h"

// Custom includes
#include "../Inc/cpp_main.h"
#include "../Inc/I2C_Driver_Malachi.h"
#include "../Inc/queue.h"
#include "../Inc/Font.h"

extern I2C_HandleTypeDef hi2c1;

// Initialization conditions
Display::Display(queue *datain): initCommands
{
	0xA8,		// Set MUX ratio
	0x3F,		// MUX ratio = 63 (default)
	0xD3, 		// Set display offset
	0x00, 		// Display offset = 0
	0x40,		// Set display start line
	0xA1, 		// Set segment remap to false (horizontal mirror)
	0xC8,		// COM output scan direction (vertical mirror)
	0xDA,		// Set COM pin remap
	0x12,		// COM pin remap
	0x81,		// Set contrast
	0x7F,		// Contrast = 0x7F (FF max)
	0xA4,		// Resume operation from RAM
	0xA6, 		// Set normal color
	0xD5,		// Set ocs frequency
	0x80,		// osc frequency = 0x80
	0x8D, 0x14,	// Enable charge pump regulator
}
{
	this -> datain = datain;
}


// Set the address of the display
void Display::setAddress(uint8_t addr)
{
	this -> address = addr;
}


// This writes a command to the screen
void Display::writeCommand(uint8_t cmd)
{
    uint8_t data[2] = {0x00, cmd};		// {command byte, command data}
    HAL_I2C_Master_Transmit(&hi2c1, (this -> address), data, 2, HAL_MAX_DELAY);
}


// This writes the entire active array to the screen in page addressing mode
void Display::writeActiveBuffer()
{
	for (int page = 0; page < 8; page++)
	{
		writeCommand(0xB0 + page); 	// Set page address
		writeCommand(0x00);        	// Lower column address
		writeCommand(0x10);        	// Higher column address

		uint8_t buffer[129];
		buffer[0] = 0x40;			// {data byte, {data data}}
		memcpy(&buffer[1], (this -> activeArray) + (page * SCREEN_BIT_WIDTH), SCREEN_BIT_WIDTH);

		HAL_I2C_Master_Transmit(&hi2c1, (this -> address), buffer, sizeof(buffer), HAL_MAX_DELAY);
	}
}


// Turns the whole display off (sleep mode)
void Display::displayOff()
{
	writeCommand(0xAE);
}


// Resumes displaying GDDRAM (turn display on from sleep mode)
void Display::displayOn()
{
	writeCommand(0xAF);
}


// Clears the contents of the specified buffer
void Display::clearBuffer(uint8_t* buf, int size)
{
	memset(buf, 0, size);
}


// Initialization function
void Display::init()
{
	setAddress(0x78);

	for(int i = 0; i < INIT_COUNT; i++)									// Write all init commands to screen
	{
		writeCommand(initCommands[i]);
	}

	displayOn();

	clearBuffer((this -> activeArray), sizeof(this -> activeArray));
	clearBuffer((this -> bufferArray), sizeof(this -> bufferArray));
	writeActiveBuffer();												// Write the clean buffer to screen for a fresh start
}


// This function receives an x, y coordinate and draws it to the buffer array.
// The coordinate plane is indexed from the top left.
void Display::drawPixelToBuffer(uint8_t x, uint8_t y)
{
	if(x < SCREEN_BIT_WIDTH && y < SCREEN_HEIGHT)
	{
		this -> bufferArray[x + ((y / 8) * SCREEN_BIT_WIDTH)] |= 1 << (y % 8);
	}

	return;
}


// This receives a character and a place on the screen and draws the char in that place in the buffer
void Display::drawCharacterToBuffer(uint8_t ch, int place)
{
	int placePixelOffset = (place * FONT_WIDTH);
	int x = 0;

	for(int i = 0; i < FONT_HEIGHT; i++)
	{
		x = font[ch + i];
		for(int j = 0; j < FONT_WIDTH; j++)
		{
			if((x << j) & 0x8000)
			{
				drawPixelToBuffer((placePixelOffset + j), i);
			}
		}
	}
}


// This receives a byte of data and displays each nibble in hex: "0x{low}{high}"
void Display::drawByteToBuffer(uint8_t byte, int column)
{
	drawCharacterToBuffer(ZERO, 0 + (4 * column));
	drawCharacterToBuffer(LETTER_x, 1 + (4 * column));

	// high nibble
	switch((byte >> 4) & 0x0F)
		{
	case 0:
		drawCharacterToBuffer(ZERO, 2 + (4 * column));		break;
	case 1:
		drawCharacterToBuffer(ONE, 2 + (4 * column));		break;
	case 2:
		drawCharacterToBuffer(TWO, 2 + (4 * column));		break;
	case 3:
		drawCharacterToBuffer(THREE, 2 + (4 * column));		break;
	case 4:
		drawCharacterToBuffer(FOUR, 2 + (4 * column));		break;
	case 5:
		drawCharacterToBuffer(FIVE, 2 + (4 * column));		break;
	case 6:
		drawCharacterToBuffer(SIX, 2 + (4 * column));		break;
	case 7:
		drawCharacterToBuffer(SEVEN, 2 + (4 * column));		break;
	case 8:
		drawCharacterToBuffer(EIGHT, 2 + (4 * column));		break;
	case 9:
		drawCharacterToBuffer(NINE, 2 + (4 * column));		break;
	case 10:
		drawCharacterToBuffer(LETTER_A, 2 + (4 * column));		break;
	case 11:
		drawCharacterToBuffer(LETTER_B, 2 + (4 * column));		break;
	case 12:
		drawCharacterToBuffer(LETTER_C, 2 + (4 * column));		break;
	case 13:
		drawCharacterToBuffer(LETTER_D, 2 + (4 * column));		break;
	case 14:
		drawCharacterToBuffer(LETTER_E, 2 + (4 * column));		break;
	case 15:
		drawCharacterToBuffer(LETTER_F, 2 + (4 * column));		break;
		}

	// low nibble
	switch(byte & 0x0F)
		{
	case 0:
		drawCharacterToBuffer(ZERO, 3 + (4 * column));		break;
	case 1:
		drawCharacterToBuffer(ONE, 3 + (4 * column));		break;
	case 2:
		drawCharacterToBuffer(TWO, 3 + (4 * column));		break;
	case 3:
		drawCharacterToBuffer(THREE, 3 + (4 * column));		break;
	case 4:
		drawCharacterToBuffer(FOUR, 3 + (4 * column));		break;
	case 5:
		drawCharacterToBuffer(FIVE, 3 + (4 * column));		break;
	case 6:
		drawCharacterToBuffer(SIX, 3 + (4 * column));		break;
	case 7:
		drawCharacterToBuffer(SEVEN, 3 + (4 * column));		break;
	case 8:
		drawCharacterToBuffer(EIGHT, 3 + (4 * column));		break;
	case 9:
		drawCharacterToBuffer(NINE, 3 + (4 * column));		break;
	case 10:
		drawCharacterToBuffer(LETTER_A, 3 + (4 * column));		break;
	case 11:
		drawCharacterToBuffer(LETTER_B, 3 + (4 * column));		break;
	case 12:
		drawCharacterToBuffer(LETTER_C, 3 + (4 * column));		break;
	case 13:
		drawCharacterToBuffer(LETTER_D, 3 + (4 * column));		break;
	case 14:
		drawCharacterToBuffer(LETTER_E, 3 + (4 * column));		break;
	case 15:
		drawCharacterToBuffer(LETTER_F, 3 + (4 * column));		break;
		}

	return;
}


void Display::drawSeparatingBar()
{
	drawPixelToBuffer(63, 0);
	drawPixelToBuffer(63, 1);
	drawPixelToBuffer(63, 2);
	drawPixelToBuffer(63, 3);
	drawPixelToBuffer(63, 4);
	drawPixelToBuffer(63, 5);
	drawPixelToBuffer(63, 6);
	drawPixelToBuffer(63, 7);
	drawPixelToBuffer(63, 8);
	drawPixelToBuffer(63, 9);
	drawPixelToBuffer(63, 10);
	drawPixelToBuffer(63, 11);
	drawPixelToBuffer(63, 12);
	drawPixelToBuffer(63, 13);
	drawPixelToBuffer(63, 14);
	drawPixelToBuffer(63, 15);
	drawPixelToBuffer(62, 0);
	drawPixelToBuffer(62, 1);
	drawPixelToBuffer(62, 2);
	drawPixelToBuffer(62, 3);
	drawPixelToBuffer(62, 4);
	drawPixelToBuffer(62, 5);
	drawPixelToBuffer(62, 6);
	drawPixelToBuffer(62, 7);
	drawPixelToBuffer(62, 8);
	drawPixelToBuffer(62, 9);
	drawPixelToBuffer(62, 10);
	drawPixelToBuffer(62, 11);
	drawPixelToBuffer(62, 12);
	drawPixelToBuffer(62, 13);
	drawPixelToBuffer(62, 14);
	drawPixelToBuffer(62, 15);

	return;
}


// This is the function that the rest of the firmware integrates with. When no data is available in the input queue, it returns.
// Otherwise, it dequeues the most recent data value and displays it on the screen.
void Display::checkForData()
{
	uint32_t data;

	if(datain -> dequeue(&data))
	{
		for (int i = 1023; i >= 0; i--)
		{
			bufferArray[i] = (i > 255) ? activeArray[i - 256] : 0x00;
		}

		drawByteToBuffer(((data >> 8) & 0x00FF), 0);		// Draw address
		drawSeparatingBar();								// Draw bar to visually separate each byte
		drawByteToBuffer((data & 0x00FF), 1);				// Draw data

		memcpy(activeArray, bufferArray, sizeof(bufferArray));

		writeActiveBuffer();
	}
	return;
}


// This is a test function. Contains a couple features to verify that your display is working.
void Display::test()
{
	clearBuffer((this -> activeArray), sizeof(this -> activeArray));
	clearBuffer((this -> bufferArray), sizeof(this -> bufferArray));

	//================================================================
	// Outputs an arrow pointing to the top left of your display
//	drawPixelToBuffer(0,0);
//	drawPixelToBuffer(0,1);
//	drawPixelToBuffer(0,2);
//	drawPixelToBuffer(0,3);
//	drawPixelToBuffer(0,4);
//	drawPixelToBuffer(0,5);
//	drawPixelToBuffer(0,6);
//	drawPixelToBuffer(0,7);
//	drawPixelToBuffer(0,8);
//	drawPixelToBuffer(0,9);
//	drawPixelToBuffer(0,10);
//
//	drawPixelToBuffer(0,0);
//	drawPixelToBuffer(1,0);
//	drawPixelToBuffer(2,0);
//	drawPixelToBuffer(3,0);
//	drawPixelToBuffer(4,0);
//	drawPixelToBuffer(5,0);
//	drawPixelToBuffer(6,0);
//	drawPixelToBuffer(7,0);
//	drawPixelToBuffer(8,0);
//	drawPixelToBuffer(9,0);
//	drawPixelToBuffer(10,0);
//
//	drawPixelToBuffer(0,0);
//	drawPixelToBuffer(1,1);
//	drawPixelToBuffer(2,2);
//	drawPixelToBuffer(3,3);
//	drawPixelToBuffer(4,4);
//	drawPixelToBuffer(5,5);
//	drawPixelToBuffer(6,6);
//	drawPixelToBuffer(7,7);
//	drawPixelToBuffer(8,8);
//	drawPixelToBuffer(9,9);
//	drawPixelToBuffer(10,10);
	//================================================================

	//================================================================
	// Fills the buffer with a pattern
//	for (int i = 0; i < 1024; i++)
//	{
////		this -> bufferArray[i] = (i / 16) % 2 == (i % 16) % 2 ? 0xFF : 0x00; // Checkerboard pattern (float errors)
////		this -> bufferArray[i] = (i % 2) ? 0xFF : 0x00;		// Vertical bars
////		this -> bufferArray[i] = 0xAA;		// Horizontal bars
//	}
	//================================================================


	memcpy(activeArray, bufferArray, sizeof(bufferArray));

	writeActiveBuffer();
}















