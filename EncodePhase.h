#define _USE_MATH_DEFINES
#include "scanParams.h"

cv::Mat phase1Image, phase2Image, phase3Image;

cv::Mat toScreenSize(cv::Mat image);

void loadImages(struct ScanParams* scanParams);

void encodePhase(struct ScanParams* scanParams);

float averageBrightness(cv::Vec3b color);

float diff(float a, float b);

cv::Vec3b blend(cv::Vec3b pixel1, cv::Vec3b pixel2, int mode);