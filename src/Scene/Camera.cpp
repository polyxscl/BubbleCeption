#include "Camera.h"

bool Camera::pointInViewport(const Vector2<float>& vec) const {
	auto bottom_left = center - Vector3(viewport_size) / 2;
	auto top_right = center + Vector3(viewport_size) / 2;
	return bottom_left.x <= vec.x
		|| top_right.x >= vec.x
		|| bottom_left.y <= vec.y
		|| top_right.y >= vec.y;
}

void Camera::setCenter(const Vector3<float>& new_center) {
	center = new_center;
}

void Camera::setViewportSize(const Vector2<float>& new_viewport_size) {
	viewport_size = new_viewport_size;
}

Rect<float> Camera::getViewport() const {
	return Rect<float>(
		center - Vector3(viewport_size) / 2,
		center + Vector3(viewport_size) / 2
	);
}