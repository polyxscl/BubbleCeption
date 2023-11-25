#include <cmath>

#include "Bubble.h"

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
	Entity::~Entity();
	Entity3D::~Entity3D();

	// Do not delete sphere_model here (double free)
}

void Bubble::idle(float t, Map& map) {
	time += t;
	auto new_size_val = std::min(time, 2.0f) * 0.35f;

	sphere_model->size = Vector3<float>(new_size_val, new_size_val, new_size_val);

	EntityPhysics::idle(t, map);

	if (direction == Direction::LEFT && vel.x > 0
		|| direction == Direction::RIGHT && vel.x < 0) {
		vel.x = accel.x = 0;
	}

	if (time > 5.0f)
		alive = false;
}

void Bubble::draw() {
	Entity3D::draw();
}