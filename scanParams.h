#ifndef __SCANPARAMS_H
#define __SCANPARAMS_H

// <-- GLOBAL VARIABLES SET BEFORE EXECUTE
#define _USE_MATH_DEFINES
#define SCREENHEIGHT 640
#define SCREENWIDTH 480
#define PATH "C:/Users/BEL/Uni/5. Semester/AVPRG/scannedPhotos/"

// end -->

// <-- global Library Bindings 

#include <string>
#include <cmath>
#include <queue>
#include <iostream>
#include <fstream>
#include <vector>

#include <opencv2/opencv.hpp>

// end-->

class ScanParams
{
private:
	// <-- const Variables once Set -> readonly
	std::string path;
	int calcWidth;
	int calcHeight;

	// end -->

	// <-- dynamic array
	// für die ganzen Variable mit index x, y

	bool **mask;
	bool **process;
	float **phase;
	float **distance;
	float **depth;
	cv::Vec3b **colors;
	int **names;

	// end -->

	// <-- runtime Variables 

	float noiseThreshold;
	float zScale;
	float zSkew;
	int renderDetail;

	// end -->
public:
	ScanParams(int calcWidth, int calcHeight);
	~ScanParams(void);

	// <-- Setter and Getter Methods
	std::string getPath();
	void setPath();
	int getCalcHeight();
	int getCalcWidth();

	int getMask(int y, int x);
	void setMask(bool value, int y, int x);

	int getProcess(int y, int x);
	void setProcess(bool value, int y, int x);

	float getPhase(int y, int x);
	void setPhase(float value, int y, int x);
	
	float getDistance(int y, int x);
	void setDistance(float value, int y, int x);

	float getDepth(int y, int x);
	void setDepth(float value, int y, int x);

	cv::Vec3b getColors(int y, int x);
	void setColors(cv::Vec3b value, int y, int x);

	int getNames(int y, int x);
	void setNames(int value, int y, int x);

	//runtime

	float getNoiseThreshold();
	void setNoiseThreshold(float value);

	float getZScale();
	void setZScale(float value);

	float getZSkew();
	void setZSkew(float value);

	int getRenderDetail();
	void setRenderDetail(int value);

	// end -->
};

#endif