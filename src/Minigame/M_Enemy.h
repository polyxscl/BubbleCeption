#pragma once
#include "Minigame/M_Map.h"
#include "Minigame/M_Image.h"

class M_Enemy : public M_Entity {
public:
	M_Enemy();
	M_Enemy(Vector3f pos, int type);
	virtual void draw() const;
	void move(class M_Map& A);
	bool alive = true;
	bool captured = false;

	static M_Image enemy_set[2];

private:
	std::map<M_Cuboid, Vector3f> area;
};