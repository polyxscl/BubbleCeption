#pragma once
#include <utility>

#include "Minigame/M_Vector.h"
#include "Asset/MaterialAsset.h"

class M_Shape3D {
public:
	M_Shape3D(float x=0.f, float y=0.f, float z=0.f);
	virtual ~M_Shape3D() = default;
	void setCenter(float axis, float pos);
	void setCenter(const Vector3f& c);
	Vector3f getCenter() const;
	void setVelocity(const Vector3f& v);
	Vector3f getVelocity() const;
	void setAcceleration(const Vector3f& a);
	Vector3f getAcceleration() const;
	void setRandomVelocity();
	void move();
	bool operator<(const M_Shape3D& other) const;
	virtual void draw() const = 0;
protected:
	Vector3f center;
	Vector3f velocity;
	Vector3f acceleration;
};

class M_Box {
public:
	void setpoint(int i, Vector3f pos);
	void setbound(int axis, int dir, float pos);
	Vector3f getpoint(int i) const;
	float getbound(int axis, int dir) const;
protected:
	float bound[3][2];
	Vector3f point[8];
	
};

class M_Cube : public M_Box, public M_Shape3D {
public:
	void settype(int i);
	int gettype() const;
	void Cubeset();
	float getlen() const;
	void setlen(float a);
	void change_volume(float a);
	
protected:
	float volume;
	float length;
	int type;
};


class M_Sphere : public M_Shape3D {
public:
	void setrad(float a);
	float getrad() const;

protected:
	float radius;
	int slice, stack;
};