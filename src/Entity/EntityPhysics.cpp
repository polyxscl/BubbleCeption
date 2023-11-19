#include "EntityPhysics.h"

void EntityPhysics::idle(float t) {
	pos += (vel + accel / 2) * t;
	vel += accel * t;
}