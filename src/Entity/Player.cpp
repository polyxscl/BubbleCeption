#include <algorithm>

#include "Constants.h"
#include "Player.h"

void Player::init(IGame& game_interface) {
	is_visible = true;
	size = Vector3<float>(1.0f, 1.0f);

	vel = Vector3<float>(0.0f, -5.0f);
	accel = Vector3<float>(0.0f, -5.0f);
	hitbox = Rect<float>(Vector2<float>(-0.5f, -0.5f), Vector2<float>(0.5f, 0.5f));

	auto& asset_manager = game_interface.getIAssetManager();
	setTexture(asset_manager.getImageAsset(""));
}

void Player::idle(float t) {
	if (is_moving_left && is_moving_right) {
		vel.x = 0.f;
	}
	else if (is_moving_left) {
		vel.x = -5.f;
	}
	else if (is_moving_right) {
		vel.x = 5.f;
	}
	else {
		vel.x = 0.f;
	}

	EntityPhysics::idle(t);
	vel.y = std::max(vel.y, -5.0f);

	if (pos.y < -size.y)
		pos.y += SCREEN_HEIGHT + size.y;
	if (pos.y > SCREEN_HEIGHT)
		pos.y -= SCREEN_HEIGHT + size.y;
}

void Player::startMovingLeft() {
	is_moving_left = true;
}

void Player::startMovingRight() {
	is_moving_right = true;
}

void Player::stopMovingLeft() {
	is_moving_left = false;
}

void Player::stopMovingRight() {
	is_moving_right = false;
}

void Player::jump() {
	vel.y = 7.f;
}