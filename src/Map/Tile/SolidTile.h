#pragma once

#include "Tile.h"

class SolidTile : public Tile {
public:
	using Tile::Tile;

	void init(IGame& game_interface) override;
	void clear(IGame& game_interface) override;
	void idle(float t) override;

	bool isCollision(IEntityPhysics* ep) const override;
	void onCollision(IEntityPhysics* ep) override;

};