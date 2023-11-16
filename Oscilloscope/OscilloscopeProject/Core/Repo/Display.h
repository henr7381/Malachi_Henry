/*
 * Display.h
 *
 *  Created on: Sep 18, 2023
 *      Author: Nathan
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include "main.h"
#include <assert.h>
#include <cstring>
#include "../repo/Mal_queue.h"

// Useful values -====================================
#define MAX_SCREEN_WIDTH 131
#define SCREEN_WIDTH 102
#define SCREEN_HEIGHT 64
#define NUM_PAGES 8
#define NUM_PAGE_BITS 8
#define PIXELON 1
#define PIXELOFF 0
#define STARTPAGE 0xB0
#define STARTCOLUMNLSB 0x00
#define STARTCOLUMNMSB 0x10

// Defining ports and values for SPI1 -===============
#define CD_GPIO_PORT GPIOD
#define CD_PIN GPIO_PIN_4
extern SPI_HandleTypeDef hspi1;

class Display {
public:
    Display(Mal_queue *q_buffer);
    void init();
    void displayOff();
    void displayOn();
    void drawPixel(uint8_t x, uint8_t y, uint8_t color);
    void clearFramebuffer();
    void sendCommand(uint8_t command);
    void drawVoltage();
    void sendData(uint8_t *data);
    void CheckForData();
    void clearSRAM();
    void clearPage();

private:
    const uint8_t initCommands[14];
    uint8_t fbuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
    uint8_t clearIndex[SCREEN_WIDTH * SCREEN_HEIGHT];
    Mal_queue *framebuffer;
    uint8_t bufferArray[SCREEN_WIDTH];
    uint8_t activeArray[SCREEN_WIDTH];
};

#endif /* SRC_DISPLAY_H_ */
