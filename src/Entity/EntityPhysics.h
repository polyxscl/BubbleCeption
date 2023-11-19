#pragma once

#include "Entity/Entity.h"

// An abstract entity class for physics.
class EntityPhysics : virtual public Entity {
public:
	bool is_moving = false;
	Vector3<float> vel, accel;

	void idle(float t) override;
};