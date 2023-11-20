#include "MapAsset.h"

#include <nlohmann/json.hpp>

using namespace nlohmann;
namespace fs = std::filesystem;

Logger MapAsset::logger("MapAsset");

void MapAsset::load() {
	if (file_path.empty()) {
		logger << "MapAsset::load() called on an empty path asset! (Asset ID " << id << ") - skipping..." << logger.warn;
		return;
	}

	std::ifstream ifs(file_path);
	if (!ifs) {
		logger << "Failed to open file: " << file_path << " (Asset ID " << id << ") - skipping..." << logger.warn;
		return;
	}

	json json_data = json::parse(ifs);

	width = json_data["width"];
	height = json_data["height"];
	palette = json_data["palette"];

	for (auto& tile_data : json_data["data"]) {
		int x = tile_data["pos"][0];
		int y = tile_data["pos"][1];
		std::string id = tile_data["id"];
		data.emplace(Vector3<int>(x, y), id);
	}

}

const int MapAsset::getWidth() const {
	return width;
}

const int MapAsset::getHeight() const {
	return height;
}

const TMapAssetData& MapAsset::getData() const {
	return data;
}

const std::string& MapAsset::getPalette() const {
	return palette;
}