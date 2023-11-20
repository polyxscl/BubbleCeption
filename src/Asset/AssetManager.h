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

	// Interface methods

	std::shared_ptr<ImageAsset> getImageAsset(std::string id) override;
	std::shared_ptr<MaterialAsset> getMaterialAsset(std::string id) override;
	std::shared_ptr<OBJAsset> getOBJAsset(std::string id) override;
	std::shared_ptr<MapAsset> getMapAsset(std::string id) override;

private:
	static AssetManager* instance;
	static void checkInit();

	std::unordered_map<std::string, std::shared_ptr<ImageAsset>> images;
	std::unordered_map<std::string, std::shared_ptr<MaterialAsset>> materials;
	std::unordered_map<std::string, std::shared_ptr<OBJAsset>> objs;
	std::unordered_map<std::string, std::shared_ptr<MapAsset>> maps;

	static Logger logger;
};