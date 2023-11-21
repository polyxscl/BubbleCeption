#pragma once

#include "Entity.h"

class Entity2D : virtual public Entity {
public:
	virtual void draw() override;

protected:
	bool is_visible = true;
	bool flipped = false;
	float rotation = 0; // in degrees
	Vector3<float> size;
	std::shared_ptr<ImageAsset> texture;

};