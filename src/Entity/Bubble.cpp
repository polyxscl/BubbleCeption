#include "Bubble.h"
#include "Constants.h"

#include "GL/freeglut.h"

Bubble::Bubble(IGame& game_interface, Map& map)
	: Entity(game_interface, map), Entity3D(game_interface, map), EntityPhysics(game_interface, map) {
	sphere_model = new SphereModel();
	sphere_model->slices = 20;
	sphere_model->stacks = 20;
	sphere_model->size = Vector3<float>(0.0f, 0.0f, 0.0f);
	
	auto& asset_manager = game_interface.getIAssetManager();
	sphere_model->material = asset_manager.getMaterialAsset("");

	model = sphere_model;
}

Bubble::~Bubble() {
	if (captured_enemy) {
		captured_enemy->captured = false;
	}

	// Do not delete sphere_model here (double free)
}

void Bubble::idle(float t, Map& map) {
	time += t;

	auto new_size_val = std::min(time, 0.5f) * 1.1f;
	if (!fully_blown) {
		sphere_model->size = Vector3<float>(new_size_val, new_size_val, new_size_val);
		
		if (time > 0.5f)
			fully_blown = true;
	}

	EntityPhysics::idle(t, map);

	if (pos.y < -new_size_val)
		pos.y += SCREEN_HEIGHT + new_size_val;
	if (pos.y > SCREEN_HEIGHT)
		pos.y -= SCREEN_HEIGHT + new_size_val;

	if (direction == Direction::LEFT && vel.x > terminal_vel.x) {
		vel.x = terminal_vel.x;
		accel.x = 0;
	}
	if (direction == Direction::RIGHT && vel.x < terminal_vel.x) {
		vel.x = terminal_vel.x;
		accel.x = 0;
	}

	if (vel.y > 3.0f) {
		vel.y = 3.0f;
		accel.y = 0.0f;
	}

	if (captured_enemy) {
		captured_enemy->pos = pos;
	}

	if (time > 5.0f)
		alive = false;
}

void Bubble::draw() {
	Entity3D::draw();
}

void Bubble::onCollision(Enemy* enemy) {
	enemy->captured = true;
	captured_enemy = enemy;
}

bool Bubble::isCollision(Enemy* enemy) {
	if (enemy->captured || fully_blown) return false;
	auto dist = enemy->pos.dist(pos);
	return dist < 0.55f;
}

void Bubble::onCollision(Bubble* bubble) {
	auto dpos = pos - bubble->pos;
	auto v1_prime = vel - 0.5f * ((vel - bubble->vel).dot(dpos)) / std::pow(dpos.size(), 2) * dpos;
	auto v2_prime = bubble->vel - 0.5f * ((bubble->vel - vel).dot(dpos)) / std::pow(dpos.size(), 2) * dpos;

	vel = v1_prime;
	bubble->vel = v2_prime;
}

bool Bubble::isCollision(Bubble* bubble) {
	auto dist = bubble->pos.dist(pos);
	return dist < 1.1f;
}