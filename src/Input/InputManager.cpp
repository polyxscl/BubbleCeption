#include "InputManager.h"

#include <GL/freeglut.h>
#include <algorithm>

Logger InputManager::logger("InputManager");

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() {
	if (instance) {
		logger << "Duplicate instances of InputManager is not allowed" << logger.error;
		throw std::runtime_error("DuplicateInputManager");
	}

	logger << "Creating InputManager class..." << logger.info;

	// Singleton
	instance = this;

	// Initialize key press table
	std::fill(key_press_table, key_press_table + 256, false);
}

void InputManager::init() {
	checkInit();

	// Attach functions to GLUT.
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);
	
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passiveMotion);
}

void InputManager::__keyboardCallback(unsigned char key, int x, int y, bool down) {
	int mod = glutGetModifiers();
	bool ctrl = (mod & GLUT_ACTIVE_CTRL) != 0;
	bool shift = (mod & GLUT_ACTIVE_SHIFT) != 0;
	bool alt = (mod & GLUT_ACTIVE_ALT) != 0;

	auto input = InputKeyboardSpecial{
		key,
		down,
		Vector2<int>(x, y),
		ctrl, shift, alt,
	};

	for (auto& [_, callback] : instance->special_key_press_callbacks) {
		callback(*instance, input);
	}

	instance->ctrl = ctrl;
	instance->shift = shift;
	instance->alt = alt;

	instance->special_key_press_table.insert(key);
}

void InputManager::keyboardDown(unsigned char key, int x, int y) {
	InputManager::checkInit();

	InputManager::__keyboardCallback(key, x, y, true);
}

void InputManager::keyboardUp(unsigned char key, int x, int y) {
	InputManager::checkInit();

	InputManager::__keyboardCallback(key, x, y, false);
}

void InputManager::__specialCallback(int key, int x, int y, bool down) {
	int mod = glutGetModifiers();
	bool ctrl = (mod & GLUT_ACTIVE_CTRL) != 0;
	bool shift = (mod & GLUT_ACTIVE_SHIFT) != 0;
	bool alt = (mod & GLUT_ACTIVE_ALT) != 0;

	auto input = InputKeyboardSpecial{
		key,
		down,
		Vector2<int>(x, y),
		ctrl, shift, alt,
	};

	for (auto& [_, callback] : instance->special_key_press_callbacks) {
		callback(*instance, input);
	}

	instance->ctrl = ctrl;
	instance->shift = shift;
	instance->alt = alt;

	instance->special_key_press_table.insert(key);
}

void InputManager::specialDown(int key, int x, int y) {
	InputManager::checkInit();

	InputManager::__specialCallback(key, x, y, true);
}

void InputManager::specialUp(int key, int x, int y) {
	InputManager::checkInit();

	InputManager::__specialCallback(key, x, y, false);
}

void InputManager::mouse(int button, int state, int x, int y) {
	InputManager::checkInit();

	MOUSE_BUTTON mouse_button;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		mouse_button = MOUSE_BUTTON::LEFT;
		break;
	case GLUT_MIDDLE_BUTTON:
		mouse_button = MOUSE_BUTTON::MIDDLE;
		break;
	case GLUT_RIGHT_BUTTON:
		mouse_button = MOUSE_BUTTON::RIGHT;
		break;
	default:
		throw std::runtime_error("InvalidMouseButton");
	}

	auto input = InputMouse{
		mouse_button,
		state == GLUT_DOWN,
	};

	for (auto& [_, callback] : instance->mouse_press_callbacks) {
		callback(*instance, input);
	}

	instance->mouse_pos = Vector2<int>(x, y);

	switch (button) {
	case GLUT_LEFT_BUTTON:
		instance->mouse_left = (state == GLUT_DOWN);
		break;
	case GLUT_MIDDLE_BUTTON:
		instance->mouse_middle = (state == GLUT_DOWN);
		break;
	case GLUT_RIGHT_BUTTON:
		instance->mouse_right = (state == GLUT_DOWN);
		break;
	default:
		throw std::runtime_error("InvalidMouseButton");
	}
}

void InputManager::motion(int x, int y) {
	InputManager::checkInit();

	auto input = InputMouseMotion{
		Vector2<int>(x, y)
	};

	for (auto& [_, callback] : instance->mouse_motion_callbacks) {
		callback(*instance, input);
	}

	instance->mouse_pos.x = x;
	instance->mouse_pos.y = y;
}

void InputManager::passiveMotion(int x, int y) {
	InputManager::motion(x, y);
}

bool InputManager::isKeyPressed(unsigned char key) const {
	return key_press_table[key];
}

bool InputManager::isSpecialKeyPressed(int key) const {
	return special_key_press_table.find(key) != special_key_press_table.end();
}

bool InputManager::isCtrlPressed() const {
	return ctrl;
}

bool InputManager::isAltPressed() const {
	return alt;
}

bool InputManager::isShiftPressed() const {
	return shift;
}

void InputManager::attachKeyPressCallback(std::string id, keyPressFuncType func) {
	key_press_callbacks.emplace(id, func);
}

void InputManager::attachSpecialKeyPressCallback(std::string id, specialKeyPressFuncType func) {
	special_key_press_callbacks.emplace(id, func);
};

void InputManager::attachMousePressCallback(std::string id, mousePressFuncType func) {
	mouse_press_callbacks.emplace(id, func);
}

void InputManager::attachMouseMotionCallback(std::string id, mouseMotionFuncType func) {
	mouse_motion_callbacks.emplace(id, func);
}

void InputManager::checkInit() {
	if (!instance) {
		logger << "InputManager instance not initialized" << logger.error;
		throw std::runtime_error("UninitializedInputManager");
	}
}