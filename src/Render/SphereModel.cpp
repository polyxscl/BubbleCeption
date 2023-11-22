#include "SphereModel.h"

#include <GL/freeglut.h>

void SphereModel::draw() {
	material->apply();
	glPushMatrix();
	glScalef(size.x, size.y, size.z);
	glutSolidSphere(1.f, slices, stacks);
	glPopMatrix();
}