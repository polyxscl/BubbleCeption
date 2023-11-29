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
				// Map data
				else if (ext == ".json") {
					auto ptr = std::make_shared<MapAsset>(id, path);
					ptr->load();
					maps.emplace(id, ptr);
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
		logger << "The exception has occurred in AssetManager::loadAssets() with the exception : " << e.what() << logger.error;
		logger << "Assets might not have been loaded properly!" << logger.error;
	}
	logger << "Found " << count << " assets." << logger.info;

	// Initialize placeholder assets
	// ImageAsset

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

	auto image_ptr = std::make_shared<ImageAsset>("null");
	image_ptr->fromRawRGBA8(16, 16, null_image_data);
	images.emplace("null", image_ptr);

	// MaterialAsset

	auto material_ptr = std::make_shared<MaterialAsset>("null");
	material_ptr->set_ambient(0.5f, 0.5f, 0.5f, 1.0f);
	material_ptr->set_diffuse(0.5f, 0.5f, 0.5f, 1.0f);
	material_ptr->set_emission(0.0f, 0.0f, 0.0f, 1.0f);
	material_ptr->set_specular(0.7f, 0.7f, 0.7f, 1.0f);
	material_ptr->set_shininess(0.78125f);
	materials.emplace("null", material_ptr);

}

std::shared_ptr<ImageAsset> AssetManager::getImageAsset(std::string id) {
	if (images.find(id) != images.end())
		return images[id];
	else {
		logger << "Failed to retrieve ImageAsset of id " << id << " - replacing with null texture..." << logger.warn;
		return images["null"];
	}
}

std::shared_ptr<MaterialAsset> AssetManager::getMaterialAsset(std::string id) {
	if (materials.find(id) != materials.end())
		return materials[id];
	else {
		logger << "Failed to retrieve MaterialAsset of id " << id << " - replacing with null material..." << logger.warn;
		return materials["null"];
	}
}

std::shared_ptr<OBJAsset> AssetManager::getOBJAsset(std::string id) {
	if (objs.find(id) != objs.end())
		return objs[id];
	else {
		logger << "Failed to retrieve OBJAsset of id " << id << " - returning nullptr..." << logger.warn;
		return nullptr;
	}
}

std::shared_ptr<MapAsset> AssetManager::getMapAsset(std::string id) {
	if (maps.find(id) != maps.end())
		return maps[id];
	else {
		logger << "Failed to retrieve MapAsset of id " << id << " - returning nullptr..." << logger.warn;
		return nullptr;
	}
}

void AssetManager::checkInit() {
	if (!instance) {
		logger << "AssetManager instance not initialized" << logger.error;
		throw std::runtime_error("UninitializedAssetManager");
	}
}