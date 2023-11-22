#pragma once

#include "Util/Vector.h"
#include "Game.interface.h"
#include "Map/Map.h"
#include "Entity.interface.h"

class Entity : virtual public IEntity {
public:
	virtual void init(IGame& game_interface, Map& map) {};
	virtual void clear() {};
	virtual void idle(float t, Map& map) {};
	virtual void draw() {};

};