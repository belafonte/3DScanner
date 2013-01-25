#include "scanParams.h"

ScanParams::ScanParams(int inputHeight, int inputWidth)
	: calcHeight(inputHeight)
	, calcWidth(inputWidth)
	, noiseThreshold( 0.12)
	, zScale(130)
	, zSkew(24)
	, renderDetail(1) {	

	// allocate Memory for all Arrays
	mask = new bool *[calcHeight];
	for( int i = 0 ; i < calcHeight ; i++ )
		mask[i] = new bool[calcWidth];

	process = new bool *[calcHeight];
	for( int i = 0 ; i < calcHeight ; i++ )
		process[i] = new bool[calcWidth];

	phase = new float *[calcHeight] ;
	for( int i = 0 ; i < calcHeight ; i++ )
		phase[i] = new float[calcWidth];

	distance = new float *[calcHeight];
	for( int i = 0 ; i < calcHeight ; i++ )
		distance[i] = new float[calcWidth];

	depth = new float *[calcHeight];
	for( int i = 0 ; i < calcHeight ; i++ )
		depth[i] = new float[calcWidth];

	colors = new cv::Vec3b *[calcHeight];
	for( int i = 0 ; i < calcHeight ; i++ )
		colors[i] = new cv::Vec3b[calcWidth];
	
	names = new int *[calcHeight];
	for( int i = 0 ; i < calcHeight ; i++ )
		names[i] = new int[calcWidth];

	// Path to Images -- setting variable!
	this->setPath();

}


ScanParams::~ScanParams(void) { }

// <-- Setter and Getter Methods
std::string ScanParams::getPath() {
	return this->path;
}
void ScanParams::setPath() {
	this->path = PATH;
}

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
void ScanParams::setPhase(float value, int y, int x) {
	this->phase[y][x] = value;
}


float ScanParams::getDistance(int y, int x) {
	return this->distance[y][x];
}
void ScanParams::setDistance(float value, int y, int x) {
	this->distance[y][x] = value;
}


float ScanParams::getDepth(int y, int x) {
	return this->depth[y][x];
}
void ScanParams::setDepth(float value, int y, int x) {
	this->depth[y][x] = value;
}


 cv::Vec3b ScanParams::getColors(int y, int x) {
	return this->colors[y][x];
}
void ScanParams::setColors(cv::Vec3b value, int y, int x) {
	this->colors[y][x] = value;
}


int ScanParams::getNames(int y, int x) {
	return this->names[y][x];
}
void ScanParams::setNames(int value, int y, int x) {
	this->names[y][x] = value;
}

//runtime variables

float ScanParams::getNoiseThreshold() {
	return this->noiseThreshold;
}
void ScanParams::setNoiseThreshold(float value) {
	this->noiseThreshold;
}


float ScanParams::getZScale() {
	return this->zScale;
}
void ScanParams::setZScale(float value) {
	this->zScale;
}


float ScanParams::getZSkew() {
	return this->zSkew;
}
void ScanParams::setZSkew(float value) {
	this->zSkew;
}


int ScanParams::getRenderDetail() {
	return this->renderDetail;
}
void ScanParams::setRenderDetail(int value) {
	this->renderDetail;
}

// end -->