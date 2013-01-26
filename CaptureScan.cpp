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
	Mat previewDist;
	Mat tmpImage;
	Mat projector;

	//Videoinput
	cv::VideoCapture capture = cv::VideoCapture(1);
	//verzerrung aufheben

	


	//initialwerte festsetzen

	int brightness = 50;
	int contrast = 50;
	int focus = 50;
	

	std::cout<<"3d-Scan vorbereitung startet"<<endl;
	cv::namedWindow("slider");
	cv::createTrackbar("helligkeit","slider",&brightness,100);
	cv::createTrackbar("kontrast","slider",&contrast,100);
	capture >> preview;
	cv::undistort(preview, previewDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());
	namedWindow("preview");
	

	//vorschau mit justierbarer helligkeit kontrast
	while(true){
		
		
		
		
		cv::getTrackbarPos("helligkeit","slider");
		cv::getTrackbarPos("kontrast","slider");
		
		
		

		
		capture.set(CV_CAP_PROP_CONTRAST,contrast-10);
		capture.set(CV_CAP_PROP_BRIGHTNESS,brightness-50);

			
		

		capture >> preview;
		cv::undistort(preview, previewDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());
		imshow("preview",previewDist);

		//vorschaubild
		projector = imread("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/vertical/testscreen.png");
		imshow("Projektor",projector);


		//esc to exit
		int key = waitKey(1);
		if(key==27){
			
			destroyWindow("preview");
			destroyWindow("Projektor");
			destroyWindow("slider");
			break;}


		
		
	}
	

	//phase1
	std::cout<<"beginn phase 1, bitte taste druecken"<<endl;
	projector = imread("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/vertical/i1.png");
	imshow("Projektor",projector);
	waitKey(0);
	Mat tmpImageDist;
	int i = 0;
	while(i<=3){
		
		capture >> tmpImage;
		cv::undistort(tmpImage, tmpImageDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());

		if(i==3){
			imwrite("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/captured/phase1.jpg",tmpImageDist);
			break;
		}

		i++;
		waitKey(10);
	}

	//phase2
	std::cout<<"beginn phase 2, bitte taste druecken"<<endl;
	projector = imread("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/vertical/i2.png");
	imshow("Projektor",projector);
	waitKey(0);
	i = 0;
	while(i<=3){

		capture >> tmpImage;
		cv::undistort(tmpImage, tmpImageDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());

		if(i==3){
			imwrite("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/captured/phase2.jpg",tmpImageDist);
			break;
		}

		i++;
		waitKey(10);
	}
	
	//phase3
	std::cout<<"beginn phase 3, bitte taste druecken"<<endl;
	projector = imread("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/vertical/i3.png");
	imshow("Projektor",projector);
	waitKey(0);
	i = 0;
	while(i<=3){

		capture >> tmpImage;
		cv::undistort(tmpImage, tmpImageDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());

		if(i==3){
			imwrite("C:/Users/Lukas/Downloads/ThreePhase-2-source/ThreePhase/img/captured/phase3.jpg",tmpImageDist);
			break;
		}

		i++;
		waitKey(10);
	}
	std::cout<<"ende des Scans, berechnung wird initialisiert..."<<endl;
	

	

	
	




}
