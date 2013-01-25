#include "AdditionalFunctions.h"


AdditionalFunctions::AdditionalFunctions(void) { }


AdditionalFunctions::~AdditionalFunctions(void) { }

cv::Mat AdditionalFunctions::toScreenSize(cv::Mat image) {
	if (image.cols > SCREENWIDTH) 
		cv::resize(image, image,cv::Size(SCREENWIDTH,
		(image.rows * SCREENHEIGHT) / image.cols));

	if (image.rows > SCREENHEIGHT)
		cv::resize(image, image,
		cv::Size((image.cols * SCREENHEIGHT / image.rows), SCREENHEIGHT));
	return image;
}

void AdditionalFunctions::loadImages() {
	this->phase1Image = AdditionalFunctions::toScreenSize(cv::imread(PATH"phase1.jpg"));
	this->phase2Image = AdditionalFunctions::toScreenSize(cv::imread(PATH"phase2.jpg"));
	this->phase3Image = AdditionalFunctions::toScreenSize(cv::imread(PATH"phase3.jpg"));
}
