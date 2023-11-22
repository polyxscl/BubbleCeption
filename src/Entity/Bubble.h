#pragma once

#include "Entity/Entity3D.h"
#include "Entity/EntityPhysics.h"

class Bubble : virtual public Entity3D, virtual public EntityPhysics {
public:
	Bubble() {}

	void init(IGame& game_interface, Map& map) override;
	void clear() override;
	void idle(float t, Map& map) override;
	void draw() override;

private:
	float time = 0;

};