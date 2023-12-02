#pragma once
#include "Minigame/M_Shape3D.h"
#include "Minigame/M_Image.h"

#define Block_length 1.f

class M_Block : public M_Cube {
public:
	M_Block();
	M_Block(Vector3f a, int b);
	void draw() const;
	void setshow(bool* info);
	
	static M_Image block_set[4];

private:
	bool show[6];
};