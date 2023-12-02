#pragma once

#include <fstream> 
#include <iostream> 
#include <string>
#include <map>
#include <set>
#include <tuple>
#include <array>


#include <GL\freeglut.h>
#include <FreeImage.h>

#include "Minigame/M_BasicCollision.h"


#define Entity_length 2.f

enum VERTICAL_STATE {STOP, JUMP, FALL};
enum FACE {FORWARD, RIGHT, BACKWARD, LEFT};

class M_Entity : public M_Cube {
public:
	M_Entity();
	M_Entity(Vector3f c, int b);
	void setspeed(float a);
	void setface(FACE face);
	void setverticalstate(VERTICAL_STATE v);
	VERTICAL_STATE getverticalstate();
	void setmoving(bool a);
	bool getmoving();
	virtual void move(std::array<std::set<M_Rect>, 6>& A);
	virtual void handling(int axis, int direc, std::set<M_Rect>& A);
protected: 
	float speed;
	FACE face;
	VERTICAL_STATE verticalstate = FALL;
	bool moving;
	std::array<std::set<M_Rect>, 6> block_setting;
};