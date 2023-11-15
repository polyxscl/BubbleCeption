#include "ImageAsset.h"

Logger ImageAsset::logger("ImageAsset");

ImageAsset::~ImageAsset() {
	delete[] data;
}

void ImageAsset::load() {
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(file_path.string().c_str(), 0), file_path.string().c_str());
	if (!image) {
		logger << "Failed to load image @ " << file_path << logger.info;
		valid = false;
		return;
	}

	FIBITMAP* rgba32 = FreeImage_ConvertTo32Bits(image); // Convert to 32-bit RGBA format
	FreeImage_Unload(image); // Remove previous FIBITMAP* (image)
	image = rgba32;

	width = FreeImage_GetWidth(image);
	height = FreeImage_GetHeight(image);

	data = new GLubyte[4 * width * height]; // Allocate memory for image data
	std::memcpy(data, FreeImage_GetBits(image), 4 * width * height); // Copy data from image

}

void ImageAsset::bind_texture() {
	if (!texture_id) {
		glGenTextures(1, &texture_id);
	}

	glBindTexture(GL_TEXTURE_2D, texture_id); // Bind the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture, stop modifying parameters
}

GLuint ImageAsset::get_texture_id() {
	return texture_id;
}