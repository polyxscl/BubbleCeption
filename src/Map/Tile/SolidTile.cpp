#include "SolidTile.h"

#include "Entity/EntityPhysics.h"

Rect<float> SolidTile::hitbox = Rect<float>(Vector2<float>(-0.5f, -0.5f), Vector2<float>(0.5f, 0.5f));

void SolidTile::init(IGame& game_interface) {
	auto& asset_manager = game_interface.getIAssetManager();
	texture = asset_manager.getImageAsset("solid_1");
}

void SolidTile::clear(IGame& game_interface) {

}

void SolidTile::idle(float t) {

}

bool SolidTile::isCollision(Entity* entity) const {
	if (!collidable) return false;

	EntityPhysics* ep = dynamic_cast<EntityPhysics*>(entity);

	if (ep) {
		return ep->getWorldHitbox().intersects(getWorldHitbox());
	}
}

void SolidTile::onCollision(Entity* entity) {
	if (!collidable) return;
	
	EntityPhysics* ep = dynamic_cast<EntityPhysics*>(entity);

	if (ep) {
		float min_dist = INFINITY;
		int selection = 0;

		if (ep->pos.x < pos.x && ep->pos.x + ep->hitbox.right() > pos.x + hitbox.left()) {
			min_dist = ep->pos.x - pos.x;
			selection = 1;
		}
		if (ep->pos.x > pos.x && ep->pos.x + ep->hitbox.left() < pos.x + hitbox.right()) {
			auto dist = pos.x - ep->pos.x;
			if (min_dist > dist) {
				min_dist = dist;
				selection = 2;
			}
		}
		if (ep->pos.y > pos.y && ep->pos.y + ep->hitbox.top() < pos.y + hitbox.bottom()) {
			auto dist = ep->pos.y - pos.y;
			if (min_dist > dist) {
				min_dist = dist;
				selection = 3;
			}
		}
		if (ep->pos.y < pos.y && ep->pos.y + ep->hitbox.bottom() > pos.y + hitbox.top()) {
			auto dist = pos.y - ep->pos.y;
			if (min_dist > dist) {
				min_dist = dist;
				selection = 4;
			}
		}
		switch (selection) {
		case 1:
			ep->pos.x = pos.x + hitbox.left() - ep->hitbox.right();
			break;
		case 2:
			ep->pos.x = pos.x + hitbox.right() - ep->hitbox.left();
			break;
		case 3:
			ep->pos.y = pos.y + hitbox.bottom() - ep->hitbox.top();
			break;
		case 4:
			ep->pos.y = pos.y + hitbox.top() - ep->hitbox.bottom();
			break;
		default:
			break;
		}
	}
}