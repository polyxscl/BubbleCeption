#include "EntityPhysics.h"

void EntityPhysics::idle(float t) {
	vel += accel * t;
	pos += vel * t;
}

Rect<float> EntityPhysics::getWorldHitbox() const {
	return Rect<float>(hitbox.getBottomLeft() + Vector2(pos), hitbox.getTopRight() + Vector2(pos));
}