#pragma once
#include "scanParams.h"
#include <iostream>
#include <fstream>

class ScanParams
{
public:
	ScanParams(void);
	~ScanParams(void);

	int vertexCount(ScanParams* scanParams);

	void writeVertices(std::ofstream file,ScanParams* scanParams);

	void exportCloud(ScanParams* scanParams);

};

