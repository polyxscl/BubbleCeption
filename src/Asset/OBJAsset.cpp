#include "OBJAsset.h"

namespace fs = std::filesystem;

Logger OBJAsset::logger("OBJAsset");

void OBJAsset::load() {
	if (file_path.empty()) {
		logger << "OBJAsset::load() called on an empty path asset! (Asset ID " << id << ") - skipping..." << logger.warn;
		return;
	}

	std::ifstream ifs(file_path);
	if (!ifs) {
		logger << "Failed to open file: " << file_path << " (Asset ID " << id << ") - skipping..." << logger.warn;
		return;
	}

	std::string line, type;
	int line_count = 0;
	
	while (std::getline(ifs, line)) {
		std::istringstream iss(line);
		++line_count;

		if (!(iss >> type)) {
			logger << "Invalid type value on line " << line_count << " in file: " << file_path << logger.error;
			logger << line_count << "| " << line << logger.error;
			continue;
		}
		
		if (type == "v") {
			float x, y, z, w;
			if (!(iss >> x >> y >> z >> w)) {
				logger << "Invalid coordinates on line " << line_count << "in file: " << file_path << logger.error;
				logger << line_count << "| " << line << logger.error;
			}
			Vector4<float> vertex(x, y, z, w);
			vertices.push_back(vertex);
		}
		else if (type == "f") {
			int a, b, c;
			if (!(iss >> a >> b >> c)) {
				faces.push_back(Face{ a, b, c });
			}
		}
		else {
			logger << "Unsupported type value on line " << line_count << " in file: " << file_path << logger.error;
			logger << line_count << "| " << line << logger.error;
		}
	}
}