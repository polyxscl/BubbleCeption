#include "PlatformTile.h"

void PlatformTile::init(IGame& game_interface, std::string palette) {
	auto& asset_manager = game_interface.getIAssetManager();
	texture = asset_manager.getImageAsset("platform_" + palette);

	hitbox = Rect<float>(Vector2<float>(-0.5f, 0.2f), Vector2<float>(0.5f, 0.5f));
}

void PlatformTile::clear(IGame& game_interface) {

}

void PlatformTile::idle(float t) {

}

bool PlatformTile::isCollision(IEntityPhysics* ep) const {
	if (!collidable) return false;

	return ep->getWorldHitbox().intersects(getWorldHitbox());
}

void PlatformTile::onCollision(IEntityPhysics* ep) {
	if (!collidable) return;
	if (!ep->should_collide) return;

	int selection = 0;

	auto ex = ep->pos.x;
	auto ey = ep->pos.y;
	auto x = pos.x;
	auto y = pos.y;

	auto leeway = 0.1f;

	if (ey + ep->hitbox.bottom() + leeway > y + hitbox.bottom() && ey + ep->hitbox.bottom() < y + hitbox.top() && ep->vel.y < 0) {
		ep->pos.y = y + hitbox.top() - ep->hitbox.bottom();
		ep->vel.y = 0;
		ep->is_down = true;
	}
}