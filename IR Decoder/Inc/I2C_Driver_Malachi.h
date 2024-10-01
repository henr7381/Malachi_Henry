/*
 * Malachi Henry
 */

#ifndef REPO_INC_I2C_DRIVER_MALACHI_H_
#define REPO_INC_I2C_DRIVER_MALACHI_H_

#include "../Inc/queue.h"

// Useful values -====================================
#define SCREEN_BIT_WIDTH 128
#define SCREEN_HEIGHT 64
#define NUM_PAGE_BITS 8
#define NUM_PAGES 8
#define PIXELON 1
#define PIXELOFF 0
#define STARTPAGE 0xB0
#define STARTCOLUMNLSB 0x00
#define STARTCOLUMNMSB 0x10
#define INIT_COUNT 17

class Display
{
public:
	Display(queue *datain);
	void init();
	void displayOff();
	void displayOn();
	void setAddress(uint8_t addr);
	void checkForData();
	void writeCommand(uint8_t cmd);
	void writeActiveBuffer();
	void drawPixelToBuffer(uint8_t x, uint8_t y);
	void bufferToScreen();
	void test();
	void clearScreen();
	void clearBuffer(uint8_t* buf, int size);
	void drawCharacterToBuffer(uint8_t ch, int place);
	void drawByteToBuffer(uint8_t byte, int column);
	void drawSeparatingBar();
private:
	uint8_t address;
	const uint8_t initCommands[INIT_COUNT];
	queue *datain;
	uint8_t bufferArray[SCREEN_BIT_WIDTH * (SCREEN_HEIGHT / NUM_PAGES)];	// This is a buffer full of bytes
	uint8_t activeArray[SCREEN_BIT_WIDTH * (SCREEN_HEIGHT / NUM_PAGES)];	// This is a buffer full of bytes
};

#endif /* REPO_INC_I2C_DRIVER_MALACHI_H_ */
