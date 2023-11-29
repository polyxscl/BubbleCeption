#include "Tile.h"

void Tile::draw(const Camera& camera) {

	auto& unwrapped_texture = *(texture.get());
	const auto size = Vector2<float>(1.0f, 1.0f);

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

Rect<float> Tile::getWorldHitbox() const {
	return Rect<float>(hitbox.getBottomLeft() + Vector2(pos), hitbox.getTopRight() + Vector2(pos));
}