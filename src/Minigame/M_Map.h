#pragma once

#include <fstream> 
#include <iostream> 
#include <string>
#include <map>
#include <set>
#include <tuple>
#include <array>
#include <utility>

#include "Minigame/M_Entity.h"
#include "MInigame/M_Cuboid.h"

#include <nlohmann/json.hpp>
#include <GL\freeglut.h>
#include <FreeImage.h>


std::tuple<Vector3f, Vector3f> pos_set(Vector3f start, Vector3f end);

class M_Map {
public:
	M_Map(std::string s);
	void generate(std::string file);
	void fill(Vector3f start, Vector3f end, int type);
	void erase(Vector3f start, Vector3f end);
	void replace(Vector3f start, Vector3f end, int type1, int type2);
	virtual void draw() const;
	std::set<M_Block>& get_block_setting();
	std::array<std::set<M_Rect>, 6>& get_block_handling();
	Vector3f get_player_init() const;
	std::map<Vector3f, int> get_enemy_init();
	std::map<M_Cuboid, Vector3f>& get_bubble_area();
	std::map<M_Cuboid, Vector3f>& get_enemy_area();
	friend class M_Entity;
private:
	std::string name;
	std::map<Vector3f, int> info;
	std::set<M_Block> block_setting;
	std::array<std::set<M_Rect>, 6> handling;
	std::map<M_Cuboid, Vector3f> bubble_area;
	std::map<M_Cuboid, Vector3f> enemy_area;
	Vector3f player_init;
	std::map<Vector3f, int> enemy_init;
};