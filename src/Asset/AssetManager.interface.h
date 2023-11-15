#pragma once

#include <string>

#include "Asset/ImageAsset.h"
#include "Asset/MaterialAsset.h"
#include "Asset/OBJAsset.h"

// Interface for AssetManager class.
class IAssetManager {
public:
	virtual std::shared_ptr<ImageAsset> getImageAsset(std::string id) = 0;
	virtual std::shared_ptr<MaterialAsset> getMaterialAsset(std::string id) = 0;
	virtual std::shared_ptr<OBJAsset> getOBJAsset(std::string id) = 0;
};