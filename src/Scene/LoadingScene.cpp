#include <iostream>
#include "LoadingScene.h"

void LoadingScene::init(IGame& game_interface) {
	auto& asset_manager = game_interface.getIAssetManager();

	enabled = true;
	visible = true;
	paused = false;

	this->texture = asset_manager.getImageAsset("snu");
}

void LoadingScene::idle(IGame& game_interface, float t) {
	// Do nothing for now.
}

void LoadingScene::draw(IGame& game_interface) {
	// If texture does not exist, return.
	if (!texture) return;

	auto& unwrapped_texture = *(texture.get());

	Vector2<float> size(0.3f, 0.3f);
	Vector2<float> pos(0.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, unwrapped_texture.get_texture_id());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-size.x / 2 + pos.x, -size.y / 2 + pos.y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-size.x / 2 + pos.x, size.y / 2 + pos.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(size.x / 2 + pos.x, size.y / 2 + pos.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(size.x / 2 + pos.x, -size.y / 2 + pos.y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}