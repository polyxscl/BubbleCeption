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
					auto ptr = std::make_shared<MaterialAsset>(id, path);
					ptr->load();
					materials.emplace(id, ptr);
				}
				// Wavefront OBJ data
				else if (ext == ".obj") {
					auto ptr = std::make_shared<OBJAsset>(id, path);
					ptr->load();
					objs.emplace(id, ptr);
				}
				// Image data
				else if (FreeImage_GetFileType(path.string().c_str(), 0) != FREE_IMAGE_FORMAT::FIF_UNKNOWN) {
					auto ptr = std::make_shared<ImageAsset>(id, path);
					ptr->load();
					images.emplace(id, ptr);
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

	// Initialize placeholder assets

	GLubyte* null_image_data = new GLubyte[4 * 16 * 16]();
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 16; ++j) {
			auto index = 4 * (16 * i + j);
			null_image_data[index + 1] = 0;
			null_image_data[index + 3] = 255;
			if ((i >> 3) + (j >> 3) == 1) {
				null_image_data[index + 0] = 255;
				null_image_data[index + 2] = 255;
			} 
			else {
				null_image_data[index + 0] = 0;
				null_image_data[index + 2] = 0;
			}
		}
	}

	auto ptr = std::make_shared<ImageAsset>("null");
	ptr->fromRawRGBA8(16, 16, null_image_data);
	images.emplace("null", ptr);
}

std::shared_ptr<ImageAsset> AssetManager::getImageAsset(std::string id) {
	return (images.find(id) != images.end()) ? images[id] : images["null"];
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