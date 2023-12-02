#pragma once

class M_Rect {
public:
	M_Rect();
	M_Rect(const M_Rect& other);
	void setpoint(int axis, int type, float pos);
	void setstandard(float axis, float pos);
	float getpoint(int axis, int type) const;
	float getstandard(int i) const;
	bool operator<(const M_Rect& other) const;
private:
	float point[2][2]; //four vertex coordinates (y+z, x+z, x+y)
	float standard[2]; //Which axis is the plane parallel to and pos
};
