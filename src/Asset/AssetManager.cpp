#include <stdexcept>
#include <filesystem>

#include "AssetManager.h"

AssetManager* AssetManager::instance = nullptr;

Logger AssetManager::logger("AssetManager");

AssetManager::AssetManager() {
	if (instance) {
		logger << "Duplicate instance of AssetManager is not allowed" << logger.error;
		throw std::runtime_error("DuplicateAssetManager");
	}

	logger << "Creating AssetManager class..." << logger.info;

	// Singleton
	instance = this;
}

void AssetManager::loadAssets(const fs::path& directory) {
	checkInit();

	logger << "Loading assets..." << logger.info;
	int count = 0;

	try {
		if (fs::exists(directory) && fs::is_directory(directory)) {
			for (const auto& entry : fs::recursive_directory_iterator(directory)) {
				if (fs::is_directory(entry)) continue;
				fs::path path = entry.path();
				std::string ext = path.extension().string();
				std::string id = path.stem().string();

				++count;

				// Material data
				if (ext == ".mtl") {
					materials.emplace(id, std::make_shared<MaterialAsset>(id, path));
				}
				// Wavefront OBJ data
				else if (ext == ".obj") {
					objs.emplace(id, std::make_shared<OBJAsset>(id, path));
				}
				// Image data
				else if (FreeImage_GetFileType(path.string().c_str(), 0) != FREE_IMAGE_FORMAT::FIF_UNKNOWN) {
					images.emplace(id, std::make_shared<ImageAsset>(id, path));
				}
				else --count;
			}
		}
		else {
			logger << "The directory " << directory << " does not exist." << logger.warn;
			logger << "Image assets could not be loaded - parts of the game might not work properly!" << logger.warn;
			logger << "Please check if the assets/ folder exist in the same folder as the game executable." << logger.warn;
		}
	}
	catch (const std::exception& e) {
		logger << "The exception has occurred in AssetManager::load_images() with the exception : " << e.what() << logger.error;
		logger << "Image assets might not have been loaded properly!" << logger.error;
	}
	logger << "Found " << count << " assets." << logger.info;
}

std::shared_ptr<ImageAsset> AssetManager::getImageAsset(std::string id) {
	return (images.find(id) != images.end()) ? images[id] : nullptr;
}

std::shared_ptr<MaterialAsset> AssetManager::getMaterialAsset(std::string id) {
	return (materials.find(id) != materials.end()) ? materials[id] : nullptr;
}

std::shared_ptr<OBJAsset> AssetManager::getOBJAsset(std::string id) {
	return (objs.find(id) != objs.end()) ? objs[id] : nullptr;
}

void AssetManager::checkInit() {
	if (!instance) {
		logger << "AssetManager instance not initialized" << logger.error;
		throw std::runtime_error("UninitializedAssetManager");
	}
}