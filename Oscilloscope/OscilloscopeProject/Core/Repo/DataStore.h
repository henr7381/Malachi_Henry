/*
 * DataStore.h
 *
 *  Created on: Oct 8, 2023
 *      Author: Franc
 */

#include "main.h"
#ifndef REPO_DATASTORE_H_
#define REPO_DATASTORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

class DataStore{
private:
	int16_t trigger_level;
	int8_t checkspot;
	int16_t bucket;
public:
	DataStore();
	void updatedata();

	uint8_t DATAREADY;

	void setTrigger(int16_t newTrigger);
};

#ifdef __cplusplus
}
#endif

#endif /* REPO_DATASTORE_H_ */
