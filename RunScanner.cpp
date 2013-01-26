/*MainKlasse
	startet die Kamerakalibrierung
			den Parameterscan
			die Bildanalyse
			die Bildkonvertierung
			und den Export
*/
			


#include "scanParams.h"
#include "DecodePhase.h"
#include "EncodePhase.h"
#include "PLYExporter.h"
#include "CamCalib.h"
#include "AdditionalFunctions.h"
#include "CaptureScan.h"


using namespace std;
using namespace cv;

int main(void) {


	//initialisierung
	ScanParams* scanParams = new ScanParams(640, 480);

	CamCalib* camCalib = new CamCalib();
	CaptureScan* captureScan = new CaptureScan();
	DecodePhase* decodePhase = new DecodePhase();
	EncodePhase* encodePhase = new EncodePhase();
	PLYExporter* plyExporter = new PLYExporter();

	//programmstart
	
	cout<<"Programm Start durch Eingabe bestaetigen"<<endl;
	cin.get();

	camCalib->camCalib(scanParams);
	captureScan->createScanPictures(scanParams);

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
	cout << "exporting Cloud" << endl;
	plyExporter->exportCloud(scanParams);
	cout << "exporting Mesh" << endl;
	plyExporter->exportMesh(scanParams);
	cout << "fertig. escape zum beenden" << endl;

	if(waitKey(0)==27)
	return 0;
	//programmende
}