#pragma once

#include <unordered_set>

#include "Scene.h"
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "Scene/Camera.h"
#include "Map/Map.h"

class GameScene : public Scene{
public:
	void init(IGame& game_interface) override;
	void clear(IGame& game_interface) override;
	void idle(IGame& game_interface, float t) override;
	void draw(IGame& game_interface) override;

	void keyPressCallback(IInputManager& interface, const InputKeyboard& input);
	void specialKeyPressCallback(IInputManager& interface, const InputKeyboardSpecial& input);

private:
	Player* player;
	Camera camera;
	Map* map;
	IGame* game;

	bool is_jumping = false;
	bool interaction = false;

	bool end = false;

	std::unordered_set<Enemy*> enemies;
	std::unordered_set<Bubble*> bubbles;

	int health = 3;
};