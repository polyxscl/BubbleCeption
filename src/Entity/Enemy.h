#pragma once

#include "Entity/Entity2D.h"
#include "Entity/EntityPhysics.h"
#include "Util/Direction.h"

class Enemy : virtual public Entity2D, virtual public EntityPhysics {
public:
	Enemy(IGame& game_interface, Map& map);

	void idle(float t, Map& map) override;
	void draw() override;

private:
	float alive_time = 0;
	Direction direction = Direction::LEFT;

};