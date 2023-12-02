#include "Minigame/M_Entity.h"
#include <iostream>

M_Entity::M_Entity() {
	
}

M_Entity::M_Entity(Vector3f c, int b) {
	this->volume = 1;
	this->length = Entity_length;
	this->center = c;
	this->type = b;
	this->volume = 1.0f;
	Vector3f v(0.f, 0.f, 0.f);
	this->velocity = v;
	this->Cubeset();
	this->moving = false;
}

void M_Entity::setspeed(float v) {
	this->speed = v;
	for (int i=0; i < 3; i++){
		if (this->velocity[i] != 0) {
			this->velocity[i] = v;
		}
	}
}

void M_Entity::setface(FACE face) {
	this->face = face;
	Vector3f v1(0, 0, this->speed);
	Vector3f v2(this->speed, 0, 0);
	Vector3f v3(0, 0, -this->speed);
	Vector3f v4(-this->speed, 0, 0);
	switch (this->face) {
	case 0:
		this->velocity = v1;
		break;
	case 1:
		this->velocity = v2;
		break;
	case 2:
		this->velocity = v3;
		break;
	case 3:
		this->velocity = v4;
		break;
	}
		
}

void M_Entity::setverticalstate(VERTICAL_STATE v) {
	if (this->verticalstate!=JUMP && v == JUMP) {
		Vector3f v(0.f, 3.f, 0.f), a(0.f, -1.2f, 0.f);
		this->velocity += v;
		this->acceleration = a;
	}
	this->verticalstate = v;
}

VERTICAL_STATE M_Entity::getverticalstate() {
	return this->verticalstate;
}

void M_Entity::setmoving(bool a) {
	this->moving = a;
}

bool M_Entity::getmoving() {
	return this->moving;
}


M_BasicCollision detect;
//엔티티 기준 방향 (direc은 양수가 0, 음수가 1)
void M_Entity::handling(int axis, int direc, std::set<M_Rect>& A) {
	int fall = 0;
	for (auto& i : A) {
		if (detect(i, *this, axis, direc)) {
			switch (axis) {
			case 0: this->moving = false; break;
			case 2: this->moving = false; break;
			case 1: 
				switch (direc) {
					case 0: this->verticalstate = FALL; break;
					case 1: this->verticalstate = STOP; fall++; break;
 				} 
				break;
			}
		}
	}
	if ((fall == 0) && (axis == 1) && (direc == 1) && (this->verticalstate == STOP)) {
		this->verticalstate = FALL;
	}
}

extern Vector3f g;

void M_Entity::move(std::array<std::set<M_Rect>, 6>& A) {
	this->Cubeset();
	this->handling(0, 1, A[1]);
	this->handling(0, 0, A[3]);
	this->handling(1, 1, A[4]);
	this->handling(1, 0, A[5]);
	this->handling(2, 1, A[0]);
	this->handling(2, 0, A[2]);
	if (this->verticalstate == FALL) {
		if (this->velocity[1] != g[1]) {
			this->velocity[1] = g[1];
		}
	}
	if (this->velocity[1] <= 0 && this->verticalstate == JUMP) {
		Vector3f a(0.f, 0.f, 0.f);
		this->verticalstate = FALL;
		this->acceleration = a;
	}
	if (this->verticalstate == STOP) {
		this->velocity[1] = 0;
	}
	if (!this->moving) {
		this->velocity[0] = 0;
		this->velocity[2] = 0;
	}
	if ((this->moving) || (this->verticalstate != STOP)) {
		this->M_Shape3D::move();
	}
}