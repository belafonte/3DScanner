#include "DecodePhase.h"

void dencodePhase(struct ScanParams* scanParams) {
	int startX = scanParams->calcWidth / 2;		// überprüfen ob variable sich ändert!
	int startY = scanParams->calcHeight / 2;


	// rausfinden was da los ist!
	toProcess.push(new EncodedPixel(startX, startY, 0, scanParams->phase[startY][startX]));

	while (!toProcess.empty()) {
		EncodedPixel const cur =  (EncodedPixel) *toProcess.top();  // vielleicht fehler!
		toProcess.pop();

		int x = cur.x;
		int y = cur.y;

		if (scanParams->process[y][x]) {
			scanParams->phase[y][x] = cur.phase;
			scanParams->process[y][x] = false;
			float d = cur.distance;
			float r = scanParams->phase[y][x];

			if(y > 0) {
				dencodePhase(x, y-1, d, r, scanParams);
			} 
			if (y < scanParams->calcHeight-1) {
				dencodePhase(x, y+1, d, r, scanParams);
			}
			if (x > 0) {
				dencodePhase(x-1, y, d, r, scanParams);
			}
			if (x < scanParams->calcWidth-1) {
				dencodePhase(x+1, y, d, r, scanParams);
			}
		}
	}
}

void decodePhase(int x, int y, float d, float r, struct ScanParams* scanParams) {
	if(scanParams->process[y][x]) {
		float diff = scanParams->phase[y][x] - (r - (int) r);  // überprüfen ob variable sich ändert
		if(diff > 0.5) 
			diff--;
		if(diff < 0.5) 
			diff++;
		toProcess.push(new EncodedPixel(x, y, d + scanParams->distance[y][x], r + diff));		// ebenso rausfinden mit priority queue!
	}
} 

void calcDepth(struct ScanParams* scanParams) {
	for (int y = 0; y < scanParams->calcHeight; y+=scanParams->renderDetail) {
		float planePhase = 0.5 - (y - (scanParams->calcHeight / 2)) / scanParams->zSkew;		//variable sich ändert
		for (int x = 0; x < scanParams->calcWidth; x += scanParams->renderDetail) {
			if (!scanParams->mask[y][x]) {
				scanParams->depth[y][x] = (scanParams->phase[x][y] - planePhase) * scanParams->zScale;
			}
		}
	}
}