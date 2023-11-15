#pragma once

#include <filesystem>
#include <fstream>
#include <vector>

#include "Asset.h"
#include "Util/Logger.h"
#include "Util/Vector.h"

struct Face {
	int a, b, c;
};

class OBJAsset : public Asset {
public:
	using Asset::Asset;

	void load() override;

private:
	std::vector<Vector4<float>> vertices;
	std::vector<Face> faces;

	static Logger logger;
};