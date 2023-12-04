#pragma once

#include "Util/Rect.h"
#include "Entity.interface.h"

class IEntityPhysics : virtual public IEntity {
public:
	bool is_moving = false;
	bool is_down = false;
	Vector3<float> vel, accel;
	Rect<float> hitbox;

	bool should_collide = true;

	virtual Rect<float> getWorldHitbox() const = 0;
};