#pragma once

#include <Util/Vector.h>
#include <Asset/MaterialAsset.h>

class Model {
public:
	virtual void draw() = 0;

	std::shared_ptr<MaterialAsset> material;

};