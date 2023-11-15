#pragma once

#include <unordered_map>
#include <filesystem>

#include "AssetManager.interface.h"
#include "Util/Logger.h"

namespace fs = std::filesystem;

class AssetManager : public IAssetManager {
public:
	explicit AssetManager();

	void loadAssets(const fs::path& directory);

private:
	static AssetManager* instance;
	static void checkInit();

	static Logger logger;
};