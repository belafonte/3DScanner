#include "scanParams.h"
#include "DecodePhase.h"
#include "EncodePhase.h"
#include "PLYExporter.h"

using namespace std;
using namespace cv;

int main(void) {
	DecodePhase* decodePhase = new DecodePhase();
	EncodePhase* encodePhase = new EncodePhase();
	PLYExporter* plyExporter = new PLYExporter();

	int waitKeyValue = 10;
	cv::Mat san;

	cv::VideoCapture san_cap(0);
	if (san_cap.isOpened()) {
		while (1) {
			san_cap.read(san);
			cv::imshow("gp", san);
			int key = cv::waitKey(waitKeyValue);
			if(key!=-1)cout<<key<<endl;
			if (key == 27 || key == 1048586) {
				if (waitKeyValue == 10)waitKeyValue = 0;
				else waitKeyValue = 10;
			}
		}
	} else cout << "videoCapture not working" << endl;



	cout<<"scan params..."<<endl;
	ScanParams* scanParams = new ScanParams(640, 480);
	cout<<"encode phase..."<<endl;
	cout<<"load images..."<<endl;
	encodePhase->loadImages();
	cout<<"encode phase 2..."<<endl;
	encodePhase->encodePhase(scanParams);
	cout<<"decode phase..."<<endl;
	cout<<"decode phase 2..."<<endl;
	decodePhase->decodePhase(scanParams);
	cout<<"calc depth..."<<endl;
	decodePhase->calcDepth(scanParams);
	cout<<"done..."<<endl;
	plyExporter->exportCloud(scanParams);
	cout << "exporting Cloud" << endl;
	plyExporter->exportMesh(scanParams);
	cout << "exporting Mesh" << endl;



	cin.get();
	return 0;
}