#pragma once

#include "Asset/ImageAsset.h"
#include "Entity/Entity.h"

// An abstract 2D entity class.
class Entity2D : virtual public Entity {
public:
	bool is_visible = true;

	std::shared_ptr<ImageAsset> texture;
	Vector2<double> size;

	// Set the texture of this Entity2D instance.
	void setTexture();
	void setTexture(const std::shared_ptr<ImageAsset>& img_asset_ptr);

	void draw() override;
};