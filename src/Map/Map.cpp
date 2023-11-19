#include "Map.h"

Map::Map(int width, int height)
	: width(width), height(height) {}

Map::~Map() {
	for (auto& elem : data) {
		delete elem.second;
	}
}

void Map::draw(const Camera& camera) const {
	for (auto& [pos, tile] : data) {
		tile->draw(camera);
	}
}

void Map::handleCollision(Entity* entity) {
	for (auto& [pos, tile] : data) {
		tile->onCollision(entity);
	}
}

void Map::setTile(IGame& game_interface, Tile* tile) {
	tile->init(game_interface);
	data[tile->pos] = tile;
}

std::optional<Tile const*> Map::getTile(Vector3<int> pos) const {
	auto it = data.find(pos);
	if (it == data.end())
		return std::nullopt;
	else
		return it->second;
}