#pragma once

#include <unordered_set>
#include <unordered_map>

#include "InputManager.interface.h"
#include "Util/Logger.h"

class InputManager : public IInputManager {
public:
	explicit InputManager();

	void init();

	static void keyboardDown(unsigned char key, int x, int y);
	static void keyboardUp(unsigned char key, int x, int y);
	static void specialDown(int key, int x, int y);
	static void specialUp(int key, int x, int y);
	static void mouse(int button, int state, int x, int y);
	static void motion(int x, int y);
	static void passiveMotion(int x, int y);

	bool isKeyPressed(unsigned char key) const override;
	bool isSpecialKeyPressed(int key) const override;
	bool isCtrlPressed() const override;
	bool isAltPressed() const override;
	bool isShiftPressed() const override;

	void attachKeyPressCallback(std::string id, keyPressFuncType func) override;
	void attachSpecialKeyPressCallback(std::string id, specialKeyPressFuncType func) override;
	void attachMousePressCallback(std::string id, mousePressFuncType func) override;
	void attachMouseMotionCallback(std::string id, mouseMotionFuncType func) override;

private:
	static InputManager* instance;
	static void checkInit();

	static void __keyboardCallback(unsigned char key, int x, int y, bool down);
	static void __specialCallback(int key, int x, int y, bool down);

	bool key_press_table[256];
	std::unordered_set<int> special_key_press_table;
	bool ctrl = false;
	bool alt = false;
	bool shift = false;

	bool mouse_left = false;
	bool mouse_middle = false;
	bool mouse_right = false;

	Vector2<int> mouse_pos;

	std::unordered_map<std::string, keyPressFuncType> key_press_callbacks;
	std::unordered_map<std::string, specialKeyPressFuncType> special_key_press_callbacks;
	std::unordered_map<std::string, mousePressFuncType> mouse_press_callbacks;
	std::unordered_map<std::string, mouseMotionFuncType> mouse_motion_callbacks;

	static Logger logger;

};