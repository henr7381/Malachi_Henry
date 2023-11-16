/*
 * Malachi Henry
 *
 * This object gets raw ADC readings from the queue and converts them into pixel heights.
 * See [../Repo/Mal_queue.cpp] for an explanation of the 'packet' datatype.
 *
 */


#include "../Repo/Mal_queue.h"
#include "../Repo/Sean_queue.h"
#include "../Repo/RawToPixel.h"




rawDataToPixelConverter::rawDataToPixelConverter(Sean_queue *q_raw, Mal_queue *q_buffer)
{
	this -> q_raw = q_raw;
	this -> q_buffer = q_buffer;
	lineCount = 0;
	newestMeasurement = 0;
	height = 0;
	mvMeasurement = 0;
	outbound.column = 0;
	outbound.height = 0;
}


rawDataToPixelConverter::~rawDataToPixelConverter() {
	// TODO Auto-generated destructor stub
}


void rawDataToPixelConverter::rawDataToPixel(void)
{
	if (q_raw->dequeue(&newestMeasurement))
	{
		// ADC raw to millivolts
		mvMeasurement = ((newestMeasurement * (3.3 / 4096)) * 1000);

		// Millivolts to a pixel location within my set range (1 - 56)
		height = ((mvMeasurement / (float)(3300)) * 56);

		outbound.column = lineCount;
		outbound.height = height;

		if(q_buffer->Menqueue(outbound))
		{
			lineCount++;
			if (lineCount > 101)
			{
				lineCount = 0;
			}
		}
	}
}






