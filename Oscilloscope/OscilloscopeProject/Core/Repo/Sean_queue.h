/*
 * Seanqueue.h
 *
 *  Created on: Aug 12, 2023
 *      Author: docca
 */



#ifndef INC_SEANQUEUE_H_
#define INC_SEANQUEUE_H_

#include <cstdint>

class Sean_queue {
private:
	int16_t buffer[100];  /* Too big - done for demo purposes */
	int16_t head;
	int16_t use_count;
public:
	Sean_queue();
	virtual ~Sean_queue();
	Sean_queue(const Sean_queue& other);

	bool enqueue(int16_t msg);
	bool dequeue(int16_t* msg);
};

#endif /* INC_SEANQUEUE_H_ */
