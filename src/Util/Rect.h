#pragma once

#include "Util/Vector.h"

template <typename T>
class Rect {
public:
    Rect(Vector2<T> bottom_left, Vector2<T> top_right)
        : bottom_left(bottom_left), top_right(top_right) {}

    void set(Vector2<T> bottom_left, Vector2<T> top_right) {
        this->bottom_left = bottom_left;
        this->top_right = top_right;
    }

    Vector2<T> getBottomLeft() const {
        return bottom_left;
    }

    Vector2<T> getTopRight() const {
        return top_right;
    }

    T width() const {
        return (top_right.x - bottom_left.x);
    }

    T height() const {
        return (top_right.y - bottom_left.y);
    }

    T area() const {
        return width() * height();
    }

private:
    Vector2<T> bottom_left;  // Bottom left corner of the rectangle
    Vector2<T> top_right;    // Top right corner of the rectangle
};
