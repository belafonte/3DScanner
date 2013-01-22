#include "DecodePhase.h"

void DecodePhase::decodePhase(ScanParams* scanParams) {
	int startX = scanParams->getCalcWidth() / 2;		// �berpr�fen ob variable sich �ndert!
	int startY = scanParams->getCalcHeight() / 2;


	// rausfinden was da los ist!
	this->toProcess.push(new EncodedPixel(startX, startY, 0, scanParams->getPhase(startY, startX)));

	while (!toProcess.empty()) {
		EncodedPixel const cur =  (EncodedPixel) *toProcess.top();  // vielleicht fehler!
		toProcess.pop();

		int x = cur.x;
		int y = cur.y;

		if (scanParams->getProcess(x, y)) {
			scanParams->setPhase(cur.phase, y, x);
			scanParams->setProcess(false, y, x);
			float d = cur.distance;
			float r = scanParams->getPhase(y, x);

			if(y > 0) {
				DecodePhase::decodePhase(x, y-1, d, r, scanParams);
			} 
			if (y < scanParams->getCalcHeight() - 1) {
				DecodePhase::decodePhase(x, y+1, d, r, scanParams);
			}
			if (x > 0) {
				DecodePhase::decodePhase(x-1, y, d, r, scanParams);
			}
			if (x < scanParams->getCalcWidth() - 1) {
				DecodePhase::decodePhase(x+1, y, d, r, scanParams);
			}
		}
	}
}

void DecodePhase::decodePhase(int x, int y, float d, float r, ScanParams* scanParams) {
	if(scanParams->getProcess(y, x)) {
		float diff = scanParams->getPhase(y, x) - (r - (int) r);  // �berpr�fen ob variable sich �ndert
		if(diff > 0.5) 
			diff--;
		if(diff < 0.5) 
			diff++;
		toProcess.push(new EncodedPixel(x, y, d + scanParams->getDistance(y, x), r + diff));		// ebenso rausfinden mit priority queue!
	}
} 

void DecodePhase::calcDepth(ScanParams* scanParams) {
	for (int y = 0; y < scanParams->getCalcHeight(); y+=scanParams->getRenderDetail()) {
		float planePhase = 0.5f - (y - (scanParams->getCalcHeight() / 2.f)) / scanParams->getZSkew();		//variable sich �ndert
		for (int x = 0; x < scanParams->getCalcWidth(); x += scanParams->getRenderDetail()) {
			if (!scanParams->getMask(y, x)) {
				scanParams->setDepth((scanParams->getPhase(y, x) - planePhase) * scanParams->getZScale(),y ,x);
			}
		}
	}
}