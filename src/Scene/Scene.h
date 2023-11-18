#pragma once

#include "Game.interface.h"

// Forward declaration for typedefs.
class Scene;

typedef void (*sceneSwitchFuncType)(Scene* self, Scene* scene);
typedef void (*sceneAppendFuncType)(Scene* self, Scene* scene);
typedef void (*sceneFinishFuncType)(Scene* self);

class Scene {
public:
	virtual ~Scene() {}

	void attachSwitchCallback(sceneSwitchFuncType func);
	void attachAppendCallback(sceneAppendFuncType func);
	void attachFinishCallback(sceneFinishFuncType func);

	virtual void init(IGame& game_interface) {}
	virtual void idle(IGame& game_interface, float t) {}
	virtual void draw(IGame& game_interface) {}

	bool enabled = true;
	bool visible = true;
	bool paused = false;

protected:
	void switchTo(Scene* scene);
	void append(Scene* scene);
	void finish();

private:
	sceneSwitchFuncType switch_callback;
	sceneFinishFuncType finish_callback;
	sceneAppendFuncType append_callback;

};