#include "scanParams.h"

class AdditionalFunctions
{
public:
	AdditionalFunctions(void);
	~AdditionalFunctions(void);

	cv::Mat phase1Image, phase2Image, phase3Image;

	void loadImages();

	cv::Mat toScreenSize(cv::Mat image);
};

