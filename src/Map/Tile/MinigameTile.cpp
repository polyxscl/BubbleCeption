#include "MinigameTile.h"

void MinigameTile::init(IGame& game_interface) {
	auto& asset_manager = game_interface.getIAssetManager();
	if (direction == Direction::LEFT)
		texture = asset_manager.getImageAsset("minigame_console_left");
	else
		texture = asset_manager.getImageAsset("minigame_console_right");

	hitbox = Rect<float>(Vector2<float>(-0.5f, -0.5f), Vector2<float>(0.5f, 0.5f));
}

void MinigameTile::clear(IGame& game_interface) {

}

void MinigameTile::idle(float t) {

}

bool MinigameTile::isCollision(IEntityPhysics* ep) const {
	if (!collidable) return false;

	return ep->getWorldHitbox().intersects(getWorldHitbox());
}

void MinigameTile::onCollision(IEntityPhysics* ep) {

}