#include "SpikeTile.h"

#include "Entity/EntityPhysics.h"

void SpikeTile::init(IGame& game_interface, std::string palette) {
	auto& asset_manager = game_interface.getIAssetManager();
	texture = asset_manager.getImageAsset("spike");

	hitbox = Rect<float>(Vector2<float>(-0.5f, -0.5f), Vector2<float>(0.5f, 0.5f));
}

void SpikeTile::clear(IGame& game_interface) {

}

void SpikeTile::idle(float t) {

}

bool SpikeTile::isCollision(IEntityPhysics* ep) const {
	if (!collidable) return false;
	if (!ep->should_collide) return false;

	return ep->getWorldHitbox().intersects(getWorldHitbox());
}

void SpikeTile::onCollision(IEntityPhysics* ep) {
	SolidTile::onCollision(ep);
	if (!ep->isHit())
		ep->doHit();
}