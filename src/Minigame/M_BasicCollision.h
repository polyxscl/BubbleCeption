#pragma once
#include "Minigame/M_Block.h"
#include "Minigame/M_Rect.h"



class M_BasicCollision {
public:
	bool operator()(const M_Rect& rect, M_Cube& Cube, int axis, int direc);
	bool operator()(const M_Rect& rect, M_Sphere& sphere, int axis, int direc);
	bool operator()(M_Cube& Cube, M_Sphere& sphere);
	bool operator()(M_Cube& Cube1, M_Cube& Cube2);
	bool operator()(M_Sphere& sphere1, M_Sphere& spehre2);
};