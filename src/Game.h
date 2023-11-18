#pragma once

#include "Game.interface.h"
#include "Asset/AssetManager.h"
#include "Input/InputManager.h"
#include "Scene/SceneManager.h"
#include "Util/Logger.h"

class Game : public IGame {
public:
	explicit Game(int argc, char** argv);

	void run();

	IAssetManager& getIAssetManager() override;
	IInputManager& getIInputManager() override;
	ISceneManager& getISceneManager() override;

private:
	static Game* instance;

	AssetManager asset_manager;
	InputManager input_manager;
	SceneManager scene_manager;

	static void display();
	static void idle();
	static void checkInit();

	static Logger logger;

};