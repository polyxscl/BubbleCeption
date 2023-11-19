#include <iostream>
#include "Constants.h"
#include "LoadingScene.h"

#include "GameScene.h"

using namespace std::placeholders;

void LoadingScene::init(IGame& game_interface) {
	auto& asset_manager = game_interface.getIAssetManager();

	enabled = true;
	visible = true;
	paused = false;

	progress = 0.0f;
	time = clock();

	auto& input_manager = game_interface.getIInputManager();
	input_manager.attachKeyPressCallback(
		"ls_key",
		std::bind(&LoadingScene::keyPressCallback, this, _1, _2)
	);

	this->texture = asset_manager.getImageAsset("snu");
}

void LoadingScene::clear(IGame& game_interface) {
	auto& input_manager = game_interface.getIInputManager();
	input_manager.detachKeyPressCallback("ls_key");
}

void LoadingScene::idle(IGame& game_interface, float t) {
	auto elapsed = clock() - time;

	progress = elapsed / 2000.f;

	if (progress > 1.0f)
		this->switchTo(new GameScene());
}

void LoadingScene::draw(IGame& game_interface) {
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

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void LoadingScene::keyPressCallback(IInputManager& interface, const InputKeyboard& input) {
	this->switchTo(new GameScene());
}