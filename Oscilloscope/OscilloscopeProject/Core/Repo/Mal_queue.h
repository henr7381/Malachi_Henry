/*
 * Seanqueue.h
 *
 *  Created on: Aug 12, 2023
 *      Author: docca
 */

#ifndef INC_MALQUEUE_H_
#define INC_MALQUEUE_H_

#include <cstdint>

struct packet
{
	int column;
	int height;
};

class Mal_queue
{
private:
	packet buffer[10];
	int16_t head;
	int16_t use_count;
public:
	Mal_queue();
	virtual ~Mal_queue();
	Mal_queue(const Mal_queue& other);

	bool Menqueue(packet msg);
	bool Mdequeue(packet* msg);
};

#endif
