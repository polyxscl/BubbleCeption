#include "SolidTile.h"

#include "Entity/EntityPhysics.h"

void SolidTile::init(IGame& game_interface) {
	auto& asset_manager = game_interface.getIAssetManager();
	texture = asset_manager.getImageAsset("solid_1");

	hitbox = Rect<float>(Vector2<float>(-0.5f, -0.5f), Vector2<float>(0.5f, 0.5f));
}

void SolidTile::clear(IGame& game_interface) {

}

void SolidTile::idle(float t) {

}

bool SolidTile::isCollision(IEntityPhysics* ep) const {
	if (!collidable) return false;

	return ep->getWorldHitbox().intersects(getWorldHitbox());
}

void SolidTile::onCollision(IEntityPhysics* ep) {
	if (!collidable) return;
	
	int selection = 0;

	auto ex = ep->pos.x;
	auto ey = ep->pos.y;
	auto evx = ep->vel.x;
	auto evy = ep->vel.y;
	auto x = pos.x;
	auto y = pos.y;

	bool top = ey + ep->hitbox.bottom() < y + hitbox.top();
	bool bottom = ey + ep->hitbox.top() > y + hitbox.bottom();
	bool left = ex + ep->hitbox.right() > x + hitbox.left();
	bool right = ex + ep->hitbox.left() < x + hitbox.right();
		
	const float leeway = 0.0f;

	if (evx >= 0 && ex < x && left && ex - x + leeway < ey - y && ey - y < x - ex - leeway) {
		selection = 1;
	}
	else if (evx <= 0 && ex > x && right && x - ex + leeway < ey - y && ey - y < ex - x - leeway) {
		selection = 2;
	}

	if (evy >= 0 && ey < y && bottom && ey - y < ex - x && ex - x < y - ey) {
		selection = 3;
	}
	else if (evy <= 0 && ey > y && top && y - ey < ex - x && ex - x < ey - y) {
		selection = 4;
	}

	switch (selection) {
	case 1:
		ep->pos.x = x + hitbox.left() - ep->hitbox.right();
		break;
	case 2:
		ep->pos.x = x + hitbox.right() - ep->hitbox.left();
		break;
	case 3:
		ep->pos.y = y + hitbox.bottom() - ep->hitbox.top();
		ep->vel.y = 0;
		break;
	case 4:
		ep->pos.y = y + hitbox.top() - ep->hitbox.bottom();
		ep->vel.y = 0;
		ep->is_down = true;
		break;
	default:
		break;
	}
}