#include "EncodePhase.h"
#include <cmath>
#include <string>

cv::Mat toScreenSize(cv::Mat image) {
	if (image.cols > SCREENWIDTH) 
		cv::resize(image, image,cv::Size(SCREENWIDTH, (image.rows * SCREENHEIGHT) / image.cols));
	if (image.rows > SCREENHEIGHT)
		cv::resize(image, image, cv::Size((image.cols * SCREENHEIGHT / image.rows), SCREENHEIGHT));
	return image;
}

void loadImages(struct ScanParams* scanParams) {
	phase1Image = toScreenSize(cv::imread(scanParams->path + "phase1.jpg"));
	phase2Image = toScreenSize(cv::imread(scanParams->path + "phase2.jpg"));
	phase3Image = toScreenSize(cv::imread(scanParams->path + "phase3.jpg"));
}

void encodePhase(struct ScanParams* scanParams) {
	float sqrt3 = std::sqrt(3.f);
	for(int y = 0; y < scanParams->calcHeight; y++) {
		for(int x = 0; x < scanParams->calcWidth; x++) {

			cv::Vec3b color1 = phase1Image.at<cv::Vec3b>(y,x);
			cv::Vec3b color2 = phase2Image.at<cv::Vec3b>(y,x);
			cv::Vec3b color3 = phase3Image.at<cv::Vec3b>(y,x);

			float phase1 = averageBrightness(color1);
			float phase2 = averageBrightness(color2);
			float phase3 = averageBrightness(color3);

			float phaseRange = std::max<float>(std::max<float>(phase1, phase2), phase3)
				- std::min<float>(std::min<float>(phase1, phase2), phase3);

			// nicht sicher über <= operator!
			scanParams->mask[y][x] = phaseRange <= scanParams->noiseThreshold;
			scanParams->process[y][x] = !scanParams->mask[y][x];
			scanParams->distance[y][x] = phaseRange;
			scanParams->phase[y][x] = std::atan2(sqrt3 * (phase1 - phase3), 2 * phase2 - phase1 - phase3) / (2 * M_PI);

			//HErausfinden wie blendColor in OPENCV funktioniert!
			scanParams->colors[y][x] = blend(blend(color1, color2, 1), color3, 1);

			for(int y = 1; y < scanParams->calcHeight -1; y++) {			// überprüfen ob calcHeight geändert wird!
				for (int x = 1; x < scanParams->calcWidth -1; x ++) {		// same!
					if (!scanParams->mask[y][x]) {
						scanParams->distance[y][x] = (
							diff(scanParams->phase[y][x], scanParams->phase[y][x - 1]) +
							diff(scanParams->phase[y][x], scanParams->phase[y][x + 1]) +
							diff(scanParams->phase[y][x], scanParams->phase[y - 1][x]) +
							diff(scanParams->phase[y][x], scanParams->phase[y + 1][x])) / scanParams->distance[y][x];
					}
				}
			}
		}
	}
}

float averageBrightness(cv::Vec3b color) {
	return (color[0] + color[1] + color[2]) / (255 * 3);
}

float diff(float a, float b) {
	float d = a < b ? b - a : a - b;
	return d < .5 ? d : 1 - d;
}

cv::Vec3b blend(cv::Vec3b pixel1, cv::Vec3b pixel2, int mode) {
	cv::Vec3b out = 0;
	if (mode == 1) {
		int tmpPixel1 = averageBrightness(pixel1); 
		int tmpPixel2 = averageBrightness(pixel2);
		out = std::max(tmpPixel1, tmpPixel2);
	}
	return out;
}