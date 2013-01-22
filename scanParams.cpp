#include "scanParams.h"

ScanParams::ScanParams(int inputWidth, int inputHeight)
	: calcWidth(inputWidth)
	, calcHeight(inputHeight)
	, noiseThreshold(1)
	, zScale(1)
	, zSkew(1)
	, renderDetail(1) {	

	mask = new bool *[calcHeight] ;
	for( int i = 0 ; i < calcHeight ; i++ )
		mask[i] = new bool[calcWidth];

	process = new bool *[calcHeight] ;
	for( int i = 0 ; i < calcHeight ; i++ )
		process[i] = new bool[calcWidth];

	phase = new float *[calcHeight] ;
	for( int i = 0 ; i < calcHeight ; i++ )
		phase[i] = new float[calcWidth];

	distance = new float *[calcHeight]();
	for( int i = 0 ; i < calcHeight ; i++ )
		distance[i] = new float[calcWidth]();

	depth = new float *[calcHeight]() ;
	for( int i = 0 ; i < calcHeight ; i++ )
		depth[i] = new float[calcWidth]();

	colors = new cv::Vec3b *[calcHeight]();
	for( int i = 0 ; i < calcHeight ; i++ )
		colors[i] = new cv::Vec3b[calcWidth]();
	
	names = new int *[calcHeight]() ;
	for( int i = 0 ; i < calcHeight ; i++ )
		names[i] = new int[calcWidth]();

}


ScanParams::~ScanParams(void) { }

// <-- Setter and Getter Methods

int ScanParams::getCalcHeight() {
	return this->calcHeight;
}
int ScanParams::getCalcWidth() {
	return this->calcWidth;
}

int ScanParams::getMask(int y, int x) {
	return this->mask[y][x];
}
void ScanParams::setMask(bool value, int y, int x) {
	this->mask[y][x] = value;
}





// end -->