#pragma once

#include "Entity.h"
#include "Render/Model.h"

class Entity3D : virtual public Entity {
public:
	using Entity::Entity;
	virtual ~Entity3D() override;

	virtual void draw() override;

protected:
	bool is_visible = true;
	Model* model;

};