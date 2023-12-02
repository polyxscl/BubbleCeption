#include "Minigame/M_Vector.h"

float& Vector3f::operator[](const int i) {
	return this->pos[i];
}

float Vector3f::operator[](const int i) const {
	return this->pos[i];
}

float& Vector4f::operator[](const int i) {
	return this->pos[i];
}

float Vector4f::operator[](const int i) const {
	return this->pos[i];
}

Vector3f::Vector3f(float x, float y, float z) {
	this->pos[0] = x;
	this->pos[1] = y;
	this->pos[2] = z;
}

Vector3f::Vector3f(const Vector3f& c) {
	this->pos[0] = c[0];
	this->pos[1] = c[1];
	this->pos[2] = c[2];
}


void Vector3f::setPos(float x, float y, float z) {
	this->pos[0] = x;
	this->pos[1] = y;
	this->pos[2] = z;
}

Vector3f operator+(const Vector3f& v1, const Vector3f& v2) {
	Vector3f v;
	v.setPos(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
	return v;
}

Vector3f operator-(const Vector3f& v1, const Vector3f& v2) {
	Vector3f v;
	v.setPos(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
	return v;
}

Vector3f Vector3f::operator-() {
	return -1 * (*this);
}

Vector3f operator*(const float s, const Vector3f& v) {
	Vector3f v1;
	v1.setPos(v[0] * s, v[1] * s, v[2] * s);
	return v1;
}

Vector3f operator/(const Vector3f& v, const float s) {
	Vector3f v1;
	v1.setPos(v[0] / s, v[1] / s, v[2] / s);
	return v1;
}

bool Vector3f::operator<(const Vector3f& other) const {
	if (this->pos[0] != other.pos[0]) return this->pos[0] < other.pos[0];
	if (this->pos[1] != other.pos[1]) return this->pos[1] < other.pos[1];
	return this->pos[2]<other.pos[2];
}


bool Vector3f::operator==(const Vector3f& other) const {
	for (int i = 0; i < 3; i++) {
		if (this->pos[i] != other.pos[i]) {
			return false;
		}
	}
	return true;
}
float dotProduct(const Vector3f& v1, const Vector3f& v2) {
	return v1[0] * v2[0] + v1[1] * v1[1] + v1[2] * v2[2];
}

Vector3f Vector3f::operator*=(const float other) {
	return other * *this;
}

float Vector3f::magnitude() const{
	return sqrt(dotProduct(*this, *this));
}

float Vector3f::distance(const Vector3f& other) {
	return sqrt(dotProduct(*this - other, *this - other));
}

Vector3f unit(const Vector3f& v) {
	return v / (v.magnitude());
}

void Vector3f::randomVector3f() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(0.f, 1.f);
	for (int i = 0; i < 3; i++) {
		float randomFloat = distribution(gen);
		this->pos[i] = randomFloat;
	}
}

Vector3f Vector3f::operator+=(const Vector3f other) {
	this->pos[0] += other.pos[0];
	this->pos[1] += other.pos[1];
	this->pos[2] += other.pos[2];
	return *this + other;
}

Vector4f::Vector4f(float x, float y, float z, float w) {
	this->pos[0] = x;
	this->pos[1] = y;
	this->pos[2] = z;
	this->pos[3] = w;
}

void Vector4f::setPos(float x, float y, float z, float w) {
	this->pos[0] = x;
	this->pos[1] = y;
	this->pos[2] = z;
	this->pos[3] = w;
}

Vector4f operator+(const Vector4f& v1, const Vector4f& v2) {
	Vector4f v;
	v.setPos(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2], v1[3] + v2[3]);
	return v;
}

Vector4f operator-(const Vector4f& v1, const Vector4f& v2) {
	Vector4f v;
	v.setPos(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2], v1[3] - v2[3]);
	return v;
}

Vector4f operator*(const float s, const Vector4f& v) {
	Vector4f v1;
	v1.setPos(v[0] * s, v[1] * s, v[2] * s, v[3] * s);
	return v1;
}

Vector4f operator/(const Vector4f& v, const float s) {
	Vector4f v1;
	v1.setPos(v[0] / s, v[1] / s, v[2] / s, v[3] / s);
	return v1;
}

float dotProduct(const Vector4f& v1, const Vector4f& v2) {
	return v1[0] * v2[0] + v1[1] * v1[1] + v1[2] * v2[2] + v1[3] * v2[3];
}