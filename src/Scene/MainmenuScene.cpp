#include <iostream>
#include "Constants.h"
#include "GameScene.h"
#include "MinigameScene.h"

#include "MainmenuScene.h"


using namespace std::placeholders;

void MainmenuScene::init(IGame& game_interface) {
	auto& asset_manager = game_interface.getIAssetManager();

	enabled = true;
	visible = true;
	paused = false;

	auto& input_manager = game_interface.getIInputManager();
	input_manager.attachKeyPressCallback(
		"mms_key",
		std::bind(&MainmenuScene::keyPressCallback, this, _1, _2)
	);
}

void MainmenuScene::clear(IGame& game_interface) {
	auto& input_manager = game_interface.getIInputManager();
	input_manager.detachKeyPressCallback("mms_key");
}

void MainmenuScene::idle(IGame& game_interface, float t) {

}

void MainmenuScene::draw(IGame& game_interface) {
	auto& asset_manager = game_interface.getIAssetManager();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBindTexture(GL_TEXTURE_2D, asset_manager.getImageAsset("logo")->getTextureID());

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-3.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(3.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(3.0f, -0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glRasterPos2f(-1.3f, -1.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*) "Press (S) to start!");

	glRasterPos2f(-2.3f, -2.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*) "Press (M) to start minigame!");
}

void MainmenuScene::keyPressCallback(IInputManager& interface, const InputKeyboard& input) {
	if (!enabled) return;
	if (input.key == 's' && input.down) {
		this->enabled = false;
		this->append(new GameScene());
	}
	else if (input.key == 'm' && input.down) {
		this->enabled = false;
		this->append(new MinigameScene());
	}
}