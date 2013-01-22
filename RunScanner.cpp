#include <iostream>
#include "scanParams.h"

using namespace std;
using namespace cv;

int main(void) {
	ScanParams* scanParams = new ScanParams(1280, 1980);
	int tmpVar = scanParams->getCalcHeight();
	cout << tmpVar << endl;
	cin.get();
}