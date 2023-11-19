#include <stdexcept>
#include <filesystem>
#include <ctime>

#include "Game.h"
#include "Scene/LoadingScene.h"
#include "Constants.h"

#include <GL/freeglut.h>

namespace fs = std::filesystem;

static clock_t last_time = clock();
static fs::path ASSETS_PATH = fs::current_path() / "assets/";

Logger Game::logger("Game");

Game* Game::instance = nullptr;

Game::Game(int argc, char** argv) {
	if (instance) {
		logger << "Duplicate instances of Game is not allowed" << logger.error;
		throw std::runtime_error("DuplicateGame");
	}

	// Initialize GLUT.
	glutInit(&argc, argv);

	// For correct memory leak reports
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	
	// fs::path ASSETS_PATH = fs::current_path() / "assets/";

	// DO NOT PUT INITIALIZING CODE HERE.
	// THE OPENGL CONTEXT IS NOT LOADED UNTIL glutCreateWindow().

	// Initialize Window.
	logger << "Initializing Window..." << logger.info;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH * TILE_SIZE) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT * TILE_SIZE) / 2
	);
	glutInitWindowSize(SCREEN_WIDTH * TILE_SIZE, SCREEN_HEIGHT * TILE_SIZE);
	window_id = glutCreateWindow(GAME_NAME);

	// Initialize InputManager.
	input_manager.init();

	// Initialize Assets.
	asset_manager.loadAssets(ASSETS_PATH);

	// Initialize Scenes.
	scene_manager.init(this);

	scene_manager.registerScene(new LoadingScene());

	// Singleton
	instance = this;

	// Set GLUT functions.
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutCloseFunc(onClose);
}

void Game::run() {
	glutMainLoop();
}

void Game::display() {
	Game::checkInit();

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto& unwrapped_texture = *(instance->asset_manager.getImageAsset("snu").get());

	Vector2<float> size(0.3f, 0.3f);
	Vector2<float> pos(0.0f, 0.0f);

	instance->scene_manager.draw();

	glutSwapBuffers();
}

void Game::idle() {
	Game::checkInit();
	
	instance->scene_manager.idle((clock() - last_time) / 1000.f);

	glutPostRedisplay();
	last_time = clock();
}

void Game::onClose() {
	Game::checkInit();

	glutLeaveMainLoop();
}

IAssetManager& Game::getIAssetManager() {
	return asset_manager;
}

IInputManager& Game::getIInputManager() {
	return input_manager;
}

ISceneManager& Game::getISceneManager() {
	return scene_manager;
}

void Game::checkInit() {
	if (!instance) {
		logger << "Game instance not initialized" << logger.error;
		throw std::runtime_error("UninitializedGame");
	}
}