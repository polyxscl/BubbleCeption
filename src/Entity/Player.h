#pragma once

#include "Entity/EntityPhysics.h"

class Player : public EntityPhysics {
public:
	Player()
		: EntityPhysics() {}

	void init(IGame& game_interface) override;
	void idle(float t) override;
	void draw() override;

	void startMovingLeft();
	void startMovingRight();
	void stopMovingLeft();
	void stopMovingRight();
	
	void jump();

private:
	bool is_visible = true;
	Vector3<float> size;
	std::shared_ptr<ImageAsset> texture;

	enum class DIRECTION { LEFT, RIGHT } direction;

	bool is_moving_left = false;
	bool is_moving_right = false;
};