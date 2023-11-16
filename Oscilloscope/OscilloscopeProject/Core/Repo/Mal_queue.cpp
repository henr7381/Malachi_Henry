/*
 * Seanqueue.cpp
 *
 *  Created on: Aug 12, 2023
 *      Author: carrolls@trine.edu
 *
 *  Malachi Henry
 *
 *  This is a modified version of the Sean_queue class. It is techinally useless at this point,
 *  but I'm too tired to change the uses of this class back into Sean_queues. I defined a custom
 *  datatype called a "packet" that has a column and height for a pixel, and (x, y) coordinate if
 *  you will. This is a remnant of a time when Nate ensured me he'd be able to plot a pixel based
 *  on a coordinate. Turns out there's an autoscroll feature so you only need the height. The
 *  column will always be zero.
 */

#include "../Repo/Mal_queue.h"
#include <cstdint>


Mal_queue::Mal_queue() {
	this->head = 0;
	this->use_count = 0;
}

Mal_queue::~Mal_queue() {
	// TODO Auto-generated destructor stub -- 3 attr, all explicit:: no effort needed.
}

Mal_queue::Mal_queue(const Mal_queue &other)
{
	this->head = other.head;
	this->use_count = other.use_count;
	for (int8_t n = 0; n < 10; n++)
	{
		this->buffer[n] = other.buffer[n];
	}
}

bool Mal_queue::Menqueue(const packet msg)
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

bool Mal_queue::Mdequeue(packet* msg)
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



