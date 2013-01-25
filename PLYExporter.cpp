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
				int red = cur[2];
				int green = cur[1];
				int blue = cur[0];
				file << x << " " <<
					(scanParams->getCalcHeight() - y) << " " <<
					scanParams->getDepth(y, x) << " " <<
					red << " " << 
					green << " " << 
					blue << "\n";
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
	file << "property uchar red\n";
	file << "property uchar green\n";
	file << "property uchar blue\n";
	file << "end_header\n";
	PLYExporter::writeVertices(file, scanParams);
	file.close();
}


// <--  MESH EXPORTER!

int PLYExporter::faceCount(ScanParams* scanParams) {
	int total = 0;
	int r = scanParams->getRenderDetail();
	for(int y = 0; y < scanParams->getCalcHeight() - r; y += r)
		for(int x = 0; x < scanParams->getCalcWidth() - r; x += r) {
			if(!scanParams->getMask(y, x) && !scanParams->getMask(y + r, x + r)) {
				if(!scanParams->getMask(y, x + r))
					total++;
				if(!scanParams->getMask(y + r, x))
					total++;
			} 
			else if(!scanParams->getMask(y, x + r) && !scanParams->getMask(y + r, x)) {
				if(!scanParams->getMask(y, x))
					total++;
				if(!scanParams->getMask(y + r, x + r))
					total++;
			}
		}
		return total;
}

void PLYExporter::writeFace(std::ofstream &file, int a, int b, int c) {
	file << "3 " << a << " " << b << " " << c << "\n";
}

void PLYExporter::writeFaces(std::ofstream &file, ScanParams* scanParams) {
	int r = scanParams->getRenderDetail();
	int total = 0;
	for(int y = 0; y < scanParams->getCalcHeight() - r; y += r)
		for(int x = 0; x < scanParams->getCalcWidth() - r; x += r) {
			if(!scanParams->getMask(y, x) && !scanParams->getMask(y + r, x + r)) {
				if(!scanParams->getMask(y, x + r)) {
					writeFace(file, scanParams->getNames(y + r, x + r),
									scanParams->getNames(y, x + r),
									scanParams->getNames(y, x));
				}
				if(!scanParams->getMask(y + r, x)) {
					writeFace(file, scanParams->getNames(y + r, x),
									scanParams->getNames(y + r, x + r),
									scanParams->getNames(y, x));
				}
			} 
			else if(!scanParams->getMask(y, x + r) && !scanParams->getMask(y + r, x)) {
				if(!scanParams->getMask(y, x)) {
					writeFace(file, scanParams->getNames(y + r, x),
									scanParams->getNames(y, x + r),
									scanParams->getNames(y, x));
				}
				if(!scanParams->getMask(y + r, x + r)) {
					writeFace(file, scanParams->getNames(y + r, x),
									scanParams->getNames(y + r, x + r),
									scanParams->getNames(y, x + r));
				}
			}
		}
}

void PLYExporter::exportMesh(ScanParams* scanParams) {
		std::ofstream file(PATH"mesh.ply");
		file << "ply\n";
		file << "format ascii 1.0\n";
		file << "element vertex " << PLYExporter::vertexCount(scanParams) << "\n";
		file << "property float x\n";
		file << "property float y\n";
		file << "property float z\n";
		file << "property uchar red\n";
		file << "property uchar green\n";
		file << "property uchar blue\n";
		file << "element face " << faceCount(scanParams) << "\n";
		file << "property list uchar uint vertex_indices\n";
		file << "end_header\n";
		writeVertices(file, scanParams); 
		writeFaces(file, scanParams);
		file.flush();
		file.close();
}