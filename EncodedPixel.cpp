#include "EncodedPixel.h"

EncodedPixel::EncodedPixel(int inputX, int inputY, float inputDistance, float inputPhase)
	: x(inputX)
	, y(inputY)
	, distance(inputDistance)
	, phase(inputPhase) { }

EncodedPixel::~EncodedPixel(void) { } // delete Priority Queue!
