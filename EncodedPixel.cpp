#include "EncodedPixel.h"

EncodedPixel::EncodedPixel(int inputX, int inputY, float inputPhase)
	: x(inputX)
	, y(inputY)
	, phase(inputPhase) { }

EncodedPixel::~EncodedPixel(void) { } // delete Priority Queue!
