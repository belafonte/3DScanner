#pragma once
#include "scanParams.h"
#include <iostream>
#include <fstream>

class ScanParams
{
public:
	ScanParams(void);
	~ScanParams(void);

	int vertexCount(struct ScanParams* scanParams);

	void writeVertices(std::ofstream file, struct ScanParams* scanParams);

	void exportCloud(struct ScanParams* scanParams);

};

