#include "Minigame/M_BasicCollision.h"
#include <iostream>
#include <cmath>

//4개의 매개변수는 (x, y) 형태
bool M_overlap(float a1[2], float a2[2], float b1[2], float b2[2]) {
	float c[4], d[4];
	for (int i = 0; i < 2; i++) {
		if (a1[i] <= a2[i]) {
			c[i] = a1[i];
			c[i + 2] = a2[i];
		}
		else if (a1[i] > a2[i]) {
			c[i] = a2[i];
			c[i + 2] = a1[i];
		}
		if (b1[i] <= b2[i]) {
			d[i] = b1[i];
			d[i + 2] = b2[i];
		}
		else if (b1[i] > b2[i]) {
			d[i] = b2[i];
			d[i + 2] = b1[i];
		}
	}
	for (int i = 0; i <= 2; i += 2) {
		for (int j = 1; j <= 3; j += 2) {
			if (((d[0] < c[i]) && (c[i] < d[2])) && ((d[1] < c[j]) && (c[j] < d[3]))) {
				return true;
			}
		}
	}
	for (int i = 0; i <= 2; i += 2) {
		for (int j = 1; j <= 3; j += 2) {
			if (((c[0] < d[i]) && (d[i] < c[2])) && ((c[1] < d[j]) && (d[j] < c[3]))) {
				return true;
			}
		}
	}
	return false;
}

bool M_overlap3d(float a1[3], float a2[3], float b1[3], float b2[3]) {
	float c[6], d[6];
	for (int i = 0; i < 3; i++) {
		if (a1[i] <= a2[i]) {
			c[i] = a1[i];
			c[i + 3] = a2[i];
		}
		else if (a1[i] > a2[i]) {
			c[i] = a2[i];
			c[i + 3] = a1[i];
		}
		if (b1[i] <= b2[i]) {
			d[i] = b1[i];
			d[i + 3] = b2[i];
		}
		else if (b1[i] > b2[i]) {
			d[i] = b2[i];
			d[i + 3] = b1[i];
		}
	}
	for (int i = 0; i <= 3; i += 3) {
		for (int j = 1; j <= 4; j += 3) {
			for (int k = 2; k <= 5; k += 3) {
				if (((d[0] <= c[i]) && (c[i] <= d[3])) && ((d[1] <= c[j]) && (c[j] <= d[4])) && ((d[2] <= c[k]) && (c[k] <= d[5]))) {
					return true;
				}
			}
		}
	}
	for (int i = 0; i <= 3; i += 3) {
		for (int j = 1; j <= 4; j += 3) {
			for (int k = 2; k <= 5; k += 3) {
				if (((c[0] <= d[i]) && (d[i] <= c[3])) && ((c[1] <= d[j]) && (d[j] <= c[4])) && ((c[2] <= d[k]) && (d[k] <= c[5]))) {
					return true;
				}
			}
		}
	}
	return false;
}


Vector3f g(0.f, -1.5f, 0.f);
//direc 1일 때가 떨어짐, 0일때가 올라가는거
bool M_BasicCollision::operator()(const M_Rect& rect, M_Cube& Cube, int axis, int direc) {
	int a, b;
	switch (axis) {
	case 0: a = 1; b = 2; break;
	case 1: a = 0; b = 2; break;
	case 2: a = 0; b = 1; break;
	}
	switch (direc) {
	case 0: 
		if (((Cube.getCenter()[axis] + Cube.getlen() / 2) <= rect.getstandard(1)) && ((Cube.getCenter()[axis] + Cube.getVelocity()[axis] + Cube.getlen() / 2) > rect.getstandard(1))) {
			float set[2][2][2];
			for (int l = 0; l < 2; l++) {
				for (int m = 0; m < 2; m++) {
					set[l][m][0] = ((l == 0) ? Cube.getbound(a, m) : rect.getpoint(m, 0));
					set[l][m][1] = ((l == 0) ? Cube.getbound(b, m) : rect.getpoint(m, 1));
				}
				if (M_overlap(set[0][0], set[0][1], set[1][0], set[1][1])) {
					Cube.setCenter(axis, (rect.getstandard(1) - Cube.getlen() / 2));
					return true;
				}
			}
		}
		break;
	case 1: 
		if (((Cube.getCenter()[axis] - Cube.getlen() / 2) >= rect.getstandard(1)) && ((Cube.getCenter()[axis] + Cube.getVelocity()[axis] +g[axis] - Cube.getlen() / 2) < rect.getstandard(1))) {
			float set[2][2][2];
			for (int l = 0; l < 2; l++) {
				for (int m = 0; m < 2; m++) {
					set[l][m][0] = ((l == 0) ? Cube.getbound(a, m) : rect.getpoint(m, 0));
					set[l][m][1] = ((l == 0) ? Cube.getbound(b, m) : rect.getpoint(m, 1));
				}
				if (M_overlap(set[0][0], set[0][1], set[1][0], set[1][1])) {
					Cube.setCenter(axis, (rect.getstandard(1) + Cube.getlen() / 2));
					return true;
				}
			}
		}
		break;
	}
	return false;
}

extern Vector3f zero;
bool M_BasicCollision::operator()(const M_Rect& rect, M_Sphere& sphere, int axis, int direc) {
	int a, b;
	switch ((int) rect.getstandard(0)) {
	case 0: a = 1; b = 2; break;
	case 1: a = 0; b = 2; break;
	case 2: a = 0; b = 1; break;
	}
	Vector3f s = sphere.getCenter();
	float pos1[2] = { s[a] - sphere.getrad(), s[b] - sphere.getrad() };
	float pos2[2] = { s[a] + sphere.getrad(), s[b] + sphere.getrad() };
	switch (direc) {
	case 0:
		if (((sphere.getCenter()[axis] + sphere.getrad()) <= rect.getstandard(1)) && ((sphere.getCenter()[axis] + sphere.getVelocity()[axis] + sphere.getrad()) > rect.getstandard(1))) {
			float set[2][2];
			for (int l = 0; l < 2; l++) {
				set[l][0] = rect.getpoint(l, 0);
				set[l][1] = rect.getpoint(l, 1);

				if (M_overlap(set[0], set[1], pos1, pos2)) {
					sphere.setCenter(axis, (rect.getstandard(1) - sphere.getrad()));
					return true;
				}
			}
		}
		break;
	case 1:
		if (((sphere.getCenter()[axis] - sphere.getrad()) >= rect.getstandard(1)) && ((sphere.getCenter()[axis] + sphere.getVelocity()[axis] - sphere.getrad()) < rect.getstandard(1))) {
			float set[2][2];
			for (int l = 0; l < 2; l++) {
				set[l][0] = rect.getpoint(l, 0);
				set[l][1] = rect.getpoint(l, 1);
				if (M_overlap(set[0], set[1], pos1, pos2)) {
					sphere.setCenter(axis, (rect.getstandard(1) + sphere.getrad()));
					return true;
				}
			}
		}
		break;
	}
	return false;
}

bool M_BasicCollision::operator()(M_Cube& Cube, M_Sphere& sphere) {
	return (Cube.getCenter() - sphere.getCenter()).magnitude() < (sphere.getrad()+1.f);
}

bool M_BasicCollision::operator()(M_Cube& Cube1, M_Cube& Cube2) {
	float pos11[3], pos12[3], pos21[3], pos22[3];
	for (int i = 0; i < 3; i++) {
		pos11[i] = Cube1.getbound(i, 0);
		pos12[i] = Cube1.getbound(i, 1);
		pos21[i] = Cube2.getbound(i, 0);
		pos22[i] = Cube2.getbound(i, 1);
	}
	return M_overlap3d(pos11, pos12, pos21, pos22);
}

bool M_BasicCollision::operator()(M_Sphere& sphere1, M_Sphere& sphere2) {
	return sphere1.getCenter().distance(sphere2.getCenter()) < (sphere1.getrad() + sphere2.getrad()) / 2;
}