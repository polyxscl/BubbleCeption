#pragma once

#include "Util/Vector.h"
#include "Game.interface.h"

class Entity {
public:
	virtual void init(IGame& game_interface) {};
	virtual void idle(float t) {};
	virtual void draw() {};

protected:
	Vector3<float> pos;

};