#include <algorithm>
#include <ctime>
#include <random>

#include "Constants.h"
#include "Player.h"

static std::mt19937 engine(time(0));
static std::uniform_real_distribution<float> bubble_vel_dist(-0.5f, 0.5f);
static auto bubble_vel_gen = std::bind(bubble_vel_dist, engine);

Player::Player(IGame& game_interface, Map& map)
	: Entity(game_interface, map), Entity2D(game_interface, map), EntityPhysics(game_interface, map) {
	is_visible = true;
	size = Vector3<float>(1.0f, 1.0f);

	vel = Vector3<float>(0.0f, 0.0f);
	accel = Vector3<float>(0.0f, -20.0f);
	hitbox = Rect<float>(Vector2<float>(-0.5f, -0.5f), Vector2<float>(0.5f, 0.5f));

	auto& asset_manager = game_interface.getIAssetManager();
	texture = asset_manager.getImageAsset("player");
}

void Player::idle(float t, Map& map) {
	is_down = false;
	if (hit) {
		hit_time += t;
		if (hit_time > 3.0f) {
			hit = false;
		}
	}

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

	EntityPhysics::idle(t, map);
	vel.y = std::max(vel.y, -10.f);

	if (pos.y < -size.y)
		pos.y += SCREEN_HEIGHT + size.y;
	if (pos.y > SCREEN_HEIGHT)
		pos.y -= SCREEN_HEIGHT + size.y;
}

void Player::draw() {
	if (hit && std::fmod(hit_time * 4, 2) < 1.0f) return;
	Entity2D::draw();
}

void Player::startMovingLeft() {
	direction = Direction::LEFT;
	flipped = true;
	is_moving_left = true;
}

void Player::startMovingRight() {
	direction = Direction::RIGHT;
	flipped = false;
	is_moving_right = true;
}

void Player::stopMovingLeft() {
	is_moving_left = false;
}

void Player::stopMovingRight() {
	is_moving_right = false;
}

void Player::onCollision(Bubble* bubble) {
	if (pos.y > bubble->pos.y) {
		vel.y = 6.f;
	}
}

bool Player::isCollision(Bubble* bubble) {
	return bubble->isFullyBlown() && bubble->pos.dist(pos) < bubble->getSize() + size.x;
}

void Player::jump() {
	if (is_down) {
		vel.y = 12.f;
	}
}

Bubble* Player::shootBubble(IGame& game_interface, Map& map) {
	auto bubble = new Bubble(game_interface, map);

	bubble->pos = this->pos;
	bubble->direction = this->direction;
	auto term_vel = bubble_vel_gen();
	if (this->direction == Direction::LEFT) {
		bubble->vel.x = -10.0f;
		bubble->vel.y = -1.0f;
		bubble->terminal_vel.x = term_vel;
		bubble->accel.x = 20.0f;
		bubble->accel.y = 6.0f;
	}
	else if (this->direction == Direction::RIGHT) {
		bubble->vel.x = 10.0f;
		bubble->vel.y = -1.0f;
		bubble->terminal_vel.x = term_vel;
		bubble->accel.x = -20.0f;
		bubble->accel.y = 6.0f;
	}

	return bubble;
}

void Player::doHit() {
	hit = true;
	hit_time = 0.0f;
}

bool Player::isHit() {
	return hit;
}