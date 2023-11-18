#include "Scene.h"

void Scene::attachSwitchCallback(sceneSwitchFuncType func) {
	switch_callback = func;
}

void Scene::attachAppendCallback(sceneAppendFuncType func) {
	append_callback = func;
}

void Scene::attachFinishCallback(sceneFinishFuncType func) {
	finish_callback = func;
}

void Scene::switchTo(Scene* scene) {
	switch_callback(this, scene);
}

void Scene::append(Scene* scene) {
	append_callback(this, scene);
}

void Scene::finish() {
	finish_callback(this);
}