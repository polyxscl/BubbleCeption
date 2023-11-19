#include "Entity2D.h"

void Entity2D::setTexture() {
	texture.reset();
}

void Entity2D::setTexture(const std::shared_ptr<ImageAsset>& img_asset_ptr) {
	texture = img_asset_ptr;
}

void Entity2D::draw() {
	// If texture does not exist, return.
	if (!texture) return;

	// If the entity is not visible, return.
	if (!is_visible) return;

	auto& unwrapped_texture = *(texture.get());

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, unwrapped_texture.getTextureID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-size.x / 2 + pos.x, -size.y / 2 + pos.y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-size.x / 2 + pos.x, size.y / 2 + pos.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(size.x / 2 + pos.x, size.y / 2 + pos.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(size.x / 2 + pos.x, -size.y / 2 + pos.y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}