#pragma once
#include "Minigame/M_Map.h"
#include "Minigame/M_Enemy.h"
#include "Asset/MaterialAsset.h"

enum STATE { BLOWING, BLOWN, POPPED };

class M_Bubble : public M_Sphere {
public:
	M_Bubble();
	M_Bubble(const M_Bubble& b);
	M_Bubble(float r, int sl, int st);
	void handling(int axis, int direc, class std::set<M_Rect>& A);
	void set_block(std::array<std::set<M_Rect>, 6>& block_setting);
	void set_area(std::map<M_Cuboid, Vector3f>& area);
	void set_face(FACE face);
	void set_state(STATE state);
	void set_enemy(M_Enemy* enemy);
	STATE get_state() const;
	void pop();
	void move();
	void draw() const;
	bool operator==(const M_Bubble& b) const;
	std::shared_ptr<MaterialAsset> mtl;
private:
	FACE face;
	STATE state = BLOWING;
	bool moving;
	std::array<std::set<M_Rect>, 6> block_setting;
	std::map<M_Cuboid, Vector3f> area;
	M_Enemy* enemy = nullptr;
};