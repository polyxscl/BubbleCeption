#pragma once

#include "Entity/Entity3D.h"
#include "Entity/EntityPhysics.h"
#include "Entity/Enemy.h"
#include "Util/Direction.h"
#include "Render/SphereModel.h"

class Bubble : virtual public Entity3D, virtual public EntityPhysics {
public:

	Bubble(IGame& game_interface, Map& map);
	~Bubble() override;

	void idle(float t, Map& map) override;
	void draw() override;

	void onCollision(Enemy* enemy);
	bool isCollision(Enemy* enemy);

	void onCollision(Bubble* bubble);
	bool isCollision(Bubble* bubble);

	void killCaptured();
	bool isFullyBlown();

	Direction direction = Direction::LEFT;
	
	Vector3<float> terminal_vel;

	float getSize();

private:
	float time = 0;
	bool fully_blown = false;
	Enemy* captured_enemy = nullptr;

	float size = 0;

	SphereModel* sphere_model;

};