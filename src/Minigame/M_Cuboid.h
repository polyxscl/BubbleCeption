#pragma once

class M_Cuboid {
public:
	M_Cuboid();
	M_Cuboid(const M_Cuboid& other);
	void setpoint(int axis, int type, float pos);
	float getpoint(int axis, int type) const;
	bool operator<(const M_Cuboid& other) const;
private:
	float point[3][2]; //four vertex x, y, z (0�� ���� ��, 1�� ū ��)
};