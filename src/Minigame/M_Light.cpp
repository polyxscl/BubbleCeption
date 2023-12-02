#include "Minigame/M_Light.h"

Light::Light(float x, float y, float z, int L_ID) {
	this->lightID = L_ID;
	this->pos.setPos(x, y, z);
}

void Light::setAmbient(float x, float y, float z, float a) {
	this->ambient.setPos(x, y, z, a);
}

void Light::setDiffuse(float x, float y, float z, float a) {
	this->diffuse.setPos(x, y, z, a);
}

void Light::setSpecular(float x, float y, float z, float a) {
	this->specular.setPos(x, y, z, a);
}

void Light::draw() const{
	float setting[3][4];
	for (int i = 0; i < 4; i++) {
		setting[0][i] = this->ambient[i];
		setting[1][i] = this->diffuse[i];
		setting[2][i] = this->specular[i];
	}
	float position[3] = { this->pos[0], this->pos[1], this->pos[2] };
	glEnable(this->lightID);
	glLightfv(this->lightID, GL_AMBIENT, setting[0]);
	glLightfv(this->lightID, GL_DIFFUSE, setting[1]);
	glLightfv(this->lightID, GL_SPECULAR, setting[2]);
	glLightfv(this->lightID, GL_POSITION, position);
}

int Light::getID() {
	return this->lightID;
}