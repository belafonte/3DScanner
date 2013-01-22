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


int ScanParams::getProcess(int y, int x) {
	return this->process[y][x];
}
void ScanParams::setProcess(bool value, int y, int x) {
	this->process[y][x] = value;
}


float ScanParams::getPhase(int y, int x) {
	return this->phase[y][x];
}
void ScanParams::setPhase(bool value, int y, int x) {
	this->phase[y][x] = value;
}


float ScanParams::getDistance(int y, int x) {
	return this->distance[y][x];
}
void ScanParams::setDistance(bool value, int y, int x) {
	this->distance[y][x] = value;
}


float ScanParams::getDepth(int y, int x) {
	return this->depth[y][x];
}
void ScanParams::setDepth(bool value, int y, int x) {
	this->depth[y][x] = value;
}


 cv::Vec3b ScanParams::getColors(int y, int x) {
	return this->colors[y][x];
}
void ScanParams::setColors(bool value, int y, int x) {
	this->colors[y][x] = value;
}


int ScanParams::getNames(int y, int x) {
	return this->names[y][x];
}
void ScanParams::setNames(bool value, int y, int x) {
	this->names[y][x] = value;
}

//runtime variables
float ScanParams::getNoiseThreshold() {
	return this->noiseThreshold;
}
void ScanParams::setNoiseThreshold(bool value) {
	this->noiseThreshold;
}


float ScanParams::getZScale() {
	return this->zScale;
}
void ScanParams::setZScale(bool value) {
	this->zScale;
}


float ScanParams::getZSkew() {
	return this->zSkew;
}
void ScanParams::setZSkew(bool value) {
	this->zSkew;
}


int ScanParams::getRenderDetail() {
	return this->renderDetail;
}
void ScanParams::setRenderDetail(bool value) {
	this->renderDetail;
}

// end -->