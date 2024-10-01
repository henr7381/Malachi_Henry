/*
 * Malachi Henry
 */

#ifndef REPO_INC_NEC_DRIVER_H_
#define REPO_INC_NEC_DRIVER_H_

#include "stdint.h"

// union for holding the received messages
static union {
	uint32_t fullRx;
	struct decodedMessage{
		uint8_t addr;
		uint8_t Naddr;
		uint8_t cmd;
		uint8_t Ncmd;
	} decodedMessage;
} message;

// No NEC packets are longer than 320ms/4 (80 ms)
#define INCOMING_RX_TIMEOUT (320u)

#endif /* REPO_INC_NEC_DRIVER_H_ */
