#pragma once

#include "LoadingScene.interface.h"
#include "Game.interface.h"
#include "Scene/Scene.h"
#include "Asset/ImageAsset.h"

class LoadingScene : public ILoadingScene {
public:
	void init(IGame& game_interface) override;
	void idle(IGame& game_interface, float t) override;
	void draw(IGame& game_interface) override;

private:
	std::shared_ptr<ImageAsset> texture;
};