#include "Minigame/M_Enemy.h"

M_Image M_Enemy::enemy_set[2];

M_Enemy::M_Enemy() {


}

M_Enemy::M_Enemy(Vector3f pos, int type) {
	this->volume = 1;
	this->length = Entity_length;
	this->center = pos;
	this->type = type;
	this->face = FORWARD;
	this->volume = 1.0f;
	Vector3f v(0.f, 0.f, 0.f);
	this->velocity = v;
	this->Cubeset();
	this->moving = true;
}

void M_Enemy::draw() const {
	int j = this->type;
	int a[4];
	for (int i = 0; i < 4; i++) {
		if (this->face == i) a[i] = 1;
		else a[i] = 0;
	}
	enemy_set[a[0]+j].draw(this->getpoint(6), this->getpoint(4), this->getpoint(0), this->getpoint(2));
	enemy_set[a[1]+j].draw(this->getpoint(2), this->getpoint(0), this->getpoint(1), this->getpoint(3));
	enemy_set[a[2]+j].draw(this->getpoint(3), this->getpoint(1), this->getpoint(5), this->getpoint(7));
	enemy_set[a[3]+j].draw(this->getpoint(7), this->getpoint(5), this->getpoint(4), this->getpoint(6));
	enemy_set[j].draw(this->getpoint(4), this->getpoint(5), this->getpoint(1), this->getpoint(0));
	enemy_set[j].draw(this->getpoint(2), this->getpoint(3), this->getpoint(7), this->getpoint(6));
}

extern Vector3f g;

void M_Enemy::move(class M_Map& A) {
	if (this->block_setting[0].empty()) {
		this->block_setting = A.get_block_handling();
	}
	if (this->area.empty()) {
		this->area = A.get_enemy_area();
	}
	Vector3f zero(0.f, -0.001f, 0.f);
	for (auto& i : this->area) {
		if ((this->center[0] <= i.first.getpoint(0, 1)) && (this->center[0] > i.first.getpoint(0, 0))) {
			if ((this->center[1] <= i.first.getpoint(1, 1)) && (this->center[1] > i.first.getpoint(1, 0))) {
				if ((this->center[2] <= i.first.getpoint(2, 1)) && (this->center[2] > i.first.getpoint(2, 0))) {
					this->velocity = i.second + zero;
				}
			}
		}
	}
		
	

	this->M_Entity::move(this->block_setting);
}