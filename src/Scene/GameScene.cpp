#include "Constants.h"
#include "GameScene.h"

#include "Map/Tile/SolidTile.h"
#include "Map/Tile/PlatformTile.h"

using namespace std::placeholders;

void GameScene::init(IGame& game_interface) {
auto& input_manager = game_interface.getIInputManager();
	input_manager.attachKeyPressCallback(
		"gs_key",
		std::bind(&GameScene::keyPressCallback, this, _1, _2)
	);
	input_manager.attachSpecialKeyPressCallback(
		"gs_spkey",
		std::bind(&GameScene::specialKeyPressCallback, this, _1, _2)
	);

	auto& asset_manager = game_interface.getIAssetManager();
	map = new Map();
	map->loadFromMapAsset(game_interface, asset_manager.getMapAsset("level1"));

	player.init(game_interface, *map);

	camera.setViewportSize(Vector2<float>(SCREEN_WIDTH, SCREEN_HEIGHT));
	camera.setCenter(Vector3<float>(SCREEN_WIDTH / 2.f - 0.5f, SCREEN_HEIGHT / 2, 0.0f));

	player.pos = Vector3<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	auto enemy = new Enemy();

	enemy->init(game_interface, *map);
	enemy->pos = Vector3<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	enemies.emplace("1", enemy);
}

void GameScene::clear(IGame& game_interface) {
	auto& input_manager = game_interface.getIInputManager();
	input_manager.detachSpecialKeyPressCallback("gs_spkey");
	input_manager.detachKeyPressCallback("gs_key");

	for (auto& [id, enemy] : enemies) {
		delete enemy;
	}
	enemies.clear();

	delete map;
}

void GameScene::idle(IGame& game_interface, float t) {
	player.idle(t, *map);
	map->handleCollision(&player);

	for (auto& [id, enemy] : enemies) {
		enemy->idle(t, *map);
		map->handleCollision(enemy);
	}
}

void GameScene::draw(IGame& game_interface) {

	auto viewport = camera.getViewport();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		viewport.left(), viewport.right(), viewport.bottom(), viewport.top(),
		-100.0, 100.0
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (map)
		map->draw(camera);
	player.draw();

	for (auto& [id, enemy] : enemies) {
		enemy->draw();
	}
}

void GameScene::keyPressCallback(IInputManager& interface, const InputKeyboard& input) {
	switch (input.key) {
	case 'a':
		if (!input.was_down && input.down) {
			player.startMovingLeft();
		}
		else if (!input.down) {
			player.stopMovingLeft();
		}
		break;
	case 'd':
		if (!input.was_down && input.down) {
			player.startMovingRight();
		}
		else if (!input.down) {
			player.stopMovingRight();
		}
		break;
	case 'w':
		if (!input.was_down && input.down) {
			player.jump();
		}
		break;
	}
}

void GameScene::specialKeyPressCallback(IInputManager& interface, const InputKeyboardSpecial& input) {

}