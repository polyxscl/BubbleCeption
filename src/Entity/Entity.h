#pragma once

#include "Util/Vector.h"
#include "Game.interface.h"
#include "Map/Map.h"
#include "Entity.interface.h"

class Entity : virtual public IEntity {
public:
	Entity() = delete;
	explicit Entity(IGame& game_interface, Map& map) {};
	virtual ~Entity() {};

	virtual void idle(float t, Map& map) {};
	virtual void draw() {};

	bool alive = true;

};