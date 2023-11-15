#pragma once

#include "Input/Input.h"

// Forward declaration for self-referencing
class IInputManager;

typedef void (*keyPressFuncType)(IInputManager& input_manager_interface, const InputKeyboard& input);
typedef void (*specialKeyPressFuncType)(IInputManager& input_manager_interface, const InputKeyboardSpecial& input);
typedef void (*mousePressFuncType)(IInputManager& input_manager_interface, const InputMouse& input);
typedef void (*mouseMotionFuncType)(IInputManager& input_manager_interface, const InputMouseMotion& input);

// Interface for InputManager class.
class IInputManager {
	virtual bool isKeyPressed(unsigned char key) const = 0;
	virtual bool isSpecialKeyPressed(int key) const = 0;
	virtual bool isCtrlPressed() const = 0;
	virtual bool isAltPressed() const = 0;
	virtual bool isShiftPressed() const = 0;

	virtual void attachKeyPressCallback(std::string id, keyPressFuncType func) = 0;
	virtual void attachSpecialKeyPressCallback(std::string id, specialKeyPressFuncType func) = 0;
	virtual void attachMousePressCallback(std::string id, mousePressFuncType func) = 0;
	virtual void attachMouseMotionCallback(std::string id, mouseMotionFuncType func) = 0;

};