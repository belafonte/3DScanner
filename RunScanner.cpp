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

	encodePhase->loadImages();
	ScanParams* scanParams = new ScanParams(encodePhase->phase1Image.rows, encodePhase->phase1Image.cols);
	encodePhase->encodePhase(scanParams);
	//decodePhase->decodePhase(scanParams);

	//plyExporter->exportCloud(scanParams);

	cout << encodePhase->phase1Image.rows << encodePhase->phase1Image.cols << endl;
	cin.get();
	return 0;
}