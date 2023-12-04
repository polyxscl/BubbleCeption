#pragma once

#include "SolidTile.h"
#include "Util/Direction.h"

class ConveyorTile : public SolidTile {
public:
	using SolidTile::SolidTile;

	void init(IGame& game_interface, std::string palette) override;
	void clear(IGame& game_interface) override;
	void idle(float t) override;

	bool isCollision(IEntityPhysics* ep) const override;
	void onCollision(IEntityPhysics* ep) override;
	
	Direction direction = Direction::LEFT;

};
