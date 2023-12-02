#include <random>
#include "Minigame/M_Player.h"

M_Image M_Player::player_set[4];

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dist(0.f, 1.f);

M_Player::M_Player() {


}

M_Player::M_Player(class M_Map& A, int b) {
	this->volume = 1;
	this->length = Entity_length;
	this->center = A.get_player_init();
	this->type = b;
	this->face = FORWARD;
	this->volume = 1.0f;
	Vector3f v(0.f, 0.f, 0.f);
	this->velocity = v;
	this->Cubeset();
	this->moving = false;
}

M_Bubble M_Player::shootBubble() {
	auto bubble = M_Bubble(0.8f, 20, 20);
	bubble.setCenter(this->center);
	auto mtl = std::shared_ptr<MaterialAsset>();
	mtl->set_ambient(dist(gen), dist(gen), dist(gen), 1.0f);
	mtl->set_diffuse(dist(gen), dist(gen), dist(gen), 1.0f);
	mtl->set_emission(dist(gen), dist(gen), dist(gen), 1.0f);
	mtl->set_specular(dist(gen), dist(gen), dist(gen), 1.0f);
	mtl->set_shininess(10.f);
	bubble.set_block(this->block_setting);
	bubble.set_area(this->bubble_area);
	Vector3f r(2.f, 0.f, 0.f), l(-2.f, 0.f, 0.f), f(0.f, 0.f, 2.f), b(0.f, 0.f, -2.f);
	Vector3f ra(-0.3f, 0.f, 0.f), la(0.3f, 0.f, 0.f), fa(0.f, 0.f, -0.3f), ba(0.f, 0.f, 0.3f);
	switch (this->face) {
	case 0:
		bubble.setVelocity(f);
		bubble.setAcceleration(fa);
		bubble.set_face(FORWARD);
		break;
	case 1:
		bubble.setVelocity(r);
		bubble.setAcceleration(ra);
		bubble.set_face(RIGHT);
		break;
	case 2:
		bubble.setVelocity(b);
		bubble.setAcceleration(ba);
		bubble.set_face(BACKWARD);
		break;
	case 3:
		bubble.setVelocity(l);
		bubble.setAcceleration(la);
		bubble.set_face(LEFT);
		break;
	}
	return bubble;
}

void M_Player::draw() const {
	int j = this->type;
	int a[4];
	for (int i = 0; i < 4; i++) {
		if (this->face == i) a[i] = 1;
		else a[i] = 0;
	}
	player_set[a[0]+j].draw(this->getpoint(6), this->getpoint(4), this->getpoint(0), this->getpoint(2));
	player_set[a[1]+j].draw(this->getpoint(2), this->getpoint(0), this->getpoint(1), this->getpoint(3));
	player_set[a[2]+j].draw(this->getpoint(3), this->getpoint(1), this->getpoint(5), this->getpoint(7));
	player_set[a[3]+j].draw(this->getpoint(7), this->getpoint(5), this->getpoint(4), this->getpoint(6));
	player_set[j].draw(this->getpoint(4), this->getpoint(5), this->getpoint(1), this->getpoint(0));
	player_set[j].draw(this->getpoint(2), this->getpoint(3), this->getpoint(7), this->getpoint(6));
}

extern Vector3f g;

void M_Player::move(class M_Map& A) {
	if (this->block_setting[0].empty()) {
		this->block_setting = A.get_block_handling();
	}
	if (this->bubble_area.empty()) {
		this->bubble_area = A.get_bubble_area();
	}
	if (this->enemy_area.empty()) {
		this->enemy_area = A.get_enemy_area();
	}
	this->M_Entity::move(this->block_setting);
}


