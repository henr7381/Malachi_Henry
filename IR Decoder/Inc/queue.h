/*
 * queue.h
 *
 *  Created on: Aug 29, 2024
 *      Author: henr7381
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <cstdint>



class queue
{
private:
	uint32_t buffer[10];
	int32_t head;
	int32_t use_count;
public:
	queue();
	virtual ~queue();
	queue(const queue& other);

	bool enqueue(uint32_t msg);
	bool dequeue(uint32_t* msg);
};


#endif /* INC_QUEUE_H_ */
