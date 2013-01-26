//zu tun
//
//gewaehlte kamera uebergeben
//
//hier werden einstellungen fuer die kamera getroffen und die phasenpatterns projiziert und die bilder der kamera gespeichert

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
	cv::namedWindow("preview");
	cv::createTrackbar("helligkeit","slider",&brightness,100);
	cv::createTrackbar("kontrast","slider",&contrast,100);

	//entzerren
	capture >> preview;
	cv::undistort(preview, previewDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());
	
	

	//vorschau mit justierbarer helligkeit kontrast
	while(true){
		
		cv::getTrackbarPos("helligkeit","slider");
		cv::getTrackbarPos("kontrast","slider");
		
		
		capture.set(CV_CAP_PROP_CONTRAST,contrast);
		capture.set(CV_CAP_PROP_BRIGHTNESS,brightness-50);

			
		capture >> preview;
		cv::undistort(preview, previewDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());
		imshow("preview",previewDist);


		//vorschaubild
		cv::namedWindow("Projektor");
		projector = imread("./vertical/testscreen.png");
		imshow("Projektor",projector);
		
		
		//esc to exit
		int key = waitKey(1);
		if(key==32){
			
			destroyWindow("preview");
			destroyWindow("Projektor");
			destroyWindow("slider");
			break;}
		
	}

	//Setup-Parameter

	cout<<"Geben sie nun bitte den ungefaehren Abstand von Projektor zur Kamera in cm ein"<<endl;
	float scale;
	cin>>scale;

	if(scale>=20 && scale<=300)
	{
		scanParams->setZScale(scale);
	}
	else
	{
		cout<<"Ungueltige Eingabe, es wird ein Standardwert verwendet"<<endl;
	}



	cout<<"Geben sie nun bitte den ungefaehren Winkel von Projektor zur Kamera in grad ein"<<endl;
	float skew;
	cin>>skew;

	if(skew>=5 && skew<=80)
	{
		scanParams->setZSkew(skew);
	}
	else
	{
		cout<<"Ungueltige Eingabe, es wird ein Standardwert verwendet"<<endl;
	}
	

	//phase1
	std::cout<<"beginn phase 1, bitte taste druecken"<<endl;
	projector = imread("./vertical/i1.png");
	imshow("Projektor",projector);
	waitKey(0);
	Mat tmpImageDist;
	int i = 0;
	while(i<=3){
		
		capture >> tmpImage;
		cv::undistort(tmpImage, tmpImageDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());

		if(i==3){
			imwrite("./captured/phase1.jpg",tmpImageDist);
			break;
		}

		i++;
		waitKey(10);
		
	}

	//phase2
	std::cout<<"beginn phase 2, bitte taste druecken"<<endl;
	projector = imread("./vertical/i2.png");
	imshow("Projektor",projector);
	waitKey(0);
	i = 0;
	while(i<=3){

		capture >> tmpImage;
		cv::undistort(tmpImage, tmpImageDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());

		if(i==3){
			imwrite("./captured/phase2.jpg",tmpImageDist);
			break;
		}

		i++;
		waitKey(10);
	}
	
	//phase3
	std::cout<<"beginn phase 3, bitte taste druecken"<<endl;
	projector = imread("./vertical/i3.png");
	imshow("Projektor",projector);
	waitKey(0);
	i = 0;
	while(i<=3){

		capture >> tmpImage;
		cv::undistort(tmpImage, tmpImageDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());

		if(i==3){
			imwrite("./captured/phase3.jpg",tmpImageDist);
			break;
		}

		i++;
		waitKey(10);
	}
	std::cout<<"ende des Scans, berechnung wird initialisiert..."<<endl;
	

	

	
	




}
