#include "EncodePhase.h"

EncodePhase::EncodePhase(void) { }

EncodePhase::~EncodePhase(void) { }

cv::Mat EncodePhase::toScreenSize(cv::Mat image) {
	if (image.cols > SCREENWIDTH) 
		cv::resize(image, image,cv::Size(SCREENWIDTH, (image.rows * SCREENHEIGHT) / image.cols));
	if (image.rows > SCREENHEIGHT)
		cv::resize(image, image, cv::Size((image.cols * SCREENHEIGHT / image.rows), SCREENHEIGHT));
	return image;
}

void EncodePhase::loadImages() {
	this->phase1Image = EncodePhase::toScreenSize(cv::imread(PATH"phase1.jpg"));
	this->phase2Image = EncodePhase::toScreenSize(cv::imread(PATH"phase2.jpg"));
	this->phase3Image = EncodePhase::toScreenSize(cv::imread(PATH"phase3.jpg"));
}

void EncodePhase::encodePhase( ScanParams* scanParams) {
	float sqrt3 = std::sqrt(3.f);
	for(int y = 0; y < scanParams->getCalcHeight(); y++) {
		for(int x = 0; x < scanParams->getCalcWidth(); x++) {

			cv::Vec3b color1 = phase1Image.at<cv::Vec3b>(y,x);
			cv::Vec3b color2 = phase2Image.at<cv::Vec3b>(y,x);
			cv::Vec3b color3 = phase3Image.at<cv::Vec3b>(y,x);

			float phase1 = EncodePhase::averageBrightness(color1);
			float phase2 = EncodePhase::averageBrightness(color2);
			float phase3 = EncodePhase::averageBrightness(color3);

			float phaseRange = std::max<float>(std::max<float>(phase1, phase2), phase3)
				- std::min<float>(std::min<float>(phase1, phase2), phase3);

			// nicht sicher über <= operator!
			scanParams->setMask(phaseRange <= scanParams->getNoiseThreshold(), y, x);
			scanParams->setProcess(!(scanParams->getMask(y, x)), y, x);
			scanParams->setDistance(phaseRange, y, x);
			scanParams->setPhase(std::atan2(sqrt3 * (phase1 - phase3), 2 * phase2 - phase1 - phase3) / (2 * M_PI), y, x);

			//HErausfinden wie blendColor in OPENCV funktioniert!
			scanParams->setColors((blend(blend(color1, color2, 1), color3, 1)), y, x);

			for(int y = 1; y < scanParams->getCalcHeight() -1; y++) {			// überprüfen ob calcHeight geändert wird!
				for (int x = 1; x < scanParams->getCalcWidth() -1; x ++) {		// same!
					if (!scanParams->getMask(y, x)) {
						scanParams->setDistance(
							EncodePhase::diff(scanParams->getPhase(y, x), scanParams->getPhase(y, x - 1)) +
							EncodePhase::diff(scanParams->getPhase(y, x), scanParams->getPhase(y, x + 1)) +
							EncodePhase::diff(scanParams->getPhase(y, x), scanParams->getPhase(y - 1, x)) +
							EncodePhase::diff(scanParams->getPhase(y, x), scanParams->getPhase(y + 1, x)) / 
							(scanParams->getDistance(y, x)), 
						y, x);
					}
				}
			}
		}
	}
}

float EncodePhase::averageBrightness(cv::Vec3b color) {
	return (color[0] + color[1] + color[2]) / (255 * 3);
}

float EncodePhase::diff(float a, float b) {
	float d = a < b ? b - a : a - b;
	return d < .5 ? d : 1 - d;
}

cv::Vec3b EncodePhase::blend(cv::Vec3b pixel1, cv::Vec3b pixel2, int mode) {
	cv::Vec3b out = 0;
	if (mode == 1) {
		int tmpPixel1 = EncodePhase::averageBrightness(pixel1); 
		int tmpPixel2 = EncodePhase::averageBrightness(pixel2);
		out = std::max(tmpPixel1, tmpPixel2);
	}
	return out;
}