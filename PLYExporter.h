#ifndef __PLYEXPORTER_H
#define __PLYEXPORTER_H

#include "scanParams.h"

class PLYExporter
{
public:
	PLYExporter(void);
	~PLYExporter(void);

	int vertexCount(ScanParams* scanParams);

	void writeVertices(std::ofstream &file,ScanParams* scanParams);

	void exportCloud(ScanParams* scanParams);

};

#endif