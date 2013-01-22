#define SCREENHEIGHT 1920
#define SCREENWIDTH 1080

#include <opencv2/opencv.hpp>
#include <string>


struct ScanParams {

	std::string path;

	int calcWidth;
	int calcHeight;

	// change to c++ vector! ---->
	// change dynamic array!
	float *phase2 = new float[calcHeight];
	float phase[SCREENHEIGHT][SCREENWIDTH];
	float distance[SCREENHEIGHT][SCREENWIDTH];
	float depth[SCREENHEIGHT][SCREENWIDTH];
	bool mask[SCREENHEIGHT][SCREENWIDTH];
	bool process[SCREENHEIGHT][SCREENWIDTH];
	cv::Vec3b colors[SCREENHEIGHT][SCREENWIDTH];
	int names[SCREENHEIGHT][SCREENWIDTH];

	// <-----

	float noiseThreshold;
	float zScale;
	float zSkew;
	int renderDetail;
};