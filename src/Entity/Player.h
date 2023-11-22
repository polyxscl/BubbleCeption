#pragma once

#include "Entity/Entity2D.h"
#include "Entity/EntityPhysics.h"

class Player : virtual public Entity2D, virtual public EntityPhysics {
public:
	Player() {}

	void init(IGame& game_interface, Map& map) override;
	void idle(float t, Map& map) override;
	void draw() override;
	 
	void startMovingLeft();
	void startMovingRight();
	void stopMovingLeft();
	void stopMovingRight();
	
	void jump();

private:
	enum class DIRECTION { LEFT, RIGHT } direction = DIRECTION::LEFT;

	bool is_moving_left = false;
	bool is_moving_right = false;
};