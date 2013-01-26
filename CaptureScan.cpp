//zu tun
//distort variablen uebergeben
//gewaehlte kamera uebergeben
//evtl gewaehlte aufloesung uebergeben


#include "CaptureScan.h"

CaptureScan::CaptureScan(void) { }


CaptureScan::~CaptureScan(void) { }


using namespace cv;
using namespace std;


void CaptureScan::createScanPictures(ScanParams *scanParams) {


	//Mat erzeugen
	cv::Mat preview;
	Mat tmpImage;
	Mat projector;

	//Videoinput
	cv::VideoCapture capture = cv::VideoCapture(1);
	//initialwerte festsetzen
	int brightness = 20;
	int contrast = 20;
	int gain = 5;
	int gamma = 10;

	std::cout<<"3d-Scan vorbereitung startet"<<endl;
	cv::namedWindow("slider");
	cv::createTrackbar("helligkeit","slider",&brightness,100);
	cv::createTrackbar("kontrast","slider",&contrast,100);
	cv::createTrackbar("gain","slider",&gain,100);
	cv::createTrackbar("gain","slider",&gamma,100);
	capture >> preview;
	namedWindow("preview");
	

	//vorschau mit justierbarer helligkeit kontrast
	while(true){
		
		
		
		
		cv::getTrackbarPos("helligkeit","slider");
		cv::getTrackbarPos("kontrast","slider");
		cv::getTrackbarPos("gain","slider");
		cv::getTrackbarPos("gamma","slider");

		capture.set(CV_CAP_PROP_GAMMA,contrast);
		capture.set(CV_CAP_PROP_GAIN,contrast);
		capture.set(CV_CAP_PROP_CONTRAST,contrast);
		capture.set(CV_CAP_PROP_BRIGHTNESS,brightness);
		capture >> preview;
		imshow("preview",preview);

		//vorschaubild
		projector = imread("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/vertical/i1.png");
		imshow("Projektor",projector);


		//esc to exit
		int key = waitKey(1);
		if(key==27){
			
			destroyWindow("preview");
			destroyWindow("Projektor");
			break;}


		
		
	}
	

	//phase1
	projector = imread("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/vertical/i1.png");
	imshow("Projektor",projector);
	waitKey(0);
	int i = 0;
	while(i<=3){
		
		capture >> tmpImage;

		if(i==3){
			imwrite("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/captured/phase1.jpg",tmpImage);
			break;
		}

		i++;
		waitKey(10);
	}

	//phase2
	projector = imread("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/vertical/i2.png");
	imshow("Projektor",projector);
	waitKey(0);
	i = 0;
	while(i<=3){

		capture >> tmpImage;

		if(i==3){
			imwrite("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/captured/phase2.jpg",tmpImage);
			break;
		}

		i++;
		waitKey(10);
	}
	
	//phase3
	projector = imread("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/vertical/i3.png");
	imshow("Projektor",projector);
	waitKey(0);
	i = 0;
	while(i<=3){

		capture >> tmpImage;

		if(i==3){
			imwrite("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/captured/phase3.jpg",tmpImage);
			break;
		}

		i++;
		waitKey(10);
	}
	
	

	

	
	




}
