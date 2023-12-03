#pragma once

#include <ctime>

#include "Game.interface.h"
#include "Scene/Scene.h"
#include "Asset/ImageAsset.h"

class GameoverScene : public Scene {
public:
	void init(IGame& game_interface) override;
	void clear(IGame& game_interface) override;
	void idle(IGame& game_interface, float t) override;
	void draw(IGame& game_interface) override;

	void keyPressCallback(IInputManager& interface, const InputKeyboard& input);

private:
	std::shared_ptr<ImageAsset> texture;
	float progress;
	float elapsed;
};