#pragma once

#include "Entity/Entity2D.h"
#include "Entity/EntityPhysics.h"

class Player : public Entity2D, public EntityPhysics {
public:
	Player()
		: Entity2D(), EntityPhysics() {}

	void init(IGame& game_interface) override;
	void idle(float t) override;

	void startMovingLeft();
	void startMovingRight();
	void stopMovingLeft();
	void stopMovingRight();

};