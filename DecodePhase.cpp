//rekursiver sich aus der mitte fortpflanzender algorithmus
//der die daten aus EncodePhase benutzt und sie in encodedPixel schreibt

#include "DecodePhase.h"

DecodePhase::DecodePhase(void) { }

DecodePhase::~DecodePhase(void) { }

void DecodePhase::decodePhase(ScanParams* scanParams) {
	int startX = scanParams->getCalcWidth() / 2;
	int startY = scanParams->getCalcHeight() / 2;

	this->toProcess.push_back(
		new EncodedPixel(startX, startY, scanParams->getPhase(startY, startX))
	);

	scanParams->setProcess(false, startY, startX);

	while (!toProcess.empty()) {
		EncodedPixel cur =  *toProcess.back();
		toProcess.pop_back();

		int x = cur.x;
		int y = cur.y;
	
		float r = scanParams->getPhase(y, x);

		if(y > 0) {
			DecodePhase::decodePhase(x, y-1, r, scanParams);
		} 
		if (y < scanParams->getCalcHeight() - 1) {
			DecodePhase::decodePhase(x, y+1, r, scanParams);
		}
		if (x > 0) {
			DecodePhase::decodePhase(x-1, y, r, scanParams);
		}
		if (x < scanParams->getCalcWidth() - 1) {
			DecodePhase::decodePhase(x+1, y, r, scanParams);
		}
	}
}

void DecodePhase::decodePhase(int x, int y, float r, ScanParams* scanParams) {
	if(scanParams->getProcess(y, x)) {
		float diff = (scanParams->getPhase(y, x) - (r - (int) r));

		if(diff > 0.5f) diff--;
		if(diff < -0.5f) diff++;

		scanParams->setPhase((r + diff), y, x);
		scanParams->setProcess(false, y, x);
		toProcess.push_back(new EncodedPixel(x, y, r + diff));
	}
} 

void DecodePhase::calcDepth(ScanParams* scanParams) {
	for (int y = 0; y < scanParams->getCalcHeight();
		y+=scanParams->getRenderDetail()) {
		float planePhase = 0.5f - (y - (scanParams->getCalcHeight() / 2.f))
			/ scanParams->getZSkew();

		for (int x = 0; x < scanParams->getCalcWidth(); 
			 x += scanParams->getRenderDetail()) {

			if (!scanParams->getMask(y, x)) {
				scanParams->setDepth((scanParams->getPhase(y, x) 
			  - planePhase) * scanParams->getZScale(),y ,x);
			}

		}
	}
}