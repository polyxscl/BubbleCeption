#pragma once

#include <filesystem>
#include <fstream>

#include "Asset/Asset.h"
#include "Util/Logger.h"

#include <GL/freeglut.h>

class MaterialAsset : public Asset {
public:
	using Asset::Asset;

	void load() override;

	void set_emission(float r, float g, float b, float a);
	void set_ambient(float r, float g, float b, float a);
	void set_diffuse(float r, float g, float b, float a);
	void set_specular(float r, float g, float b, float a);
	void set_shininess(float s);

	const float* get_emission() const;
	const float* get_ambient() const;
	const float* get_diffuse() const;
	const float* get_specular() const;
	const float* get_shininess() const;

	void apply() const;

private:
	float emission[4];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess[1];

	static Logger logger;
};