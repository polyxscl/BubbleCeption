#pragma once

#include "Util/Rect.h"
#include "Entity/Entity.h"
#include "Scene/Camera.h"
#include "Game.interface.h"

class Tile {
public:
	explicit Tile(Vector3<int> pos)
		: pos(pos), collidable(true), visible(true) {}

	virtual void init(IGame& game_interface) {};
	virtual void clear(IGame& game_interface) {};
	virtual void draw(const Camera& camera);
	virtual void idle(float t) {};

	virtual bool isCollision(Entity* entity) const { return false; };
	virtual void onCollision(Entity* entity) {};

	Rect<float> getWorldHitbox() const;

	const Vector3<int> pos;
	Rect<float> hitbox;

	bool collidable;
	bool visible;

protected:
	std::shared_ptr<ImageAsset> texture;
	
};