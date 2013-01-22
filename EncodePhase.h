#ifndef __ENCODEPHASE_H
#define __ENCODEPHASE_H

#include "scanParams.h"

cv::Mat phase1Image, phase2Image, phase3Image;

cv::Mat toScreenSize(cv::Mat image);

void loadImages(ScanParams* scanParams);

void encodePhase(ScanParams* scanParams);

float averageBrightness(cv::Vec3b color);

float diff(float a, float b);

cv::Vec3b blend(cv::Vec3b pixel1, cv::Vec3b pixel2, int mode);

#endif