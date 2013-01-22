#ifndef __ENCODEDPIXEL_H
#define __ENCODEDPIXEL_H

#include "scanParams.h"

class EncodedPixel
{
public:
	EncodedPixel(int x, int y, float distance, float phase);
	~EncodedPixel(void);
public:
	int x, y;
	float distance, phase;
};

#endif