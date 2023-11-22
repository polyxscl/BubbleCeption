#pragma once

#include "Model.h"
#include "Util/Vector.h"

class SphereModel : public Model {
public:
	void draw() override;

	Vector3<float> size;
	int slices;
	int stacks;
	
};