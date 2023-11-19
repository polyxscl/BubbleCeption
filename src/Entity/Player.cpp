#include "Constants.h"
#include "Player.h"

void Player::init(IGame& game_interface) {
	is_visible = true;
	size = Vector3<float>(1.0f, 1.0f);

	vel = Vector3<float>(0.0f, -2.0f);

	auto& asset_manager = game_interface.getIAssetManager();
	setTexture(asset_manager.getImageAsset(""));
}

void Player::idle(float t) {
	EntityPhysics::idle(t);

	if (pos.y < -size.y)
		pos.y += SCREEN_HEIGHT + size.y;
}

void Player::startMovingLeft() {
	vel.x -= 2.f;
}

void Player::startMovingRight() {
	vel.x += 2.f;
}

void Player::stopMovingLeft() {
	vel.x += 2.f;
}

void Player::stopMovingRight() {
	vel.x -= 2.f;
}