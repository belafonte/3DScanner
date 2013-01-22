#include "EncodedPixel.h"

EncodedPixel::EncodedPixel(int x, int y, float distance, float phase)
	: x(x)
	, y(y)
	, distance(distance)
	, phase(phase) { }

EncodedPixel::~EncodedPixel(void) { } // delete Priority Queue!
