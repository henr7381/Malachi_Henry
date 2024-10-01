/*
 * queue.cpp
 *
 *  Created on: Aug 29, 2024
 *      Author: henr7381
 */

#include "../Inc/queue.h"
#include <cstdint>


queue::queue() {
	this->head = 0;
	this->use_count = 0;
}

queue::~queue() {
	// TODO Auto-generated destructor stub -- 3 attr, all explicit:: no effort needed.
}

queue::queue(const queue &other)
{
	this->head = other.head;
	this->use_count = other.use_count;
	for (int8_t n = 0; n < 10; n++)
	{
		this->buffer[n] = other.buffer[n];
	}
}

bool queue::enqueue(const uint32_t msg)
{
	bool successQ = false;
	if (use_count >= 8)
	{
		successQ = false;
	}
	else
	{
	   int16_t slot = (head + use_count) % 8;
	   buffer[slot] = msg;
	   use_count++;
	   successQ = true;
	}
	return successQ;
}

bool queue::dequeue(uint32_t* msg)
{
	bool successQ = false;
	if (use_count <= 0)
	{
		successQ = false;
	}
	else
	{
		*msg = buffer[head];
		head = (head + 1) % 8;
		use_count--;
		successQ = true;
	}
	return successQ;
}


