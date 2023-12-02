#include "Minigame/M_Rect.h"

M_Rect::M_Rect() {

}

M_Rect::M_Rect(const M_Rect& other) {
	for (int i = 0; i < 2; i++) {
		this->standard[i] = other.standard[i];
		for (int j = 0; j < 2; j++) {
			this->point[i][j] = other.point[i][j];
		}
	}
}

void M_Rect::setpoint(int axis, int type, float pos) {
	this->point[axis][type] = pos;
}

void M_Rect::setstandard(float axis, float pos) {
	this->standard[0] = axis;
	this->standard[1] = pos;
}

float M_Rect::getpoint(int axis, int type) const {
	return this->point[axis][type];
}

float M_Rect::getstandard(int i) const {
	return this->standard[i];
}

bool M_Rect::operator<(const M_Rect& other) const {
	if (this->standard[0] != other.standard[0]) return this->standard[0] < other.standard[0];
	else if (this->standard[1] != other.standard[1]) return this->standard[1] < other.standard[1];
	else if (this->point[0][0] != other.point[0][0]) return this->point[0][0] < other.point[0][0];
	else if (this->point[0][1] != other.point[0][1]) return this->point[0][1] < other.point[0][1];
	else if (this->point[1][0] != other.point[1][0]) return this->point[1][0] < other.point[1][0];
	else if (this->point[1][1] != other.point[1][1]) return this->point[1][1] < other.point[1][1];
	return false;
}