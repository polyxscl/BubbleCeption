#include <deque>
#include <random>
#include "Constants.h"
#include "GameScene.h"


#include "Map/Tile/SolidTile.h"
#include "Map/Tile/PlatformTile.h",

#include "MinigameScene.h"
#include "GameoverScene.h"

Logger GameScene::logger("GameScene");

using namespace std::placeholders;

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dist(3.f, 10.f);

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

	player->pos = Vector3<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 300.0f, 0.0f);
	
	for (int i = 0; i < 3; ++i) {
		auto enemy = new Enemy(game_interface, *map);
		enemy->pos = Vector3<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		enemy->speed = dist(gen);
		enemies.emplace(enemy);
	}

	for (int i = 0; i < 3; ++i) {
		auto enemy = new Enemy(game_interface, *map);
		enemy->pos = Vector3<int>(SCREEN_WIDTH / 2 - 5.0f, 2.0f, 0.0f);
		enemy->speed = dist(gen);
		enemies.emplace(enemy);
	}

	for (int i = 0; i < 3; ++i) {
		auto enemy = new Enemy(game_interface, *map);
		enemy->pos = Vector3<int>(SCREEN_WIDTH / 2 + 5.0f, 2.0f, 0.0f);
		enemy->speed = dist(gen);
		enemies.emplace(enemy);
	}

	game = &game_interface;

	max_health = 4;
	health = 4;

	hasHit = true;
	player->doHit();
}

void GameScene::clear(IGame& game_interface) {
	auto& input_manager = game_interface.getIInputManager();
	input_manager.detachSpecialKeyPressCallback("gs_spkey");
	input_manager.detachKeyPressCallback("gs_key");

	for (auto& enemy : enemies) {
		if (enemy != nullptr) {
			delete enemy;
		}
	}
	enemies.clear();

	for (auto& bubble : bubbles) {
		if (bubble != nullptr) {
			delete bubble;
		}
	}
	bubbles.clear();

	if (map != nullptr) {
		delete map;
		map = nullptr;
	}

	if (player != nullptr) {
		delete player;
	}
}

void GameScene::idle(IGame& game_interface, float t) {
	if (this->end) {
		finish();
		return;
	}

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
			if (bubble->isCollision(enemy) && !enemy->captured && !bubble->hasEnemy()) {
				bubble->onCollision(enemy);
			}
		}

		if (enemy->getWorldHitbox().intersects(player->getWorldHitbox()) && !player->isHit() && !enemy->captured) {
			player->doHit();
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

			auto count = 0;
			auto mul = 1;
			while (!dq.empty()) {
				auto b2 = dq.front();
				dq.pop_front();
				for (auto& b3 : bubbles) {
					if (visited.find(b3) != visited.end()) continue;
					if (b2->isCollision(b3)) {
						dq.push_back(b3);
					}
				}
				count++;
				if (b2->hasEnemy()) {
					mul++;
				}
				b2->killCaptured();
				b2->alive = false;
				visited.insert(b2);
			}
			score += count * 100 * mul;
		}
	}

	if (health == 0) {
		this->paused = true;
		this->end = true;
		append(new GameoverScene());
	}

	auto& asset_manager = game->getIAssetManager();

	if (enemies.empty()) {
		stage++;
		logger << "Stage " << stage << logger.info;
		delete map;
		map = new Map();
		map->loadFromMapAsset(game_interface, asset_manager.getMapAsset("level2"));

		if (stage == 2) {
			for (int i = 0; i < 3; ++i) {
				auto enemy = new Enemy(game_interface, *map);
				enemy->pos = Vector3<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
				enemy->speed = dist(gen);
				enemies.emplace(enemy);
			}

			for (int i = 0; i < 3; ++i) {
				auto enemy = new Enemy(game_interface, *map);
				enemy->pos = Vector3<int>(SCREEN_WIDTH / 2 - 5.0f, 2.0f, 0.0f);
				enemy->speed = dist(gen);
				enemies.emplace(enemy);
			}

			for (int i = 0; i < 3; ++i) {
				auto enemy = new Enemy(game_interface, *map);
				enemy->pos = Vector3<int>(SCREEN_WIDTH / 2 + 5.0f, 2.0f, 0.0f);
				enemy->speed = dist(gen);
				enemies.emplace(enemy);
			}
		}

		hasHit = true;
		player->doHit();
	}

	score = std::max(0, score);
	score_display += ((float) score - score_display) / 64.f;

	if (!hasHit && player->isHit()) {
		hasHit = true;
		score /= 2;
		health--;
	}
	else if (!player->isHit()) {
		hasHit = false;
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

	auto& asset_manager = game_interface.getIAssetManager();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < max_health; ++i) {
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, asset_manager.getImageAsset(i < health ? "heart" : "heart_broken")->getTextureID());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f + i, -0.5f);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f + i, 0.5f);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f + i, 0.5f);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f + i, -0.5f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, asset_manager.getImageAsset("score")->getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.25f, -1.25f + SCREEN_HEIGHT);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.25f, -0.75f + SCREEN_HEIGHT);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(2.25f, -0.75f + SCREEN_HEIGHT);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(2.25f, -1.25f + SCREEN_HEIGHT);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	int score_temp = std::lround(score_display);
	for (int i = 0; i < 8; ++i) {
		auto j = 7 - i;
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, asset_manager.getImageAsset("number_" + to_string(score_temp % 10))->getTextureID());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.25f + j / 2.f, -1.75f + SCREEN_HEIGHT);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.25f + j / 2.f, -1.25f + SCREEN_HEIGHT);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(0.25f + j / 2.f, -1.25f + SCREEN_HEIGHT);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(0.25f + j / 2.f, -1.75f + SCREEN_HEIGHT);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		score_temp /= 10;
	}
	glDisable(GL_BLEND);
}

void GameScene::keyPressCallback(IInputManager& interface, const InputKeyboard& input) {
	if (!enabled) return;
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
		break;
	}
}

void GameScene::specialKeyPressCallback(IInputManager& interface, const InputKeyboardSpecial& input) {
	if (!enabled) return;
}