#include "CamCalib.h"

CamCalib::CamCalib(void){}
CamCalib::~CamCalib(void){}

using namespace cv;
using namespace std;



int CamCalib::camCalib(ScanParams * scanParams)
{

	//Variablen Deklaration
	int numShots = 1;
	int numCornersHor;
	int numCornersVer;
	int videoInputNr;

	cout <<"Kamera Kalibration initialisiert "<<endl;
	cout <<"Abfrage der Schachbretteigenschaften: "<<endl;
	//Variablenwert Abfrage
	cout <<"Horizontal eingeschlossene Ecken:(mind.3) "<<endl;
	while(true){
		cin >> numCornersHor;
		if(numCornersHor <= 10 && numCornersHor >=3){
			break;
		}

		else{cout<<"Bitte eine Zahl zwischen 3 und 10 eingeben"<<endl;}

	}

	cout <<"Vertikal eingeschlossene Ecken:(mind.3) "<<endl;
	while(true){
		cin >> numCornersVer;
		if(numCornersVer <= 10 && numCornersVer >=3){
			break;
		}

		else{cout<<"Bitte eine Zahl zwischen 3 und 10 eingeben"<<endl;}

	}

	cout <<"Anzahl der für die Kallibration zu verwendenden Shots(mind.2): "<<endl;
	while(true){
		cin >> numShots;
		if(numShots <= 30 && numShots >=1){
			break;
		}

		else{cout<<"Bitte eine Zahl zwischen 1 und 30 eingeben"<<endl;}

	}


	//Berechnung der Schachbrettgroesse
	int numSquares = numCornersHor * numCornersVer;
	Size boardSize = Size(numCornersHor, numCornersVer);



	//Videoinput
	cout<<"bitte Kamera durch Zahleingabe selektieren"<<endl;
	cout<<"0: Standardkamera"<<endl;
	cin >> videoInputNr;
	VideoCapture capture = VideoCapture(1);

	if(!capture.isOpened()){
		cout<<"keine Kamera gefunden, bitte entweder Kamera anschliessen oder Standardkamera selektieren"<<endl;
		cout<<" und Programm neustarten"<<endl;
	}
	
	int hor = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int vert = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	

	cout<< "die ausgewaehlte kamera arbeitet mit einer aufloesung von "<<hor<<" auf "<<vert<<endl;
	
	
	cout<<"hoehere kameraaufloesung waehlen?(falls moeglich) zahleneingabe + bestaetigen "<<endl;
	cout<<"1: 640 x 480 "<<endl;
	cout<<"2: 1280 x 720 "<<endl;
	cout<<"3: 1920 x 1080 "<<endl;
	int res = 0;
	cin >> res;
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

	else {cout<<"keine aenderung vorgenommen"<<endl;}

	//Vektoren

	vector <vector<Point3f >> object_points;
	vector <vector<Point2f >> image_points;


	vector<Point2f> corners;
	int successes=0;

	//Kamerabilder
	Mat image;
	Mat greyImage;

	//auf mat
	capture >> image;



	//position fuer jeden vertex
	vector<Point3f> obj;
	for(int j=0;j<numSquares;j++)
		obj.push_back(Point3f(j/numCornersHor, j%numCornersHor, 0.0f));



	


	//Schleife solange numShots groesser als successes

	while(successes<numShots)
	{
		//graukonvertierung des kamerabilds
		cv::cvtColor(image, greyImage, CV_BGR2GRAY);

		//findchessboardcorners
		
		bool found = cv::findChessboardCorners(image, boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

		if(found)
		{
			cv::cornerSubPix(greyImage, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(greyImage, boardSize, corners, found);
		}

		//anzeigen der bilder
		
		//imshow("win1", image);
		
		imshow("kamera kalibration", greyImage);
		

		//neuer frame

		capture >> image;
		
		int key = cv::waitKey(1);

		//speichern der zahlen und schleifenbruch
		

		if(successes>=numShots)
			{
				cout<<"Alle Bilder erfolgreich aufgenommen!"<<endl;
				break;
		}

		if(key==27)
			break;
	
		if(found!=0 && (key==32))
		{
			image_points.push_back(corners);
			object_points.push_back(obj);
			cout<<"Bild gespeichert!"<<endl;;

			successes++;

			if(successes>=numShots)
				cout<<"Alle Bilder erfolgreich aufgenommen!"<<endl;
				break;
			
		}
		
	}
	//Kallibrationsvariablen
	cout<<"Kalibrationsvorbereitung...";
	Mat intrinsic = Mat(3, 3, CV_32FC1);
	Mat distCoeffs;
	vector<Mat> rvecs;
	vector<Mat> tvecs;
	cout<<"beendet"<<endl;


	//focal length
	intrinsic.ptr<float>(0)[0] = 1;
	intrinsic.ptr<float>(1)[1] = 1;


	//kallibration
	cout<<"Kalibration...";
	cv::calibrateCamera(object_points, image_points, image.size(), intrinsic, distCoeffs, rvecs, tvecs);
	cout<<"beendet"<<endl;


	cout<<"Kalibriertes Kamerabild"<<endl;
	Mat imageUndistorted;
	while(1)
	{



		capture >> image;
		cv::undistort(image, imageUndistorted, intrinsic, distCoeffs);

		cv::imshow("win1", image);
		cv::imshow("win3", imageUndistorted);
		int key1 = waitKey(1);
		if(key1==27)
			break;



	}
	scanParams->setDistCoeffs(distCoeffs);
	scanParams->setIntrinsic(intrinsic);

	capture.release();
	destroyAllWindows();

	return 0;

	
}
