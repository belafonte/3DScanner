#include <queue>
#include <opencv2/opencv.hpp>
#include "EncodedPixel.h"
#include "scanParams.h"

std::priority_queue<EncodedPixel*> toProcess;
long position;

void decodePhase(ScanParams* scanParams);

void decodePhase(int x, int y, float d, float r, ScanParams* scanParams);

void calcDepth(ScanParams* scanParams);