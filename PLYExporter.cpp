#include "PLYExporter.h"


PLYExporter::PLYExporter(void)
{
}


PLYExporter::~PLYExporter(void)
{
}

int vertexCount(struct ScanParams* scanParams) {
	int total = 0;
	for (int y = 0; y < scanParams->calcHeight; y += scanParams->renderDetail) {
		for (int x = 0; x < scanParams->calcWidth; x += scanParams->renderDetail) {
			if(!scanParams->mask[y][x])
				scanParams->names[y][x] = total++;
		}
	}
	return total;
}

void writeVertices(std::ofstream file, struct ScanParams* scanParams) {
	for (int y = 0; y < scanParams->calcHeight; y += scanParams->renderDetail)
		for (int x = 0; x < scanParams->calcWidth; x += scanParams->renderDetail)
			if (!scanParams->mask[y][x]) {
				cv::Vec3b cur = (cv::Vec3b) scanParams->colors[y][x];
				file <<
					x << " " <<
					(scanParams->calcHeight - y) << " " <<
					scanParams->depth[y][x] << " " <<
					(int) cur[2] << " " << 
					(int) cur[1] << " " << 
					(int) cur[0] << "\n";
			}
}

void exportCloud(struct ScanParams* scanParams) {
	std::ofstream file ("file.ply");
	file << "ply\n";
	file << "format ascii 1.0\n";
	file << "element vertex " << vertexCount(scanParams) << "\n";
	file << "property float x\n";
	file << "property float y\n";
	file << "property float z\n";
	file << "property unchar red\n";
	file << "property unchar green\n";
	file << "property unchar blue\n";
	file << "end_header";
	writeVertices(file, scanParams);
	file.close();
}