#pragma once

#include "Entity/Entity3D.h"
#include "Entity/EntityPhysics.h"
#include "Util/Direction.h"
#include "Render/SphereModel.h"

class Bubble : virtual public Entity3D, virtual public EntityPhysics {
public:

	Bubble(IGame& game_interface, Map& map);
	~Bubble() override;

	void idle(float t, Map& map) override;
	void draw() override;

	Direction direction = Direction::LEFT;
	
private:
	float time = 0;

	SphereModel* sphere_model;

};