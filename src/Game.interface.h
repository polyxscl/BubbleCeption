#pragma once

#include <memory>

#include "Asset/AssetManager.interface.h"
#include "Input/InputManager.interface.h"
#include "Scene/SceneManager.interface.h"

// Interface for Game class.
class IGame {
public:
	virtual IAssetManager& getIAssetManager() = 0;
	virtual IInputManager& getIInputManager() = 0;
	virtual ISceneManager& getISceneManager() = 0;

};