#pragma once

#include "Tile.h"

class SolidTile : virtual public Tile {
public:
	using Tile::Tile;

	virtual void init(IGame& game_interface) override;
	virtual void clear(IGame& game_interface) override;
	virtual void idle(float t) override;

	virtual bool isCollision(IEntityPhysics* ep) const override;
	virtual void onCollision(IEntityPhysics* ep) override;

};