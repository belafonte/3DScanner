//kamerakalibration

#include "CamCalib.h"

CamCalib::CamCalib(void){}
CamCalib::~CamCalib(void){}




int CamCalib::camCalib(ScanParams * scanParams)
{

	//Variablen Deklaration
	int numShots = 1;
	int numCornersHor;
	int numCornersVer;
	int videoInputNr;

	std::cout <<"Kamera Kalibration initialisiert "<<std::endl;
	std::cout <<"Abfrage der Schachbretteigenschaften: "<<std::endl;

	//Variablenwert Abfrage
	std::cout <<"Horizontal eingeschlossene Ecken:(mind.3) "<<std::endl;
	while(true){
		std::cin >> numCornersHor;
		if(numCornersHor <= 10 && numCornersHor >=3){
			break;
		}

		else{std::cout<<"Bitte eine Zahl zwischen 3 und 10 eingeben"<<std::endl;}

	}

	std::cout <<"Vertikal eingeschlossene Ecken:(mind.3) "<<std::endl;
	while(true){
		std::cin >> numCornersVer;
		if(numCornersVer <= 10 && numCornersVer >=3){
			break;
		}

		else{std::cout<<"Bitte eine Zahl zwischen 3 und 10 eingeben"<<std::endl;}

	}

	std::cout <<"Anzahl der für die Kallibration zu verwendenden Shots(mind.2): "<<std::endl;
	while(true){
		std::cin >> numShots;
		if(numShots <= 30 && numShots >=1){
			break;
		}

		else{std::cout<<"Bitte eine Zahl zwischen 1 und 30 eingeben"<<std::endl;}

	}


	//Berechnung der Schachbrettgroesse
	int numSquares = numCornersHor * numCornersVer;
	cv::Size boardSize = cv::Size(numCornersHor, numCornersVer);



	//Videoinput
	std::cout<<"bitte Kamera durch Zahleingabe selektieren"<<std::endl;
	std::cout<<"0: Standardkamera"<<std::endl;
	std::cin >> videoInputNr;
	cv::VideoCapture capture = cv::VideoCapture(1);

	if(!capture.isOpened()){
		std::cout<<"keine Kamera gefunden, bitte entweder Kamera anschliessen oder Standardkamera selektieren"<<std::endl;
		std::cout<<" und Programm neustarten"<<std::endl;
	}
	
	int hor = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int vert = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	

	std::cout<< "die ausgewaehlte kamera arbeitet mit einer aufloesung von "<<hor<<" auf "<<vert<<std::endl;
	
	
	std::cout<<"hoehere kameraaufloesung waehlen?(falls moeglich) zahleneingabe + bestaetigen "<<std::endl;
	std::cout<<"1: 640 x 480 "<<std::endl;
	std::cout<<"2: 1280 x 720 "<<std::endl;
	std::cout<<"3: 1920 x 1080 "<<std::endl;
	int res = 0;
	std::cin >> res;
	if (res == 1)
	{

		capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
	}
	else if(res == 2){
		capture.set(CV_CAP_PROP_FRAME_WIDTH,1280);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT,720);
	}
	else if(res == 3){
		capture.set(CV_CAP_PROP_FRAME_WIDTH,1920);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT,1080);
	}

	else {std::cout<<"keine aenderung vorgenommen"<<std::endl;}



	//Vektoren

	std::vector <std::vector<cv::Point3f >> object_points;
	std::vector <std::vector<cv::Point2f >> image_points;


	cv::vector<cv::Point2f> corners;
	int successes=0;

	//Kamerabilder
	cv::Mat image;
	cv::Mat greyImage;

	//auf mat
	capture >> image;



	//position fuer jeden vertex
	std::vector<cv::Point3f> obj;
	for(int j=0;j<numSquares;j++)
		obj.push_back(cv::Point3f(j/numCornersHor, j%numCornersHor, 0.0f));



	


	//Schleife solange numShots groesser als successes

	while(successes<=numShots)
	{
		//graukonvertierung des kamerabilds
		cv::cvtColor(image, greyImage, CV_BGR2GRAY);

		//findchessboardcorners
		
		bool found = cv::findChessboardCorners(image, boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

		if(found)
		{
			cv::cornerSubPix(greyImage, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(greyImage, boardSize, corners, found);
		}

		//anzeigen der bilder
		
		//cv::imshow("win1", image);
		
		cv::imshow("kamera kalibration", greyImage);
		

		//neuer frame

		capture >> image;
		
		int key = cv::waitKey(1);

		//speichern der zahlen und schleifenbruch
		

		if(successes>=numShots)
			{
				std::cout<<"Alle Bilder erfolgreich aufgenommen!"<<std::endl;
				break;
		}

		if(key==27)
			break;
	
		if(found!=0)
		{
			int snap = cv::waitKey(500);
			if (snap == 32){
			image_points.push_back(corners);
			object_points.push_back(obj);
			std::cout<<"Bild gespeichert!"<<std::endl;;

			successes++;

			if(successes>=numShots){
				std::cout<<"Alle Bilder erfolgreich aufgenommen!"<<std::endl;
				break;
				}
			}
		
		}
	}
	//Kallibrationsvariablen
	std::cout<<"Kalibrationsvorbereitung...";
	cv::Mat intrinsic = cv::Mat(3, 3, CV_32FC1);
	cv::Mat distCoeffs;
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
	std::cout<<"beendet"<<std::endl;


	//focal length
	intrinsic.ptr<float>(0)[0] = 1;
	intrinsic.ptr<float>(1)[1] = 1;


	//kallibration
	std::cout<<"Kalibration...";
	cv::calibrateCamera(object_points, image_points, image.size(), intrinsic, distCoeffs, rvecs, tvecs);
	std::cout<<"beendet"<<std::endl;


	std::cout<<"Kalibriertes Kamerabild"<<std::endl;
	cv::Mat imageUndistorted;
	while(1)
	{



		capture >> image;
		cv::undistort(image, imageUndistorted, intrinsic, distCoeffs);
		cv::imshow("Calibrated Video", imageUndistorted);
		int key1 = cv::waitKey(1);
		if(key1==32)
			break;



	}
	scanParams->setDistCoeffs(distCoeffs);
	scanParams->setIntrinsic(intrinsic);

	capture.release();
	cv::destroyAllWindows();

	return 0;

	
}
