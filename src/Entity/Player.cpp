#include <algorithm>

#include "Constants.h"
#include "Player.h"

void Player::init(IGame& game_interface) {
	is_visible = true;
	size = Vector3<float>(1.0f, 1.0f);

	vel = Vector3<float>(0.0f, 0.0f);
	accel = Vector3<float>(0.0f, -20.0f);
	hitbox = Rect<float>(Vector2<float>(-0.5f, -0.5f), Vector2<float>(0.5f, 0.5f));

	auto& asset_manager = game_interface.getIAssetManager();
	texture = asset_manager.getImageAsset("player");
}

void Player::draw() {
	// If texture does not exist, return.
	if (!texture) return;

	// If the entity is not visible, return.
	if (!is_visible) return;

	auto& unwrapped_texture = *(texture.get());

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, unwrapped_texture.getTextureID());
	glBegin(GL_QUADS);
	if (direction == DIRECTION::LEFT) {
		glTexCoord2f(0.0f, 0.0f); glVertex2f(size.x / 2 + pos.x, -size.y / 2 + pos.y);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(size.x / 2 + pos.x, size.y / 2 + pos.y);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(-size.x / 2 + pos.x, size.y / 2 + pos.y);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(-size.x / 2 + pos.x, -size.y / 2 + pos.y);
	}
	else if (direction == DIRECTION::RIGHT) {
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-size.x / 2 + pos.x, -size.y / 2 + pos.y);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-size.x / 2 + pos.x, size.y / 2 + pos.y);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(size.x / 2 + pos.x, size.y / 2 + pos.y);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(size.x / 2 + pos.x, -size.y / 2 + pos.y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
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
	vel.y = std::max(vel.y, -10.f);

	if (pos.y < -size.y)
		pos.y += SCREEN_HEIGHT + size.y;
	if (pos.y > SCREEN_HEIGHT)
		pos.y -= SCREEN_HEIGHT + size.y;
}

void Player::startMovingLeft() {
	direction = DIRECTION::LEFT;
	is_moving_left = true;
}

void Player::startMovingRight() {
	direction = DIRECTION::RIGHT;
	is_moving_right = true;
}

void Player::stopMovingLeft() {
	is_moving_left = false;
}

void Player::stopMovingRight() {
	is_moving_right = false;
}

void Player::jump() {
	vel.y = 12.f;
}