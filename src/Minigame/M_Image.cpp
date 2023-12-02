#include "M_Image.h"

void M_Image::draw(Vector3f a, Vector3f b, Vector3f c, Vector3f d) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, asset ? asset->getTextureID() : 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex4f(a[0], a[1], a[2], 1.0);
	glTexCoord2f(0.0f, 1.0f); glVertex4f(b[0], b[1], b[2], 1.0);
	glTexCoord2f(1.0f, 1.0f); glVertex4f(c[0], c[1], c[2], 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex4f(d[0], d[1], d[2], 1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}