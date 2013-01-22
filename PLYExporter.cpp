#include "PLYExporter.h"

PLYExporter::PLYExporter(void) { }

PLYExporter::~PLYExporter(void) { }

int PLYExporter::vertexCount(ScanParams* scanParams) {
	int total = 0;
	for (int y = 0; y < scanParams->getCalcHeight(); y += scanParams->getRenderDetail()) {
		for (int x = 0; x < scanParams->getCalcWidth(); x += scanParams->getRenderDetail()) {
			if(!scanParams->getMask(y, x))
				scanParams->setNames(total++, y, x);
		}
	}
	return total;
}

void PLYExporter::writeVertices(std::ofstream &file, ScanParams* scanParams) {
	for (int y = 0; y < scanParams->getCalcHeight(); y += scanParams->getRenderDetail())
		for (int x = 0; x < scanParams->getCalcWidth(); x += scanParams->getRenderDetail())
			if (!scanParams->getMask(y, x)) {
				cv::Vec3b cur = (cv::Vec3b) scanParams->getColors(y, x);
				file <<
					x << " " <<
					(scanParams->getCalcHeight() - y) << " " <<
					scanParams->getDepth(y, x) << " " <<
					(int) cur[2] << " " << 
					(int) cur[1] << " " << 
					(int) cur[0] << "\n";
			}
}

void PLYExporter::exportCloud(ScanParams* scanParams) {
	std::ofstream file(PATH"cloud.ply");
	file << "ply\n";
	file << "format ascii 1.0\n";
	file << "element vertex " << PLYExporter::vertexCount(scanParams) << "\n";
	file << "property float x\n";
	file << "property float y\n";
	file << "property float z\n";
	file << "property unchar red\n";
	file << "property unchar green\n";
	file << "property unchar blue\n";
	file << "end_header";
	PLYExporter::writeVertices(file, scanParams);
	file.close();
}