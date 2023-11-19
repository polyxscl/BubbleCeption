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

	bindTexture();
}

void ImageAsset::bindTexture() {

	GLuint texture_id_buffer = 0;
	glGenTextures(1, &texture_id_buffer);
	texture_id = texture_id_buffer;

	if (texture_id == 0) {
		logger << "Error occurred generating GL texture. The texture of id " << id << " might not be loaded." << logger.error;
	}

	glBindTexture(GL_TEXTURE_2D, texture_id); // Bind the texture

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
}

void ImageAsset::fromRawRGBA8(int width, int height, GLubyte* input_data) {
	this->width = width;
	this->height = height;

	delete data;
	data = input_data;

	bindTexture();
}

GLuint ImageAsset::getTextureID() const {
	return texture_id;
}

int ImageAsset::getWidth() const {
	return width;
}

int ImageAsset::getHeight() const {
	return height;
}

void ImageAsset::dumpBitData() const {
	size_t dataSize = width * height * 4; // Assuming 4 bytes per pixel (RGBA)

	for (size_t i = 0; i < dataSize; ++i) {
		// Output as hexadecimal
		std::cout << std::hex << std::setw(2) << std::setfill('0')
			<< static_cast<unsigned>(data[i]);

		if ((i + 1) % 4 == 0) {
			std::cout << std::endl; // New line for each pixel for readability
		}
		else {
			std::cout << " "; // Separate the components of a single pixel
		}
	}

	std::cout << std::dec;
}