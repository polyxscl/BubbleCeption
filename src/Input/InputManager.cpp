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

	logger << "Initializing InputManager..." << logger.info;

	// Attach functions to GLUT.
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);
	
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passiveMotion);
}

void InputManager::__keyboardCallback(unsigned char key, int x, int y, bool down, bool was_down) {
	int mod = glutGetModifiers();
	bool ctrl = (mod & GLUT_ACTIVE_CTRL) != 0;
	bool shift = (mod & GLUT_ACTIVE_SHIFT) != 0;
	bool alt = (mod & GLUT_ACTIVE_ALT) != 0;

	auto input = InputKeyboard{
		key,
		was_down,
		down,
		Vector2<int>(x, y),
		ctrl, shift, alt,
	};

	for (auto it = instance->key_press_callbacks.begin(); it != instance->key_press_callbacks.end();) {
		auto& [_, callback] = *it;
		if (!callback.valid) {
			it = instance->key_press_callbacks.erase(it);
		}
		else {
			callback.func(*instance, input);
			++it;
		}
	}

	instance->ctrl = ctrl;
	instance->shift = shift;
	instance->alt = alt;
}

void InputManager::keyboardDown(unsigned char key, int x, int y) {
	InputManager::checkInit();

	InputManager::__keyboardCallback(key, x, y, true, instance->key_press_table[key]);
	instance->key_press_table[key] = true;
}

void InputManager::keyboardUp(unsigned char key, int x, int y) {
	InputManager::checkInit();

	InputManager::__keyboardCallback(key, x, y, false, instance->key_press_table[key]);
	instance->key_press_table[key] = false;
}

void InputManager::__specialCallback(int key, int x, int y, bool down, bool was_down) {
	int mod = glutGetModifiers();
	bool ctrl = (mod & GLUT_ACTIVE_CTRL) != 0;
	bool shift = (mod & GLUT_ACTIVE_SHIFT) != 0;
	bool alt = (mod & GLUT_ACTIVE_ALT) != 0;

	auto input = InputKeyboardSpecial{
		key,
		was_down,
		down,
		Vector2<int>(x, y),
		ctrl, shift, alt,
	};


	for (auto it = instance->special_key_press_callbacks.begin(); it != instance->special_key_press_callbacks.end();) {
		auto& [_, callback] = *it;
		if (!callback.valid) {
			it = instance->special_key_press_callbacks.erase(it);
		}
		else {
			callback.func(*instance, input);
			++it;
		}
	}

	instance->ctrl = ctrl;
	instance->shift = shift;
	instance->alt = alt;
}

void InputManager::specialDown(int key, int x, int y) {
	InputManager::checkInit();

	InputManager::__specialCallback(key, x, y, true,
		instance->special_key_press_table.find(key) != instance->special_key_press_table.end()
	);
	instance->special_key_press_table.insert(key);
}

void InputManager::specialUp(int key, int x, int y) {
	InputManager::checkInit();

	InputManager::__specialCallback(key, x, y, false,
		instance->special_key_press_table.find(key) != instance->special_key_press_table.end()
	);
	instance->special_key_press_table.erase(key);
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
	case 3:
		mouse_button = MOUSE_BUTTON::SCROLL_UP;
		break;
	case 4:
		mouse_button = MOUSE_BUTTON::SCROLL_DOWN;
		break;
	default:
		throw std::runtime_error("InvalidMouseButton");
	}

	auto input = InputMouse{
		mouse_button,
		state == GLUT_DOWN,
		Vector2<int>(x, y),
	};

	for (auto it = instance->mouse_press_callbacks.begin(); it != instance->mouse_press_callbacks.end();) {
		auto& [_, callback] = *it;
		if (!callback.valid) {
			it = instance->mouse_press_callbacks.erase(it);
		}
		else {
			callback.func(*instance, input);
			++it;
		}
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
	}
}

void InputManager::motion(int x, int y) {
	InputManager::checkInit();

	auto input = InputMouseMotion{
		Vector2<int>(x, y)
	};

	for (auto it = instance->mouse_motion_callbacks.begin(); it != instance->mouse_motion_callbacks.end();) {
		auto& [_, callback] = *it;
		if (!callback.valid) {
			it = instance->mouse_motion_callbacks.erase(it);
		}
		else {
			callback.func(*instance, input);
			++it;
		}
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
	logger << "Attached keyPressCallback of id " << id << logger.info;
	key_press_callbacks.emplace(id, KeyPressFunc{ true, func });
}

void InputManager::attachSpecialKeyPressCallback(std::string id, specialKeyPressFuncType func) {
	logger << "Attached specialKeyPressCallback of id " << id << logger.info;
	special_key_press_callbacks.emplace(id, SpecialKeyPressFunc{ true, func });
};

void InputManager::attachMousePressCallback(std::string id, mousePressFuncType func) {
	logger << "Attached mousePressCallback of id " << id << logger.info;
	mouse_press_callbacks.emplace(id, MousePressFunc{ true, func });
}

void InputManager::attachMouseMotionCallback(std::string id, mouseMotionFuncType func) {
	logger << "Attached mouseMotionCallback of id " << id << logger.info;
	mouse_motion_callbacks.emplace(id, MouseMotionFunc{ true, func });
}

void InputManager::detachKeyPressCallback(std::string id) {
	logger << "Detached keyPressCallback of id " << id << logger.info;
	if (key_press_callbacks.find(id) != key_press_callbacks.end())
		key_press_callbacks[id].valid = false;
}

void InputManager::detachSpecialKeyPressCallback(std::string id) {
	logger << "Detached specialKeyPressCallback of id " << id << logger.info;
	if (special_key_press_callbacks.find(id) != special_key_press_callbacks.end())
		special_key_press_callbacks[id].valid = false;
}

void InputManager::detachMousePressCallback(std::string id) {
	logger << "Detached mousePressCallback of id " << id << logger.info;
	if (mouse_press_callbacks.find(id) != mouse_press_callbacks.end())
		mouse_press_callbacks[id].valid = false;
}


void InputManager::detachMouseMotionCallback(std::string id) {
	logger << "Detached mouseMotionCallback of id " << id << logger.info;
	if (mouse_motion_callbacks.find(id) != mouse_motion_callbacks.end())
		mouse_motion_callbacks[id].valid = false;
}

void InputManager::checkInit() {
	if (!instance) {
		logger << "InputManager instance not initialized" << logger.error;
		throw std::runtime_error("UninitializedInputManager");
	}
}