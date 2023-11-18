#include <bitset>
#include "ImageAsset.h"

static std::wstring stringToWstring(const std::string& str) {
	std::wstring wstr(str.begin(), str.end());
	return wstr;
}


void printBits(unsigned char* data, int width, int height) {
	
	int bytesPerPixel = 4; // Assuming 4 bytes per pixel (RGBA)
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			unsigned char* pixel = data + (y * width + x) * bytesPerPixel;
			std::bitset<8> r(pixel[0]);
			std::bitset<8> g(pixel[1]);
			std::bitset<8> b(pixel[2]);
			std::bitset<8> a(pixel[3]);
			std::cout << "Pixel (" << x << ", " << y << "): "
				<< "R: " << r << ", "
				<< "G: " << g << ", "
				<< "B: " << b << ", "
				<< "A: " << a << std::endl;
		}
	}
}

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

	bind_texture();
}

void ImageAsset::bind_texture() {

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
}

GLuint ImageAsset::get_texture_id() {
	return texture_id;
}