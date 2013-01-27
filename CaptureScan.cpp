
//
//hier werden einstellungen fuer die kamera getroffen, phasenpatterns projiziert und die bilder der kamera gespeichert

#include "CaptureScan.h"

CaptureScan::CaptureScan(void) { }


CaptureScan::~CaptureScan(void) { }




void CaptureScan::createScanPictures(ScanParams *scanParams) {


	//Mat erzeugen
	cv::Mat preview;
	cv::Mat previewDist;
	cv::Mat tmpImage;
	cv::Mat projector;

	//Videoinput
	cv::VideoCapture capture = cv::VideoCapture(1);
	


	//initialwerte festsetzen

	int brightness = 50;
	int contrast = 50;
	int focus = 50;
	int anzahlAufrufe=2;

	std::cout<<"3d-Scan vorbereitung startet"<<std::endl;
	cv::namedWindow("slider",CV_WINDOW_AUTOSIZE);
	cv::namedWindow("preview",CV_WINDOW_AUTOSIZE);
	cv::resizeWindow("slider",300,80);
	
	cv::createTrackbar("helligkeit","slider",&brightness,100);
	cv::createTrackbar("kontrast","slider",&contrast,100);

	//entzerren
	capture >> preview;
	cv::undistort(preview, previewDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());
	
	//vorschaubild
	cv::namedWindow("Projektor",CV_WINDOW_NORMAL);
	projector = cv::imread("./vertical/testscreen.png");
	

	//vorschau mit justierbarer helligkeit kontrast
	while(true){
		
		cv::getTrackbarPos("helligkeit","slider");
		cv::getTrackbarPos("kontrast","slider");
		
		
		capture.set(CV_CAP_PROP_CONTRAST,contrast);
		capture.set(CV_CAP_PROP_BRIGHTNESS,brightness-50);

			
		capture >> preview;
		cv::undistort(preview, previewDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());

		//Fadenkreuz zur Mittelpunktausrichtung
		cv::line(previewDist,cv::Point(315,0),cv::Point(315,480),10);
		cv::line(previewDist,cv::Point(640,235),cv::Point(0,235),10);

		
		//kameravorschau
		cv::imshow("preview",previewDist);
		
		
		int key = cv::waitKey(2);

		//fullscreen fuer projektorbild
		if(key==102)
		{
			
			if(anzahlAufrufe%2==0){
			cv::setWindowProperty("Projektor",CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
			}

			else{
			cv::setWindowProperty("Projektor",CV_WINDOW_NORMAL,CV_WINDOW_NORMAL);
			}

			anzahlAufrufe++;
		}

		//projektorvorschau
		cv::imshow("Projektor",projector);
		
		//esc to exit
		
		if(key==32){
			
			cv::destroyWindow("preview");
			cv::destroyWindow("slider");
			break;}
		
	}
	

	//Setup-Parameter

	std::cout<<"Geben sie nun bitte den ungefaehren Abstand von Projektor zur Kamera in cm ein"<<std::endl;
	float scale;
	std::cin>>scale;

	if(scale>=20 && scale<=300)
	{
		scanParams->setZScale(scale);
	}
	else
	{
		std::cout<<"Ungueltige Eingabe, es wird ein Standardwert verwendet"<<std::endl;
	}



	std::cout<<"Geben sie nun bitte den ungefaehren Winkel von Projektor zur Kamera in grad ein"<<std::endl;
	float skew;
	std::cin>>skew;

	if(skew>=5 && skew<=80)
	{
		scanParams->setZSkew(skew);
	}
	else
	{
		std::cout<<"Ungueltige Eingabe, es wird ein Standardwert verwendet"<<std::endl;
	}
	
	//versehentliche Tastatureingabe abfangen

	cv::waitKey(50);

	//phase1
	std::cout<<"beginn phase 1, bitte leertaste druecken"<<std::endl;
	projector = cv::imread("./vertical/i1.png");
	imshow("Projektor",projector);
	

	while(cv::waitKey(0)!=32)
		{

		}

	cv::Mat tmpImageDist;
	int i = 0;
	while(i<=3)
		{
		
		capture >> tmpImage;
		cv::undistort(tmpImage, tmpImageDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());

			if(i==3)
			{
			cv::imwrite("./captured/phase1.jpg",tmpImageDist);
			break;
			}

		i++;
		cv::waitKey(10);
		
	}

	//phase2
	std::cout<<"beginn phase 2, bitte leertaste druecken"<<std::endl;
	projector = cv::imread("./vertical/i2.png");
	cv::imshow("Projektor",projector);
	while(cv::waitKey(0)!=32)
	{
	
	}
	i = 0;
	while(i<=3){

		capture >> tmpImage;
		cv::undistort(tmpImage, tmpImageDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());

		if(i==3){
			cv::imwrite("./captured/phase2.jpg",tmpImageDist);
			break;
		}

		i++;
		cv::waitKey(10);
	}
	
	//phase3
	std::cout<<"beginn phase 3, bitte leertaste druecken"<<std::endl;
	projector = cv::imread("./vertical/i3.png");
	cv::imshow("Projektor",projector);
	while(cv::waitKey(0)!=32)
	{

	}
	i = 0;
	while(i<=3){

		capture >> tmpImage;
		cv::undistort(tmpImage, tmpImageDist, scanParams->getIntrinsic(), scanParams->getDistCoeffs());

		if(i==3){
			cv::imwrite("./captured/phase3.jpg",tmpImageDist);
			break;
		}

		i++;
		cv::waitKey(10);
	}
	std::cout<<"ende des Scans, berechnung wird initialisiert..."<<std::endl;
	

	

	
	




}
