
#include "../Repo/Mal_queue.h"

#ifndef REPO_RAWTOPIXEL_H_
#define REPO_RAWTOPIXEL_H_

class rawDataToPixelConverter
{
public:
	rawDataToPixelConverter(Sean_queue *q_raw, Mal_queue *q_buffer);
	void rawDataToPixel();
	virtual ~rawDataToPixelConverter();
	rawDataToPixelConverter (const rawDataToPixelConverter &other);

private:
	Sean_queue *q_raw;
	Mal_queue *q_buffer;
	uint32_t lineCount;
	int16_t newestMeasurement;
	int16_t height;
	int16_t mvMeasurement;
	packet outbound;
};
#endif /* REPO_RAWTOPIXEL_H_ */
