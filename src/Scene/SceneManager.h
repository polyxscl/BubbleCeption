#pragma once

#include <unordered_map>
#include <vector>

#include "SceneManager.interface.h"
#include "Game.interface.h"
#include "Scene/Scene.h"
#include "Util/Logger.h"

class SceneManager : public ISceneManager {
public:
	explicit SceneManager();
	~SceneManager();

	void init(IGame* game_interface);
	void idle(float t);
	void draw();

	void registerScene(Scene* scene);

private:
	static SceneManager* instance;
	static IGame* game_interface;

	std::vector<Scene*> scene_stack;

	static void switchCallback(Scene* self, Scene* scene);
	static void appendCallback(Scene* self, Scene* scene);
	static void finishCallback(Scene* self);

	static Logger logger;
	static void checkInit();

};