#include "CamCalib.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>

CamCalib::CamCalib(void){}
CamCalib::~CamCalib(void){}

using namespace cv;
using namespace std;



int CamCalib::camCalib()
{
	//Variablen Deklaration
	int numShots = 0;
	int numCornersHor;
	int numCornersVer;
	int videoInputNr;


	//Variablenwert Abfrage
	cout <<"Horizontal eingeschlossene Ecken: "<<endl;
	while(true){
		cin >> numCornersHor;
		if(numCornersHor <= 10 && numCornersHor >=1){
			break;
		}

		else{cout<<"Bitte eine Zahl zwischen 1 und 10 eingeben"<<endl;}

	}

	cout <<"Vertikal eingeschlossene Ecken: "<<endl;
	while(true){
		cin >> numCornersVer;
		if(numCornersVer <= 10 && numCornersVer >=1){
			break;
		}

		else{cout<<"Bitte eine Zahl zwischen 1 und 10 eingeben"<<endl;}

	}

	cout <<"Anzahl der für die Kallibration zu verwendenden Shots: "<<endl;
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
	cout<<"select video input"<<endl;
	cin >> videoInputNr;
	VideoCapture capture = VideoCapture(videoInputNr);
	
	int hor = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	int vert = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	

	cout<< "die ausgewaehlte kamera arbeitet mit einer Aufloesung von "<<hor<<" auf "<<vert<<endl;
	waitKey();
	
	cout<<"hoehere kameraaufloesung waehlen? "<<endl;
	cout<<"1: 640 x 480 "<<endl;
	cout<<"2: 800 x 600 "<<endl;
	cout<<"3: 1280 x 960 "<<endl;
	int res = 0;
	cin >> res;
	if (res == 1)
	{

		capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
	}
	else if(res == 2){
		capture.set(CV_CAP_PROP_FRAME_WIDTH,800);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT,600);
	}
	else if(res == 3){
		capture.set(CV_CAP_PROP_FRAME_WIDTH,1280);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT,960);
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



	//assign a constant position to each vertex.
	vector<Point3f> obj;
	for(int j=0;j<numSquares;j++)
		obj.push_back(Point3f(j/numCornersHor, j%numCornersHor, 0.0f));

	//An important point here is that you’re essentially setting up the units of calibration. Suppose the squares in your chessboards were 30mm in size, and you supplied these coordinates as (0,0,0), (0, 30, 0), etc, you’d get all unknowns in millimeters.

	
	

	//Schleife solange numShots groesser als successes

	while(successes<numShots)
	{
		//graukonvertierung des kamerabilds
		cvtColor(image, greyImage, CV_BGR2GRAY);

		//findchessboardcorners
		
		bool found = findChessboardCorners(image, boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

		if(found)
		{
			cornerSubPix(greyImage, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
			drawChessboardCorners(greyImage, boardSize, corners, found);
		}

		//anzeigen der bilder
		
		//imshow("win1", image);
		
		imshow("win2", greyImage);
		

		//neuer frame

		capture >> image;
		
		int key = waitKey(1);

		//speichern der zahlen und schleifenbruch
		

		if(successes>=numShots)
			break;

		if(key==27)
			break;
	
		if(found!=0 && (key==32))
		{
			image_points.push_back(corners);
			object_points.push_back(obj);
			printf("Snap stored!\n");

			successes++;

			if(successes>=numShots)
				break;
			
		}
		
	}
	//Kallibrationsvariablen
	cout<<"prepare calibration..."<<endl;
	Mat intrinsic = Mat(3, 3, CV_32FC1);
	Mat distCoeffs;
	vector<Mat> rvecs;
	vector<Mat> tvecs;
	cout<<"prepare calibration done."<<endl;


	//focal length
	intrinsic.ptr<float>(0)[0] = 1;
	intrinsic.ptr<float>(1)[1] = 1;


	//kallibration
	cout<<"start calibration..."<<endl;
	calibrateCamera(object_points, image_points, image.size(), intrinsic, distCoeffs, rvecs, tvecs);
	cout<<"calibration done."<<endl;


	cout<<"show undistorted image..."<<endl;
	Mat imageUndistorted;
	while(1)
	{



		capture >> image;
		undistort(image, imageUndistorted, intrinsic, distCoeffs);

		imshow("win1", image);
		imshow("win3", imageUndistorted);
		waitKey(1);




	}

	capture.release();
	destroyWindow("win2");

	return 0;

	
}
