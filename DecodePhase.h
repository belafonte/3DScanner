#include <queue>
#include <opencv2/opencv.hpp>
#include "EncodedPixel.h"
#include "scanParams.h"

std::priority_queue<EncodedPixel*> toProcess;
long position;

void dencodePhase(struct ScanParams* scanParams);

void dencodePhase(int x, int y, float d, float r, struct ScanParams* scanParams);

void calcDepth(struct ScanParams* scanParams);