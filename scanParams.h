// <-- GLOBAL VARIABLES SET BEFORE EXECUTE

#define SCREENHEIGHT 1920
#define SCREENWIDTH 1080
#define PATH "insertPathHere"

// end -->

// <-- global Library Bindings 

#include <opencv2/opencv.hpp>
#include <string>

// end-->

class ScanParams
{
private:
	// <-- const Variables once Set -> readonly

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

	int getCalcHeight();
	int getCalcWidth();

	int getMask(int y, int x);
	int setMask(bool value, int y, int x);
	// end -->
};