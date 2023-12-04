#include <iostream>
#include "Constants.h"
#include "VictoryScene.h"

using namespace std::placeholders;

void VictoryScene::init(IGame& game_interface) {
	auto& asset_manager = game_interface.getIAssetManager();

	enabled = true;
	visible = true;
	paused = false;

	progress = 0.0f;
	elapsed = 0.0f;

	auto& input_manager = game_interface.getIInputManager();
	input_manager.attachKeyPressCallback(
		"vs_key",
		std::bind(&VictoryScene::keyPressCallback, this, _1, _2)
	);

	this->texture = asset_manager.getImageAsset("victory");
}

void VictoryScene::clear(IGame& game_interface) {
	auto& input_manager = game_interface.getIInputManager();
	input_manager.detachKeyPressCallback("vs_key");
}

void VictoryScene::idle(IGame& game_interface, float t) {
	elapsed += t;

	progress = elapsed / 2.f;

	if (progress > 1.0f)
		this->finish();
}

void VictoryScene::draw(IGame& game_interface) {
	// If texture does not exist, return.
	if (!texture) return;

	auto& unwrapped_texture = *(texture.get());

	Vector2<float> size(10.f, 10.f * unwrapped_texture.getHeight() / unwrapped_texture.getWidth());
	Vector2<float> pos(0.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, unwrapped_texture.getTextureID());

	auto alpha = (progress < 0.5f) ? 1.0f : (1.0f - progress) * 2.0f;

	glColor4f(1.0f, 1.0f, 1.0f, alpha);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-size.x / 2 + pos.x, -size.y / 2 + pos.y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-size.x / 2 + pos.x, size.y / 2 + pos.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(size.x / 2 + pos.x, size.y / 2 + pos.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(size.x / 2 + pos.x, -size.y / 2 + pos.y);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	// Set the color to black with the current opacity
	glColor4f(0.0f, 0.0f, 0.0f, progress);

	// Enable blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw a full-screen rectangle
	glBegin(GL_QUADS);
	glVertex2f(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2);
	glVertex2f(SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2);
	glVertex2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	glVertex2f(-SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	glEnd();

	// Disable blending

	glDisable(GL_BLEND);
}

void VictoryScene::keyPressCallback(IInputManager& interface, const InputKeyboard& input) {

}