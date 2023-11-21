#include "Entity2D.h"

#define RAD45 0.7853981633974483096156608458198757210492923498437764552437361480
#define SQRT2 1.4142135623730950488016887242096980785696718753769480731766797379

void Entity2D::draw() {
	// If texture does not exist, return.
	if (!texture) return;

	// If the entity is not visible, return.
	if (!is_visible) return;

	auto& unwrapped_texture = *(texture.get());

	glEnable(GL_BLEND);
	// Set the blending function for textures with alpha
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, unwrapped_texture.getTextureID());
	glBegin(GL_QUADS);
	if (flipped) {
		glTexCoord2f(0.0f, 0.0f); glVertex2f(size.x / 2 * SQRT2 * std::cosf(rotation + RAD45) + pos.x, -size.y / 2 * SQRT2 * std::sinf(rotation + RAD45) + pos.y);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(size.x / 2 * SQRT2 * std::cosf(rotation - RAD45) + pos.x, -size.y / 2 * SQRT2 * std::sinf(rotation - RAD45) + pos.y);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(-size.x / 2 * SQRT2 * std::cosf(rotation + RAD45) + pos.x, size.y / 2 * SQRT2 * std::sinf(rotation + RAD45) + pos.y);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(-size.x / 2 * SQRT2 * std::cosf(rotation - RAD45) + pos.x, size.y / 2 * SQRT2 * std::sinf(rotation - RAD45) + pos.y);
	}
	else {
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-size.x / 2 * SQRT2 * std::cosf(rotation + RAD45) + pos.x, -size.y / 2 * SQRT2 * std::sinf(rotation + RAD45) + pos.y);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-size.x / 2 * SQRT2 * std::cosf(rotation - RAD45) + pos.x, -size.y / 2 * SQRT2 * std::sinf(rotation - RAD45) + pos.y);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(size.x / 2 * SQRT2 * std::cosf(rotation + RAD45) + pos.x, size.y / 2 * SQRT2 * std::sinf(rotation + RAD45) + pos.y);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(size.x / 2 * SQRT2 * std::cosf(rotation - RAD45) + pos.x, size.y / 2 * SQRT2 * std::sinf(rotation - RAD45) + pos.y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}