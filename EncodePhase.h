#ifndef __ENCODEPHASE_H
#define __ENCODEPHASE_H

#include "scanParams.h"

class EncodePhase
{
public:
	EncodePhase(void);
	~EncodePhase(void);

	cv::Mat phase1Image, phase2Image, phase3Image;

	cv::Mat toScreenSize(cv::Mat image);

	void loadImages();

	void encodePhase(ScanParams* scanParams);

	float averageBrightness(cv::Vec3b color);

	float diff(float a, float b);

	cv::Vec3b blend(cv::Vec3b pixel1, cv::Vec3b pixel2, int mode);

};

#endif