#include "EntityPhysics.h"

void EntityPhysics::idle(float t) {
	pos += (vel + accel / 2) * t;
	vel += accel * t;
}

Rect<float> EntityPhysics::getWorldHitbox() const {
	return Rect<float>(hitbox.getBottomLeft() + Vector2(pos), hitbox.getTopRight() + Vector2(pos));
}