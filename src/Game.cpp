#include <stdexcept>
#include <filesystem>

#include "Game.h"
#include "Constants.h"

#include <GL/freeglut.h>

namespace fs = std::filesystem;

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

	// Initialize Assets.
	asset_manager.loadAssets(ASSETS_PATH);

	// Initialize Window.
	logger << "Initializing Window..." << logger.info;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2
	);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow(GAME_NAME);

	// Singleton
	instance = this;

	// Set GLUT functions.
	glutDisplayFunc(display);
	glutIdleFunc(idle);
}

void Game::run() {
	glutMainLoop();
}

void Game::display() {
	Game::checkInit();
}

void Game::idle() {
	Game::checkInit();

	glutPostRedisplay();
}

IAssetManager& Game::getIAssetManager() {
	return asset_manager;
}

void Game::checkInit() {
	if (!instance) {
		logger << "Game instance not initialized" << logger.error;
		throw std::runtime_error("UninitializedGame");
	}
}