#pragma once

#include "Entity/Entity2D.h"
#include "Entity/EntityPhysics.h"

class Enemy : virtual public Entity2D, virtual public EntityPhysics {
public:
	Enemy()
		: Entity2D(), EntityPhysics() {}

	void init(IGame& game_interface) override;
	void idle(float t) override;
	void draw() override;

private:
	bool is_visible = true;
	Vector3<float> size;
	std::shared_ptr<ImageAsset> texture;

	enum class DIRECTION { LEFT, RIGHT } direction = DIRECTION::LEFT;

};