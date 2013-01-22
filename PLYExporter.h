#pragma once
#include "scanParams.h"
#include <iostream>
#include <fstream>

class PLYExporter
{
public:
	PLYExporter(void);
	~PLYExporter(void);

	int vertexCount(struct ScanParams* scanParams);

	void writeVertices(std::ofstream file, struct ScanParams* scanParams);

	void exportCloud(struct ScanParams* scanParams);

};

