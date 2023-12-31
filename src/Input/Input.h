#pragma once

#include "Util/Vector.h"

enum class MOUSE_BUTTON { LEFT, MIDDLE, RIGHT, SCROLL_UP, SCROLL_DOWN };

struct InputKeyboard {
	const unsigned char key;
	const bool was_down;
	const bool down;
	const Vector2<int> mouse_pos;
	const bool ctrl, alt, shift;
};

struct InputKeyboardSpecial {
	const int key;
	const bool was_down;
	const bool down;
	const Vector2<int> mouse_pos;
	const bool ctrl, alt, shift;
};

struct InputMouse {
	const MOUSE_BUTTON button;
	const bool down;
	const Vector2<int> mouse_pos;
};

struct InputMouseMotion {
	const Vector2<int> mouse_pos;
};