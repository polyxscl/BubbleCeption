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

	logger << "Initializing AssetManager..." << logger.info;

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

void AssetManager::checkInit() {
	if (!instance) {
		logger << "AssetManager instance not initialized" << logger.error;
		throw std::runtime_error("UninitializedAssetManager");
	}
}