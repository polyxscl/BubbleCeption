#pragma once

#include "Util/Vector.h"
#include "Util/Rect.h"

class Camera {
public:

	bool pointInViewport(const Vector2<float>& vec) const;
	void setCenter(const Vector3<float>& new_center);
	void setViewportSize(const Vector2<float>& new_viewport_size);
	Rect<float> getViewport() const;

private:
	Vector2<float> viewport_size;
	Vector3<float> center;

};