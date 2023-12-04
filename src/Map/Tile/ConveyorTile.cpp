#include "ConveyorTile.h"

#include "Entity/EntityPhysics.h"

void ConveyorTile::init(IGame& game_interface, std::string palette) {
	auto& asset_manager = game_interface.getIAssetManager();
	if (direction == Direction::LEFT)
		texture = asset_manager.getImageAsset("conveyor_left");
	else
		texture = asset_manager.getImageAsset("conveyor_right");

	hitbox = Rect<float>(Vector2<float>(-0.5f, -0.5f), Vector2<float>(0.5f, 0.5f));
}

void ConveyorTile::clear(IGame& game_interface) {

}

void ConveyorTile::idle(float t) {

}

bool ConveyorTile::isCollision(IEntityPhysics* ep) const {
	if (!collidable) return false;
	if (!ep->should_collide) return false;

	return ep->getWorldHitbox().intersects(getWorldHitbox());
}

void ConveyorTile::onCollision(IEntityPhysics* ep) {
	SolidTile::onCollision(ep);
	
	if (direction == Direction::LEFT) {
		ep->pos.x -= 0.003f;
	}
	else if (direction == Direction::RIGHT) {
		ep->pos.x += 0.003f;
	}
}