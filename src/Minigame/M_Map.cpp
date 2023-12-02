#include <string>
#include <iostream>
#include <fstream>
#include <iostream>

#include "Minigame/M_Map.h"

M_Map::M_Map(std::string s) {
	this->name = s;
}

void M_Map::generate(std::string file) {
	nlohmann::json M_MapJson;
	std::ifstream File(file);
	if (File.is_open()) {
		std::string fileContent((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
		try {
			M_MapJson = nlohmann::json::parse(fileContent);
		}
		catch (const nlohmann::json::parse_error& e) {
			std::cerr << "JSON 파싱 오류: " << e.what() << std::endl;
		}
		File.close();
	}
	else {
		std::cerr << "파일을 열 수 없습니다." << std::endl;
	}
	std::string block[2] = { "basic_block", "additional_block" };
	for (auto& i : block) {
		if (M_MapJson.find(i) != M_MapJson.end()) {
			const nlohmann::json& blockInfo = M_MapJson[i];
			if (blockInfo.is_object()) {
				if (blockInfo.find("fill") != blockInfo.end() && blockInfo["fill"].is_array()) {
					for (const auto& fillInfo : blockInfo["fill"]) {
						if (fillInfo.is_array() && fillInfo.size() == 3) {
							Vector3f start(fillInfo[0][0], fillInfo[0][1], fillInfo[0][2]);
							Vector3f end(fillInfo[1][0], fillInfo[1][1], fillInfo[1][2]);
							int type = fillInfo[2];
							fill(start, end, type);
						}
					}
				}

				if (blockInfo.find("erase") != blockInfo.end() && blockInfo["erase"].is_array()) {
					for (const auto& eraseInfo : blockInfo["erase"]) {
						if (eraseInfo.is_array() && (eraseInfo.size() == 2 || eraseInfo.size() == 3)) {
							Vector3f start(eraseInfo[0][0], eraseInfo[0][1], eraseInfo[0][2]);
							Vector3f end(eraseInfo[1][0], eraseInfo[1][1], eraseInfo[1][2]);
							erase(start, end);
						}
					}
				}
				if (blockInfo.find("replace") != blockInfo.end() && blockInfo["replace"].is_array()) {
					for (const auto& replaceInfo : blockInfo["replace"]) {
						if (replaceInfo.is_array() && replaceInfo.size() == 4) {
							Vector3f start(replaceInfo[0][0], replaceInfo[0][1], replaceInfo[0][2]);
							Vector3f end(replaceInfo[1][0], replaceInfo[1][1], replaceInfo[1][2]);
							int type1 = replaceInfo[2];
							int type2 = replaceInfo[3];
							replace(start, end, type1, type2);
						}
					}
				}
			}
		}
	}

	if (M_MapJson.find("entity") != M_MapJson.end()) {
	const nlohmann::json& entityInfo = M_MapJson["entity"];
		if (entityInfo.find("player") != entityInfo.end() && entityInfo["player"].size() == 3) {
			Vector3f pos(entityInfo["player"][0], entityInfo["player"][1], entityInfo["player"][2]);
			this->player_init = pos;
		}
		if (entityInfo.find("enemy") != entityInfo.end()) {
			const nlohmann::json& enemyInfo = entityInfo["enemy"];
			for (const auto& enemyinfo : enemyInfo) {
				if (enemyinfo.is_array() && enemyinfo.size() == 2) {
					Vector3f pos(enemyinfo[0][0], enemyinfo[0][1], enemyinfo[0][2]);
					int type = enemyinfo[1];
					this->enemy_init[pos] = type;
				}
			}
		}	
	}

	//버블 영역 만들기
	if (M_MapJson.find("area") != M_MapJson.end()) {
		const nlohmann::json& areaInfo = M_MapJson["area"];
		if (areaInfo.find("bubble") != areaInfo.end() && areaInfo["bubble"].is_array()) {
			for (const auto& i : areaInfo["bubble"]) {
				if (i.is_array() && i.size() == 3) {
					Vector3f start(i[0][0], i[0][1], i[0][2]);
					Vector3f end(i[1][0], i[1][1], i[1][2]);
					Vector3f v(i[2][0], i[2][1], i[2][2]);
					M_Cuboid area;
					for (int j = 0; j < 3; j++) {
						if (start[j] <= end[j]) {
							area.setpoint(j, 0, start[j] - Block_length / 2);
							area.setpoint(j, 1, end[j] + Block_length / 2);
						}
						else {
							area.setpoint(j, 1, start[j] + Block_length / 2);
							area.setpoint(j, 0, end[j] - Block_length / 2);
						}
					}
					this->bubble_area[area] = v;
				}
			}
		}
		if (areaInfo.find("enemy") != areaInfo.end() && areaInfo["enemy"].is_array()) {
			for (const auto& i : areaInfo["enemy"]) {
				if (i.is_array() && i.size() == 3) {
					Vector3f start(i[0][0], i[0][1], i[0][2]);
					Vector3f end(i[1][0], i[1][1], i[1][2]);
					Vector3f v(i[2][0], i[2][1], i[2][2]);
					M_Cuboid area;
					for (int j = 0; j < 3; j++) {
						if (start[j] <= end[j]) {
							area.setpoint(j, 0, start[j] - Block_length / 2);
							area.setpoint(j, 1, end[j] + Block_length / 2);
						}
						else {
							area.setpoint(j, 1, start[j] + Block_length / 2);
							area.setpoint(j, 0, end[j] - Block_length / 2);
						}
					}
					this->enemy_area[area] = v;
				}
			}
		}
	}


	Vector3f  v0(0.f, 0.f, 1.f), v1(1.f, 0.f, 0.f), v2(0.f, 0.f, -1.f), v3(-1.f, 0.f, 0.f), v4(0.f, 1.f, 0.f), v5(0.f, -1.f, 0.f);
	Vector3f h1(Block_length, 0.f, 0.f), h2(0.f, Block_length, 0.f), h3(0.f, 0.f, Block_length);
	Vector3f adj1[6] = { v0, v1, v2, v3, v4, v5 };
	Vector3f adj2[6][3] = { {h3, h1, h2}, {h1, h3, h2}, {-h3, h1, h2}, {-h1, h3, h2}, {h2, h1, h3}, {-h2, h1, h3} };

	std::map<Vector3f, std::array<bool, 6>> handling_set;
	//겹치는 부분 투명화 처리 (최적화 필수)
	for (const auto& i : this->info) {
		bool show[6], handling[6];
		for (int j = 0; j < 6; j++) {
			Vector3f pos(i.first + adj1[j]);
			auto it = this->info.find(pos);
			if ((it != this->info.end()) && (it->second != 0)) {
				show[j] = false;
				handling[j] = false;
			}
			else if ((it != this->info.end()) && (it->second == 0)) {
				show[j] = true;
				handling[j] = false;
			}
			else if ((it == this->info.end()) && (i.second == 0)) {
				show[j] = true;
				if (j == 5) handling[j] = true; 
				else handling[j] = true; 
			}
			else {
				show[j] = true;
				if (j == 5)  handling[j] = false; 
				else  handling[j] = true; 
			}
		}
		for (int h = 0; h < 6; h++) {
			handling_set[i.first][h] = handling[h];
		}
		M_Block A(Block_length * i.first, i.second);
		A.setshow(show);
		this->block_setting.insert(A);
	}

	//충돌용 면 만들기 (최적화 필수)
	
	std::array<std::set<Vector3f>, 6> mini_handling_set;
	for (int k = 0; k < 6; k++) {
		for (auto it1 = handling_set.begin(); it1 != handling_set.end(); it1++) {
			if (it1->second[k] == true) {
				mini_handling_set[k].insert(it1->first);
			}
		}
	}

	int c = 0;
	for (int j = 0; j < 6; j++) {
		std::set<std::tuple<Vector3f, Vector3f>> ErasePair;
		for (auto it1 = mini_handling_set[j].begin(); it1 != mini_handling_set[j].end(); it1++) {
			Vector3f pos(*it1);
			pos += adj2[j][1];
			auto it2 = mini_handling_set[j].find(pos);
			while ((it2 != mini_handling_set[j].end())) {
				mini_handling_set[j].erase(pos);
				pos += adj2[j][1];
				it2 = mini_handling_set[j].find(pos);
			}
			ErasePair.insert(pos_set(*it1, pos - adj2[j][1]));	
		}
		
		std::set<std::tuple<Vector3f, Vector3f>> init;
		for (auto it3 = ErasePair.begin(); it3 != ErasePair.end(); it3++) {
			int t; if (j < 4) t = 1; else t = 2;
			auto& [first, second] = *it3;
			Vector3f a(first), b(second);
			a += adj2[j][2]; b += adj2[j][2];
			std::tuple<Vector3f, Vector3f> c;
			c=std::make_tuple(a, b);
			auto it4 = ErasePair.find(c);

			int once = 0;
			while ((it4 != ErasePair.end())) {
				if (once == 0) {
					if (first[t] == second[t]) {
						init.insert(*it3); once++;
					}
				}
				ErasePair.erase(c);
				a += adj2[j][2]; b += adj2[j][2];
				c = std::make_tuple(a, b);
				it4 = ErasePair.find(c);
			}
			ErasePair.insert(std::make_tuple(first, b-adj2[j][2]));
		}
		for (auto& i : init) {
			ErasePair.erase(i);
		}

		for (auto it5 = ErasePair.begin(); it5 != ErasePair.end(); it5++) {
			M_Rect side; //작은 좌표를 type 0, 큰 좌표를 type 1이라 지정
			auto& [first, second] = *it5;
			switch (j) {
			case 0:
				side.setstandard(2, first[2] + Block_length / 2);
				side.setpoint(0, 0, first[0] - Block_length / 2); //한 점의 좌표가 한 쌍이 되게 저장
				side.setpoint(0, 1, first[1] - Block_length / 2);
				side.setpoint(1, 0, second[0] + Block_length / 2);
				side.setpoint(1, 1, second[1] + Block_length / 2);
				break;
			case 1:
				side.setstandard(0, first[0] + Block_length / 2);
				side.setpoint(0, 0, first[1] - Block_length / 2);
				side.setpoint(0, 1, first[2] - Block_length / 2);
				side.setpoint(1, 0, second[1] + Block_length / 2);
				side.setpoint(1, 1, second[2] + Block_length / 2);
				break;
			case 2:
				side.setstandard(2, first[2] - Block_length / 2);
				side.setpoint(0, 0, first[0] - Block_length / 2);
				side.setpoint(0, 1, first[1] - Block_length / 2);
				side.setpoint(1, 0, second[0] + Block_length / 2);
				side.setpoint(1, 1, second[1] + Block_length / 2);
				break;
			case 3:
				side.setstandard(0, first[0] - Block_length / 2);
				side.setpoint(0, 0, first[1] - Block_length / 2);
				side.setpoint(0, 1, first[2] - Block_length / 2);
				side.setpoint(1, 0, second[1] + Block_length / 2);
				side.setpoint(1, 1, second[2] + Block_length / 2);
				break;
			case 4:
				side.setstandard(1, first[1] + Block_length / 2);
				side.setpoint(0, 0, first[0] - Block_length / 2);
				side.setpoint(0, 1, first[2] - Block_length / 2);
				side.setpoint(1, 0, second[0] + Block_length / 2);
				side.setpoint(1, 1, second[2] + Block_length / 2);
				break;
			case 5:
				side.setstandard(1, first[1] - Block_length / 2);
				side.setpoint(0, 0, first[0] - Block_length / 2);
				side.setpoint(0, 1, first[2] - Block_length / 2);
				side.setpoint(1, 0, second[0] + Block_length / 2);
				side.setpoint(1, 1, second[2] + Block_length / 2);
				break;
			}
			this->handling[j].insert(side);
			//std::cout << "number " << c << ": " << side.getstandard(0) << " " << side.getstandard(1) << std::endl;
			//std::cout << side.getpoint(0, 0) << " " << side.getpoint(0, 1) << " " << side.getpoint(1, 0) << " " << side.getpoint(1, 1) << std::endl<<std::endl;
			//c++;
		}
		ErasePair.clear();
	}
}

std::tuple<Vector3f, Vector3f> pos_set(Vector3f start, Vector3f end) {
	Vector3f start_pos, end_pos;
	for (int i = 0; i < 3; i++) {
		if (start[i] <= end[i]) {
			start_pos[i] = start[i];
			end_pos[i] = end[i];
		}
		else {
			start_pos[i] = end[i];
			end_pos[i] = start[i];
		}
	}
	return std::make_tuple(start_pos, end_pos);
}

void M_Map::fill(Vector3f start, Vector3f end, int type) {
	auto [a, b] = pos_set(start, end);
	for (float i = a[0]; i <= b[0]; i++) {
		for (float j = a[1]; j <= b[1]; j++) {
			for (float k = a[2]; k <= b[2]; k++) {
				Vector3f make(i, j, k);
				this->info.insert(std::make_pair(make, type));
			}
		}
	}
}

void M_Map::erase(Vector3f start, Vector3f end) {
	auto [a, b] = pos_set(start, end);
	for (float i = a[0]; i <= b[0]; i++) {
		for (float j = a[1]; j <= b[1]; j++) {
			for (float k = a[2]; k <= b[2]; k++) {
				Vector3f make(i, j, k);
				this->info.erase(make);
			}
		}
	}
}

void M_Map::replace(Vector3f start, Vector3f end, int type1, int type2) {
	auto [a, b] = pos_set(start, end);
	for (float i = a[0]; i <= b[0]; i++) {
		for (float j = a[1]; j <= b[1]; j++) {
			for (float k = a[2]; k <= b[2]; k++) {
				Vector3f make(i, j, k);
				if (this->info.find(make) != this->info.end() && this->info[make] == type1) {
					this->info[make] = type2;
				}
			}
		}
	}
}

std::set<M_Block>& M_Map::get_block_setting() {
	return this->block_setting;
}

std::array<std::set<M_Rect>, 6>& M_Map::get_block_handling(){
	return this->handling;
}

Vector3f M_Map::get_player_init() const{
	return this->player_init;
}

std::map<Vector3f, int> M_Map::get_enemy_init() {
	return this->enemy_init;
}

std::map<M_Cuboid, Vector3f>& M_Map::get_bubble_area() {
	return this->bubble_area;
}

std::map<M_Cuboid, Vector3f>& M_Map::get_enemy_area() {
	return this->enemy_area;
}

void M_Map::draw() const {
	for (auto& i : this->block_setting) {
		i.draw();
	}
}