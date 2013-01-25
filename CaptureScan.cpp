#include "CaptureScan.h"

CaptureScan::CaptureScan(void) { }


CaptureScan::~CaptureScan(void) { }

void CaptureScan::createScanPictures() {


	cv::Mat projector(SCREENWIDTH, SCREENHEIGHT, CV_8UC3);
	cv::Mat tmpImage(SCREENWIDTH, SCREENHEIGHT, CV_8UC3);


	cv::namedWindow("Projector", CV_WINDOW_NORMAL);
	cv::setWindowProperty("Projector", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

	int i = 0;
	while(i<3) {
		projector = cv::imread(PATH"vertical/" + i);
		imshow("Projecor", projector);


		cv::VideoCapture *capture = new cv::VideoCapture(1);

		cv::imwrite(PATH"captured/phase" + i, capture->grab());
	i++;
	}
}
