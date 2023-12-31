#pragma once

#include <unordered_map>
#include <optional>

#include "Util/Vector.h"
#include "Map/Tile/Tile.h"
#include "Asset/MapAsset.h"
#include "Entity/EntityPhysics.interface.h"

class Map {
public:
	explicit Map();
	explicit Map(int width, int height);
	~Map();

	void clear();
	void loadFromMapAsset(IGame& game_interface, std::shared_ptr<MapAsset> map_asset);

	void draw(const Camera& camera) const;
	void handleCollision(IEntityPhysics* ep);

	void setTile(IGame& game_interface, Tile* tile);
	std::optional<Tile const*> getTile(Vector3<int> pos) const;
	bool hasTile(Vector3<int> pos) const;

private:
	int width;
	int height;

	std::unordered_map<Vector3<int>, Tile*> data;

	std::string palette;

	static Logger logger;

};