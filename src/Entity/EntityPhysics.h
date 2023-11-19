#pragma once

#include "Util/Rect.h"
#include "Entity/Entity.h"

// An abstract entity class for physics.
class EntityPhysics : virtual public Entity {
public:
	bool is_moving = false;
	Vector3<float> vel, accel;
	Rect<float> hitbox;

	Rect<float> getWorldHitbox() const;

	void idle(float t) override;
};