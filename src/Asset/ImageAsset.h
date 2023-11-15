#pragma once

#include <string>
#include <sstream>

#include "Asset/Asset.h"
#include "Util/Logger.h"

#include <GL/freeglut.h>
#include <FreeImage.h>

class ImageAsset : public Asset {
public:
	using Asset::Asset;

	~ImageAsset() override;

	void load() override;
	void bind_texture();
	GLuint get_texture_id();

private:
	GLuint texture_id = 0;
	GLubyte* data = nullptr;
	int width = 0;
	int height = 0;

	static Logger logger;
};