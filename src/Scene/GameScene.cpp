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

	player = new Player(game_interface, *map);

	camera.setViewportSize(Vector2<float>(SCREEN_WIDTH, SCREEN_HEIGHT));
	camera.setCenter(Vector3<float>(SCREEN_WIDTH / 2.f - 0.5f, SCREEN_HEIGHT / 2, 0.0f));

	player->pos = Vector3<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	auto enemy = new Enemy(game_interface, *map);

	enemy->pos = Vector3<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	enemies.emplace(enemy);

	game = &game_interface;
}

void GameScene::clear(IGame& game_interface) {
	auto& input_manager = game_interface.getIInputManager();
	input_manager.detachSpecialKeyPressCallback("gs_spkey");
	input_manager.detachKeyPressCallback("gs_key");

	for (auto& enemy : enemies) {
		delete enemy;
	}
	enemies.clear();

	for (auto& bubble : bubbles) {
		delete bubble;
	}
	bubbles.clear();

	delete map;
}

void GameScene::idle(IGame& game_interface, float t) {
	player->idle(t, *map);
	map->handleCollision(player);
	
	for (auto it = enemies.begin(); it != enemies.end();) {
		auto enemy = *it;
		enemy->idle(t, *map);
		map->handleCollision(enemy);
		if (!enemy->alive)
			it = enemies.erase(it);
		else
			++it;
	}

	for (auto it = bubbles.begin(); it != bubbles.end();) {
		auto bubble = *it;
		bubble->idle(t, *map);
		if (!bubble->alive)
			it = bubbles.erase(it);
		else
			++it;
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
	player->draw();

	for (auto& enemy : enemies) {
		enemy->draw();
	}

	for (auto& bubble : bubbles) {
		bubble->draw();
	}
}

void GameScene::keyPressCallback(IInputManager& interface, const InputKeyboard& input) {
	switch (input.key) {
	case 'a':
		if (!input.was_down && input.down) {
			player->startMovingLeft();
		}
		else if (!input.down) {
			player->stopMovingLeft();
		}
		break;
	case 'd':
		if (!input.was_down && input.down) {
			player->startMovingRight();
		}
		else if (!input.down) {
			player->stopMovingRight();
		}
		break;
	case 'w':
		if (!input.was_down && input.down) {
			player->jump();
		}
		break;
	case ' ':
		if (!input.was_down && input.down) {
			auto bubble = player->shootBubble(*game, *map);
			bubbles.emplace(bubble);
		}
	}
}

void GameScene::specialKeyPressCallback(IInputManager& interface, const InputKeyboardSpecial& input) {

}