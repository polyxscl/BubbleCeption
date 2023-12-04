#include <cmath>
#include <ctime>
#include <random>

#include "Constants.h"

#include "Enemy.h"

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dist(0.f, 1.f);

Enemy::Enemy(IGame& game_interface, Map& map)
	: Entity(game_interface, map), Entity2D(game_interface, map), EntityPhysics(game_interface, map) {
	is_visible = true;
	size = Vector3<float>(1.0f, 1.0f);

	vel = Vector3<float>(0.0f, 0.0f);
	accel = Vector3<float>(0.0f, -20.0f);
	hitbox = Rect<float>(Vector2<float>(-0.5f, -0.5f), Vector2<float>(0.5f, 0.5f));

	should_collide = true;

	auto& asset_manager = game_interface.getIAssetManager();
	texture = asset_manager.getImageAsset("enemy");
}

void Enemy::idle(float t, Map& map) {
	alive_time += t;

	if (pos.y + size.y / 2.f > SCREEN_HEIGHT - 0.5f) {
		pos.y = +0.5f + size.y / 2.f;
	}
	else if (pos.y - size.y / 2.f < -0.5f) {
		pos.y = SCREEN_HEIGHT - size.y / 2.f - 0.5f;
	}
	if (captured) {
		rotation = std::fmod(alive_time, 1.0f) * 2 * PI;
		should_collide = false;
		return;
	}
	else {
		rotation = 0.0f;
		should_collide = true;
	}

	if (direction == Direction::LEFT) {
		if (map.hasTile(pos + Vector3<float>(0.5f, -0.5f, 0.0f)) && !map.hasTile(pos + Vector3<float>(0.0f, -0.5f, 0.0f)) || map.hasTile(pos + Vector3<float>(-0.1f, 0.0f, 0.0f))) {
			direction = Direction::RIGHT;
			flipped = false;
		}
	}
	else {
		if (map.hasTile(pos + Vector3<float>(0.5f, -0.5f, 0.0f)) && !map.hasTile(pos + Vector3<float>(1.0f, -0.5f, 0.0f)) || map.hasTile(pos + Vector3<float>(+1.1f, 0.0f, 0.0f))) {
			direction = Direction::LEFT;
			flipped = true;
		}
	}

	if (direction == Direction::LEFT) {
		vel.x = -speed;
	}
	else {
		vel.x = speed;
	}

	if (pos.x < 0.0f) {
		pos.x = 1.0f;
	}
	else if (pos.x > SCREEN_WIDTH) {
		pos.x = SCREEN_WIDTH - 1.0f;
	}

	if (dist(gen) > 0.998f)
		vel.y = 20.f;

	if (vel.y < -10.f)
		vel.y = -10.f;

	EntityPhysics::idle(t, map);
}

void Enemy::draw() {
	Entity2D::draw();
}