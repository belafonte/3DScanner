#ifndef __DECODEPHASE_H
#define __DECODEPHASE_H

#include "EncodedPixel.h"
#include "scanParams.h"

class DecodePhase
{
public:
	DecodePhase(void);
	~DecodePhase(void);

	std::priority_queue<EncodedPixel*> toProcess;

	void decodePhase(ScanParams* scanParams);

	void decodePhase(int x, int y, float d, float r, ScanParams* scanParams);

	void calcDepth(ScanParams* scanParams);

};
#endif