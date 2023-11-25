#pragma once

#include "Util/Rect.h"
#include "Entity/Entity.h"
#include "EntityPhysics.interface.h"

// An abstract entity class for physics.
class EntityPhysics : virtual public IEntityPhysics, virtual public Entity {
public:
	using Entity::Entity;

	Rect<float> getWorldHitbox() const override;

	virtual void idle(float t, Map& map) override;
};