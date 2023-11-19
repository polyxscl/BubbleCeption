#include "Constants.h"
#include "GameScene.h"

using namespace std::placeholders;

void GameScene::init(IGame& game_interface) {
	player.init(game_interface);

	auto& input_manager = game_interface.getIInputManager();
	input_manager.attachSpecialKeyPressCallback(
		"gs_spkey",
		std::bind(&GameScene::specialKeyPressCallback, this, _1, _2)
	);
}

void GameScene::clear(IGame& game_interface) {
	auto& input_manager = game_interface.getIInputManager();
	input_manager.detachSpecialKeyPressCallback("gs_spkey");
}

void GameScene::idle(IGame& game_interface, float t) {
	player.idle(t);
}

void GameScene::draw(IGame& game_interface) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2,
		-100.0, 100.0
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	player.draw();
}

void GameScene::specialKeyPressCallback(IInputManager& interface, const InputKeyboardSpecial& input) {
	switch (input.key) {
	case GLUT_KEY_LEFT:
		if (!input.was_down && input.down) {
			player.startMovingLeft();
		}
		else if (!input.down) {
			player.stopMovingLeft();
		}
		break;
	case GLUT_KEY_RIGHT:
		if (!input.was_down && input.down) {
			player.startMovingRight();
		}
		else if (!input.down) {
			player.stopMovingRight();
		}
		break;
	}
}