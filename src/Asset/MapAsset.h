#pragma once

#include <filesystem>
#include <fstream>

#include "Asset.h"
#include "Util/Logger.h"
#include "Util/Vector.h"

typedef std::unordered_map<Vector3<int>, std::string> TMapAssetData;

class MapAsset : public Asset {
public:
	using Asset::Asset;

	void load() override;
	const int getWidth() const;
	const int getHeight() const;
	const TMapAssetData& getData() const;
	const std::string& getPalette() const;

private:
	int width;
	int height;
	std::string palette;

	TMapAssetData data;

	static Logger logger;

};