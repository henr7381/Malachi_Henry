/*
 * Malachi Henry
 *
 * Ram Health functions. There are functions to set RAM check values, and some to ensure they
 * are still intact.
 *
 */

#include "../Repo/Ram_Health.h"

void Ram_Health()
{
	static uint32_t barrier1 = 0xBADF00D;
	if (barrier1 != 0xBADF00D)
	{
		while(1){}
	}

	static uint32_t barrier2;
	if (barrier2 != 0)
	{
		while(1){}
	}

	if (*(uint16_t *) 1002 != 0xd300)
	{
		while(1){}
	}
}

void Ram_init()
{
	*(uint16_t *) 1002 = 0xACE;
}
