#include <deque>

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
	if (is_jumping) {
		player->jump();
	}

	for (auto it = bubbles.begin(); it != bubbles.end();) {
		auto bubble = *it;
		bubble->idle(t, *map);

		if (!bubble->alive) {
			delete bubble;
			it = bubbles.erase(it);
		}
		else
			++it;
	}
	
	for (auto it = enemies.begin(); it != enemies.end();) {
		auto enemy = *it;
		enemy->idle(t, *map);
		map->handleCollision(enemy);

		for (auto& bubble : bubbles) {
			if (bubble->isCollision(enemy)) {
				bubble->onCollision(enemy);
			}
		}

		if (!enemy->alive) {
			delete enemy;
			it = enemies.erase(it);
		} 
		else
			++it;
	}

	for (auto i1 = bubbles.begin(); i1 != bubbles.end(); ++i1) {
		auto i2 = i1;
		auto b1 = *i1;
		while (true) {
			++i2;
			if (i2 == bubbles.end()) break;
			auto b2 = *i2;
			if (b1->isCollision(b2)) {
				b1->onCollision(b2);
			}
		}
		if (player->isCollision(b1)) {
			player->onCollision(b1);

			std::unordered_set<Bubble*> visited;
			std::deque<Bubble*> dq;
			dq.push_back(b1);

			while (!dq.empty()) {
				auto b2 = dq.front();
				dq.pop_front();
				for (auto& b3 : bubbles) {
					if (visited.find(b3) != visited.end()) continue;
					if (b2->isCollision(b3)) {
						dq.push_back(b3);
					}
				}
				b2->killCaptured();
				b2->alive = false;
				visited.insert(b2);
			}
		}
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	static float ambient_vec[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
	static float diffuse_vec[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	static float specular_vec[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
	static float position_vec[4] = { 0.0f, 20.0f, 0.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_vec);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_vec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_vec);
	glLightfv(GL_LIGHT0, GL_POSITION, position_vec);

	for (auto& bubble : bubbles) {
		bubble->draw();
	}

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	player->draw();
	for (auto& enemy : enemies) {
		enemy->draw();
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
			is_jumping = true;
		}
		else if (!input.down) {
			is_jumping = false;
		}
		break;
	case ' ':
		if (!input.was_down && input.down) {
			if (bubbles.size() < 25) {
				auto bubble = player->shootBubble(*game, *map);
				bubbles.emplace(bubble);
			}
		}
	}
}

void GameScene::specialKeyPressCallback(IInputManager& interface, const InputKeyboardSpecial& input) {

}