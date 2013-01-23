#ifndef __ENCODEDPIXEL_H
#define __ENCODEDPIXEL_H

#include "scanParams.h"

class EncodedPixel
{
public:
	EncodedPixel(int x, int y, float phase);
	~EncodedPixel(void);

	int x, y;
	float phase; 
};

#endif