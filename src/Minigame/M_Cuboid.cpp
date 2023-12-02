#include "Minigame/M_Cuboid.h"

M_Cuboid::M_Cuboid() {

}

M_Cuboid::M_Cuboid(const M_Cuboid& other) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			this->point[i][j] = other.point[i][j];
		}
	}
}

void M_Cuboid::setpoint(int axis, int type, float pos) {
	this->point[axis][type] = pos;
}

float M_Cuboid::getpoint(int axis, int type) const {
	return this->point[axis][type];
}

bool M_Cuboid::operator<(const M_Cuboid& other) const {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			if (this->point[i][j] != other.point[i][j]) {
				return this->point[i][j] < other.point[i][j];
			}
		}
	}
	return false;
}