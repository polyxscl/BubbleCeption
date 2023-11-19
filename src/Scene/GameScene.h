#pragma once

#include "Scene.h"
#include "Entity/Player.h"
#include "Scene/Camera.h"
#include "Map/Map.h"

class GameScene : public Scene{
public:
	void init(IGame& game_interface) override;
	void clear(IGame& game_interface) override;
	void idle(IGame& game_interface, float t) override;
	void draw(IGame& game_interface) override;

	void specialKeyPressCallback(IInputManager& interface, const InputKeyboardSpecial& input);

private:
	Player player;
	Camera camera;
	Map* map;

};