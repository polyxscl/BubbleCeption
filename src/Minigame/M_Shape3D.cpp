#include <random>

#include "Minigame/M_Shape3D.h"

M_Shape3D::M_Shape3D(float x, float y, float z) {
	this->center[0] = x;
	this->center[1] = y;
	this->center[2] = z;
}

void M_Shape3D::setCenter(float axis, float pos) {
	this->center[axis] = pos;
}

void M_Shape3D::setCenter(const Vector3f& c) {
	this->center = c;
}

Vector3f M_Shape3D::getCenter() const {
	return this->center;
}

void M_Shape3D::setVelocity(const Vector3f& v) {
	this->velocity = v;
}

Vector3f M_Shape3D::getVelocity() const {
	return this->velocity;
}

void M_Shape3D::setAcceleration(const Vector3f& a) {
	this->acceleration = a;
}

Vector3f M_Shape3D::getAcceleration() const {
	return this->acceleration;
}

void M_Shape3D::setRandomVelocity() {
	for (int i = 0; i < 3; i++) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> distribution(-5.0f, 5.0f);
		float randomFloat = distribution(gen);
		this->velocity[i] = randomFloat;
	}
}

void M_Shape3D::move() {
	this->center += this->velocity;
	this->velocity += this->acceleration;
}

bool M_Shape3D::operator<(const M_Shape3D& other) const {
	return this->center < other.center;
}

void M_Cube::settype(int i) {
	this->type = i;
}

void M_Cube::change_volume(float a) {
	this->length = a;
}

void M_Cube::Cubeset() {
	for (int i = 0; i < 3; i++) {
		this->bound[i][0] = this->center[i] + this->length / 2;
		this->bound[i][1] = this->center[i] - this->length / 2;
	}
	int c = 0;
	for (auto &i : this->bound[0]) {
		for (auto& j : this->bound[1]) {
			for (auto& k : this->bound[2]) {
				this->point[c].setPos(i, j, k);
				c++;
			}
		}
	}
}

int M_Cube::gettype() const {
	return this->type;
}

float M_Cube::getlen() const {
	return this->length;
}
void M_Cube::setlen(float a) {
	this->length = a;
}

void M_Box::setpoint(int i, Vector3f pos) {
	this->point[i] = pos;
}

void M_Box::setbound(int axis, int dir, float pos) {
	this->bound[axis][dir] = pos;
}

Vector3f M_Box::getpoint(int i) const {
	return this->point[i];
}

float M_Box::getbound(int axis, int dir) const {
	return this->bound[axis][dir];
}


void M_Sphere::setrad(float a) {
	this->radius = a;
}

float M_Sphere::getrad() const{
	return this->radius;
}