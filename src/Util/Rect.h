#pragma once

#include "Util/Vector.h"

template <typename T>
class Rect {
public:
    Rect()
        : bottom_left(Vector2<T>()), top_right(Vector2<T>()) {}
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

    Vector2<T> getBottomRight() const {
        return Vector2<T>(top_right.x, bottom_left.y);
    }

    Vector2<T> getTopLeft() const {
        return Vector2<T>(bottom_left.x, top_right.y);
    }

    T width() const {
        return (top_right.x - bottom_left.x);
    }

    T height() const {
        return (top_right.y - bottom_left.y);
    }

    T top() const {
        return top_right.y;
    }

    T bottom() const {
        return bottom_left.y;
    }

    T right() const {
        return top_right.x;
    }

    T left() const {
        return bottom_left.x;
    }

    Vector2<T> center() const {
        return bottom_left + top_right;
    }

    T area() const {
        return width() * height();
    }

    bool intersects(const Rect& other) const {
        // Check if one rectangle is to the left of the other
        if (right() < other.left() || other.right() < left())
            return false;

        // Check if one rectangle is above the other
        if (top() < other.bottom() || other.top() < bottom())
            return false;

        // If neither is true, rectangles intersect
        return true;
    }

    bool contains(Vector2<T> point) const {
        return bottom_left.x <= point.x
            || top_right.x >= point.x
            || bottom_left.y <= point.y
            || top_right.y >= point.y;
    }

private:
    Vector2<T> bottom_left;  // Bottom left corner of the rectangle
    Vector2<T> top_right;    // Top right corner of the rectangle
};
