#pragma once

#include "Tile.h"

class PlatformTile : public Tile {
public:
	using Tile::Tile;

	void init(IGame& game_interface, std::string palette) override;
	void clear(IGame& game_interface) override;
	void idle(float t) override;

	bool isCollision(IEntityPhysics* ep) const override;
	void onCollision(IEntityPhysics* ep) override;

};