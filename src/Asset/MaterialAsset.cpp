#include "MaterialAsset.h"

namespace fs = std::filesystem;

Logger MaterialAsset::logger("MaterialAsset");

void MaterialAsset::load() {
	if (file_path.empty()) {
		logger << "MaterialAsset::load() called on an empty path asset! (Asset ID " << id << ") - skipping..." << logger.warn;
		return;
	}

	std::ifstream ifs(file_path);
	if (!ifs) {
		logger << "Failed to open file: " << file_path << " (Asset ID " << id << ") - skipping..." << logger.warn;
		return;
	}

	std::string line, property;
	float r, g, b, a, s;
	int line_count = 0;

	while (std::getline(ifs, line)) {
		std::istringstream iss(line);
		++line_count;

		// Attempt to read the property name
		if (!(iss >> property)) {
			logger << "Invalid line " << line_count << " in file: " << file_path << logger.warn;
			logger << line_count << "| " << line << logger.warn;
			continue;
		}

		if (property == "SHININESS") {
			// Shininess only expects a single value
			if (!(iss >> s)) {
				logger << "Invalid shininess value on line " << line_count << " in file: " << file_path << logger.warn;
				logger << line_count << "| " << line << logger.warn;
				continue;
			}
			set_shininess(s);
		}
		else {
			// Other properties expect four values
			if (!(iss >> r >> g >> b >> a)) {
				logger << "Invalid color values on line " << line_count << " in file: " << file_path << logger.warn;
				logger << line_count << "| " << line << logger.warn;
				continue;
			}
			if (property == "EMISSION") {
				set_emission(r, g, b, a);
			}
			else if (property == "AMBIENT") {
				set_ambient(r, g, b, a);
			}
			else if (property == "DIFFUSE") {
				set_diffuse(r, g, b, a);
			}
			else if (property == "SPECULAR") {
				set_specular(r, g, b, a);
			}
			else {
				logger << "Unknown property " << property << " on line " << line_count << " in file: " << file_path << logger.warn;
			}
		}
	}
}

void MaterialAsset::set_emission(float r, float g, float b, float a) {
	emission[0] = r;
	emission[1] = g;
	emission[2] = b;
	emission[3] = a;
}

void MaterialAsset::set_ambient(float r, float g, float b, float a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}

void MaterialAsset::set_diffuse(float r, float g, float b, float a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}

void MaterialAsset::set_specular(float r, float g, float b, float a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}

void MaterialAsset::set_shininess(float s) {
	shininess[0] = s;
}

const float* MaterialAsset::get_emission() const {
	return emission;
}

const float* MaterialAsset::get_ambient() const {
	return ambient;
}

const float* MaterialAsset::get_diffuse() const {
	return diffuse;
}

const float* MaterialAsset::get_specular() const {
	return specular;
}

const float* MaterialAsset::get_shininess() const {
	return shininess;
}

void MaterialAsset::apply() const {
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}