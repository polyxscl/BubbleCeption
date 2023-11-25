#include "Entity3D.h"

#include "GL/freeglut.h"

Entity3D::~Entity3D() {
	delete model;
}

void Entity3D::draw() {
	// If model does not exist, return.
	if (!model) return;

	// If the entity is not visible, return.
	if (!is_visible) return;
	
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	model->draw();
	glPopMatrix();

}