#pragma once

#include "Entity/Entity2D.h"
#include "Entity/EntityPhysics.h"

class Enemy : virtual public Entity2D, virtual public EntityPhysics {
public:
	Enemy()
		: Entity2D(), EntityPhysics() {}

	void init(IGame& game_interface, Map& map) override;
	void idle(float t, Map& map) override;
	void draw() override;

private:
	float alive_time = 0;
	enum class DIRECTION { LEFT, RIGHT } direction = DIRECTION::LEFT;

};