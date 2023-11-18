#pragma once

#include <functional>
#include "Input/Input.h"

// Forward declaration for self-referencing
class IInputManager;

typedef std::function<void(IInputManager&, const InputKeyboard&)> keyPressFuncType;
typedef std::function<void(IInputManager&, const InputKeyboardSpecial&)> specialKeyPressFuncType;
typedef std::function<void(IInputManager&, const InputMouse&)> mousePressFuncType;
typedef std::function<void(IInputManager&, const InputMouseMotion&)> mouseMotionFuncType;

// Interface for InputManager class.
class IInputManager {
public:
	virtual bool isKeyPressed(unsigned char key) const = 0;
	virtual bool isSpecialKeyPressed(int key) const = 0;
	virtual bool isCtrlPressed() const = 0;
	virtual bool isAltPressed() const = 0;
	virtual bool isShiftPressed() const = 0;

	virtual void attachKeyPressCallback(std::string id, keyPressFuncType func) = 0;
	virtual void attachSpecialKeyPressCallback(std::string id, specialKeyPressFuncType func) = 0;
	virtual void attachMousePressCallback(std::string id, mousePressFuncType func) = 0;
	virtual void attachMouseMotionCallback(std::string id, mouseMotionFuncType func) = 0;

	virtual void detachKeyPressCallback(std::string id) = 0;
	virtual void detachSpecialKeyPressCallback(std::string id) = 0;
	virtual void detachMousePressCallback(std::string id) = 0;
	virtual void detachMouseMotionCallback(std::string id) = 0;

};