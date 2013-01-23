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

	

	cout<<"scan params..."<<endl;
	ScanParams* scanParams = new ScanParams(640, 480);

	cout << scanParams->getNoiseThreshold() << endl;

	cout<<"encode phase..."<<endl;
	cout<<"load images..."<<endl;
	encodePhase->loadImages();
	cout<<"encode phase 2..."<<endl;
	encodePhase->encodePhase(scanParams);
	cout<<"decode phase..."<<endl;
	cout<<"decode phase 2..."<<endl;
	//cin.get();
	//bool tmpVar = scanParams->process;

	/*cout << sizeof(tmpVar) << endl;
	scanParams->setProcess(false, 10000, 100000);
	scanParams->setProcess(false, 1, 1);
	cout << scanParams->getProcess(1, 1) << endl;
	scanParams->setProcess(true, 1, 1);
	cout << scanParams->getProcess(1, 1) << endl;

	for(int y = 0; y < scanParams->getCalcHeight(); y++) {
		for (int x = 0; x < scanParams->getCalcWidth(); x++) {
			cout << scanParams->getProcess(y, x) << endl;
		}
	}
	cin.get();*/
	

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