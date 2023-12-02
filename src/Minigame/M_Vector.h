#pragma once
#include <cmath>
#include <tuple>
#include <random>

class Vector3f {
public:
	Vector3f(float x = 0.f, float y = 0.f, float z = 0.f);
	Vector3f(const Vector3f& c);
	void setPos(float x, float y, float z);
	friend Vector3f operator+(const Vector3f& v1, const Vector3f& v2);
	friend Vector3f operator-(const Vector3f& v1, const Vector3f& v2);
	friend Vector3f operator*(const float s, const Vector3f& v);
	friend Vector3f operator/(const Vector3f& v, const float s);
	Vector3f operator-();
	friend float dotProduct(const Vector3f& v1, const Vector3f& v2);
	float& operator[](const int i);
	float operator[](const int i) const;
	bool operator<(const Vector3f& other) const;
	bool operator==(const Vector3f& other) const;
	Vector3f operator*=(const float other);
	Vector3f operator+=(const Vector3f other);
	void randomVector3f();
	float magnitude() const;
	float distance(const Vector3f& other);
	Vector3f unit(const Vector3f& v);
private:
	float pos[3];
};

class Vector4f {
public:
	Vector4f(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f);
	void setPos(float x, float y, float z, float w);
	friend Vector4f operator+(const Vector4f& v1, const Vector4f& v2);
	friend Vector4f operator-(const Vector4f& v1, const Vector4f& v2);
	friend Vector4f operator*(const float s, const Vector4f& v);
	friend Vector4f operator/(const Vector4f& v, const float s);
	friend float dotProduct(const Vector4f& v1, const Vector4f& v2);
	float& operator[](const int i);
	float operator[](const int i) const;
private:
	float pos[4];
};