#include "Entity3D.h"

void Entity3D::draw() {
	// If model does not exist, return.
	if (!model) return;

	// If the entity is not visible, return.
	if (!is_visible) return;
	
	model->draw();

}