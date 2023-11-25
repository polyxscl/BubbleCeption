#pragma once

#include "Entity/Entity2D.h"
#include "Entity/EntityPhysics.h"
#include "Entity/Bubble.h"
#include "Util/Direction.h"

class Player : virtual public Entity2D, virtual public EntityPhysics {
public:
	Player(IGame& game_interface, Map& map);

	void idle(float t, Map& map) override;
	void draw() override;
	 
	void startMovingLeft();
	void startMovingRight();
	void stopMovingLeft();
	void stopMovingRight();
	
	void jump();

	Bubble* shootBubble(IGame& game_interface, Map& map);

private:
	Direction direction = Direction::LEFT;

	bool is_moving_left = false;
	bool is_moving_right = false;
};