#pragma once

#include <unordered_map>
#include <optional>

#include "Util/Vector.h"
#include "Map/Tile/Tile.h"

class Map {
public:
	Map() = delete;
	explicit Map(int width, int height);
	~Map();

	void draw(const Camera& camera) const;
	void handleCollision(Entity* entity);

	void setTile(IGame& game_interface, Tile* tile);
	std::optional<Tile const*> getTile(Vector3<int> pos) const;

private:
	int width;
	int height;

	std::unordered_map<Vector3<int>, Tile*> data;

};