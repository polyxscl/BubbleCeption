#include <cmath>
#include <ctime>

#include "Enemy.h"

void Enemy::init(IGame& game_interface, Map& map) {
	is_visible = true;
	size = Vector3<float>(1.0f, 1.0f);

	vel = Vector3<float>(0.0f, 0.0f);
	accel = Vector3<float>(0.0f, -20.0f);
	hitbox = Rect<float>(Vector2<float>(-0.5f, -0.5f), Vector2<float>(0.5f, 0.5f));

	auto& asset_manager = game_interface.getIAssetManager();
	texture = asset_manager.getImageAsset("");
}

void Enemy::idle(float t, Map& map) {
	alive_time += t;

	if (direction == DIRECTION::LEFT) {
		if (!map.hasTile(pos + Vector3<float>(0.0f, -0.5f, 0.0f))) {
			direction = DIRECTION::RIGHT;
		}
	}
	else {
		if (!map.hasTile(pos + Vector3<float>(1.0f, -0.5f, 0.0f))) {
			direction = DIRECTION::LEFT;
		}
	}

	if (direction == DIRECTION::LEFT) {
		vel.x = -5.0f;
	}
	else {
		vel.x = 5.0f;
	}

	EntityPhysics::idle(t, map);
}

void Enemy::draw() {
	Entity2D::draw();
}