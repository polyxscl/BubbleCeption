#pragma once

#include "Util/Rect.h"
#include "Entity/EntityPhysics.interface.h"
#include "Scene/Camera.h"
#include "Game.interface.h"

class Tile {
public:
	explicit Tile(Vector3<int> pos)
		: pos(pos), collidable(true), visible(true) {}

	virtual void init(IGame& game_interface, std::string palette) {};
	virtual void clear(IGame& game_interface) {};
	virtual void draw(const Camera& camera);
	virtual void idle(float t) {};

	virtual bool isCollision(IEntityPhysics* ep) const { return false; };
	virtual void onCollision(IEntityPhysics* ep) {};

	Rect<float> getWorldHitbox() const;

	const Vector3<int> pos;

	bool collidable;
	bool visible;

protected:
	std::shared_ptr<ImageAsset> texture;
	Rect<float> hitbox;

};