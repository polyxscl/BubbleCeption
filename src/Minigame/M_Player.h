#pragma once
#include "Minigame/M_Bubble.h"
#include "Minigame/M_Image.h"

class M_Player: public M_Entity {
public:
	M_Player();
	M_Player(class M_Map& A, int b);
	M_Bubble shootBubble();
	virtual void draw() const;
	void move(class M_Map& A);
	
	static M_Image player_set[4];

private:
	std::map<M_Cuboid, Vector3f> enemy_area;
	std::map<M_Cuboid, Vector3f> bubble_area;
};