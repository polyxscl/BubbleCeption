#pragma once

#include "Entity.h"
#include "Render/Model.h"

class Entity3D : virtual public Entity {
public:
	virtual void draw() override;

protected:
	bool is_visible = true;
	Model* model;

};