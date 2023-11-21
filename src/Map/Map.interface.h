#pragma once

#include <optional>

#include "Util/Vector.h"
#include "Map/Tile/Tile.h"
#include "Asset/MapAsset.h"

class IMap {
public:
	virtual void clear();
	virtual void loadFromMapAsset(IGame& game_interface, std::shared_ptr<MapAsset> map_asset);

	virtual void draw(const Camera& camera) const;

	virtual void setTile(IGame& game_interface, Tile* tile);
	std::optional<Tile const*> getTile(Vector3<int> pos) const;
	bool hasTile(Vector3<int> pos) const;
};