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



	int faceCount(ScanParams* scanParams);

	void writeFace(std::ofstream &file, int a, int b, int c);

	void writeFaces(std::ofstream &file, ScanParams* scanParams);

	void exportMesh(ScanParams* scanParams);

};

#endif