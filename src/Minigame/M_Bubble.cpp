#include <random>
#include "Minigame/M_Bubble.h"

M_Bubble::M_Bubble() {

}

M_Bubble::M_Bubble(float r, int sl, int st) {
	this->radius = r;
	this->slice = sl;
	this->stack = st;
}

M_Bubble::M_Bubble(const M_Bubble& b) {
	this->radius = b.radius;
	this->slice = b.slice;
	this->stack = b.stack;
	this->center = b.center;
	this->velocity = b.velocity;
	this->acceleration = b.acceleration;
	this->block_setting = b.block_setting;
	this->face = b.face;
	this->area = b.area;
}

void M_Bubble::draw() const {
	float emission[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float diffuse[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	float specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float ambient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float shininess[1] = { 10.f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glPushMatrix();
	glTranslatef(this->center[0], this->center[1], this->center[2]);
	glutSolidSphere(this->radius, this->slice, this->stack);
	glPopMatrix();
	glEnd();
}

Vector3f up(0.f, 1.5f, 0.f);

extern bool M_overlap(float a1[2], float a2[2], float b1[2], float b2[2]);

M_BasicCollision detectM_Bubble;
//엔티티 기준 방향 (물체 기준 direc은 양수가 0, 음수가 1)
void M_Bubble::handling(int axis, int direc, class std::set<M_Rect>& A) {
	for (auto& i : A) {
		if (detectM_Bubble(i, *this, axis, direc)) {
			switch (axis) {
			case 0: this->state = BLOWN; this->radius = 1.5f; break;
			case 2: this->state = BLOWN; this->radius = 1.5f; break;
			case 1: this->state = BLOWN; break;
			}
		}
	}
}

void M_Bubble::set_block(std::array<std::set<M_Rect>, 6>& block) {
	this->block_setting = block;
}

void M_Bubble::set_area(std::map<M_Cuboid, Vector3f>& area) {
	this->area = area;
}

void M_Bubble::set_face(FACE f) {
	this->face = f;
}

STATE M_Bubble::get_state() const {
	return this->state;
}

bool M_Bubble::operator==(const M_Bubble& b) const {
	return this->center == b.center;
}


void M_Bubble::move() {
	this->handling(0, 1, this->block_setting[1]);
	this->handling(0, 0, this->block_setting[3]);
	this->handling(1, 1, this->block_setting[4]);
	this->handling(1, 0, this->block_setting[5]);
	this->handling(2, 1, this->block_setting[0]);
	this->handling(2, 0, this->block_setting[2]);

	if (enemy) {
		enemy->setCenter(getCenter());
	}

	if (this->state == BLOWING) {
		switch (this->face) {
		case FORWARD: 
			if (this->velocity[2] <= 0) {
				this->state = BLOWN;
				//this->velocity = up;
			}
			else {
				this->radius += 0.1f;
			}
			break;
		case BACKWARD:
			if (this->velocity[2] >= 0) {
				this->state = BLOWN;
				//this->velocity = up;
			}
			else {
				this->radius += 0.1f;
			}
			break;
		case RIGHT:
			if (this->velocity[0] <= 0) {
				this->state = BLOWN;
			//	this->velocity = up;
			}
			else {
				this->radius += 0.1f;
			}
			break;
		case LEFT:
			if (this->velocity[0] >= 0) {
				this->state = BLOWN;
			//	this->velocity = up;
			}
			else {
				this->radius += 0.1f;
			}
			break;
		}
	}

	Vector3f zero(0.f, -0.001f, 0.f);
	if (this->state==BLOWN) {
		for (auto& i : this->area) {
			if ((this->center[0] <= i.first.getpoint(0, 1)) && (this->center[0] > i.first.getpoint(0, 0))) {
				if ((this->center[1] <= i.first.getpoint(1, 1)) && (this->center[1] > i.first.getpoint(1, 0))) {
					if ((this->center[2] <= i.first.getpoint(2, 1)) && (this->center[2] > i.first.getpoint(2, 0))) {
						this->velocity = i.second+zero;
					}
				}
			}
			
		}
	}
	
	this->M_Shape3D::move();
}

void M_Bubble::set_state(STATE state) {
	this->state = state;
}

void M_Bubble::set_enemy(M_Enemy* enemy) {
	this->enemy = enemy;
}

void M_Bubble::pop() {
	if (enemy) {
		this->enemy->alive = false;
	}
}