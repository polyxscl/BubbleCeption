
#include <algorithm>

#include "SceneManager.h"

#include "GL/freeglut.h"

SceneManager* SceneManager::instance = nullptr;
IGame* SceneManager::game_interface = nullptr;

Logger SceneManager::logger("SceneManager");

SceneManager::SceneManager() {
	if (instance) {
		logger << "Duplicate instances of SceneManager is not allowed" << logger.error;
		throw std::runtime_error("DuplicateSceneManager");
	}

	logger << "Creating SceneManager class..." << logger.info;

	// Singleton
	instance = this;
}

SceneManager::~SceneManager() {
	for (auto& elem : scene_stack) {
		delete elem;
	}
	scene_stack.clear();
}

void SceneManager::init(IGame* game_interface) {
	logger << "Initializing SceneManager..." << logger.info;
	this->game_interface = game_interface;
}

void SceneManager::idle(float t) {
	for (auto& scene : scene_stack) {
		if (!scene->enabled) continue;
		if (!scene->paused) scene->idle(*game_interface, t);
	}

	glutPostRedisplay();
}

void SceneManager::draw() {
	for (auto& scene : scene_stack) {
		if (!scene->enabled) continue;
		if (scene->visible) scene->draw(*game_interface);
	}
}

void SceneManager::registerScene(Scene* scene) {
	scene->attachSwitchCallback(SceneManager::switchCallback);
	scene->attachAppendCallback(SceneManager::appendCallback);
	scene->attachFinishCallback(SceneManager::finishCallback);
	scene->init(*game_interface);
	scene_stack.push_back(scene);
}

void SceneManager::switchCallback(Scene* self, Scene* other) {
	checkInit();

	auto& stack = instance->scene_stack;

	self->clear(*game_interface);
	auto it = std::find(stack.begin(), stack.end(), self);
	*it = other;
	delete self;

	other->attachSwitchCallback(SceneManager::switchCallback);
	other->attachAppendCallback(SceneManager::appendCallback);
	other->attachFinishCallback(SceneManager::finishCallback);
	other->init(*game_interface);
}

void SceneManager::appendCallback(Scene* self, Scene* other) {
	checkInit();

	auto& stack = instance->scene_stack;

	stack.push_back(other);

	other->attachSwitchCallback(SceneManager::switchCallback);
	other->attachAppendCallback(SceneManager::appendCallback);
	other->attachFinishCallback(SceneManager::finishCallback);
	other->init(*game_interface);
}

void SceneManager::finishCallback(Scene* self) {
	checkInit();

	auto& stack = instance->scene_stack;

	self->clear(*game_interface);
	stack.erase(std::find(stack.begin(), stack.end(), self));

	if (!stack.empty()) {
		stack.back()->enabled = true;
		stack.back()->paused = false;
		stack.back()->visible = true;
	}
}

void SceneManager::checkInit() {
	if (!instance) {
		logger << "SceneManager instance not initialized" << logger.error;
		throw std::runtime_error("UninitializedSceneManager");
	}
}