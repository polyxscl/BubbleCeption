#pragma once

#include "Asset/ImageAsset.h"
#include "Minigame/M_Vector.h"

class M_Image {
public:
	void draw(Vector3f a, Vector3f b, Vector3f c, Vector3f d);
	std::shared_ptr<ImageAsset> asset;
};