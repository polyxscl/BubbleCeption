#pragma once

#include <memory>

#include "Asset/AssetManager.interface.h"

// Interface for Game class.
class IGame {
	virtual IAssetManager& getIAssetManager() = 0;

};