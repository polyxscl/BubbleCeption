#include "PlatformTile.h"

#include "Entity/EntityPhysics.h"

void PlatformTile::init(IGame& game_interface) {
	auto& asset_manager = game_interface.getIAssetManager();
	texture = asset_manager.getImageAsset("platform_1");

	hitbox = Rect<float>(Vector2<float>(0.2f, 0.2f), Vector2<float>(0.5f, 0.5f));
}

void PlatformTile::clear(IGame& game_interface) {

}

void PlatformTile::idle(float t) {

}

bool PlatformTile::isCollision(Entity* entity) const {
	if (!collidable) return false;

	EntityPhysics* ep = dynamic_cast<EntityPhysics*>(entity);

	if (ep) {
		return ep->getWorldHitbox().intersects(getWorldHitbox());
	}
}

void PlatformTile::onCollision(Entity* entity) {
	if (!collidable) return;

	EntityPhysics* ep = dynamic_cast<EntityPhysics*>(entity);

	if (ep) {
		int selection = 0;

		auto ex = ep->pos.x;
		auto ey = ep->pos.y;
		auto x = pos.x;
		auto y = pos.y;

		auto leeway = 0.1f;

		if (ey + ep->hitbox.bottom() + leeway > y + hitbox.bottom() && ey + ep->hitbox.bottom() < y + hitbox.top() && ep->vel.y < 0) {
			ep->pos.y = y + hitbox.top() - ep->hitbox.bottom();
			ep->vel.y = 0;
		}
	}
}