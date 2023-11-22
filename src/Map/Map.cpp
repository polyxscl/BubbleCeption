#include "Map.h"

#include "Map/Tile/SolidTile.h"
#include "Map/Tile/PlatformTile.h"

Logger Map::logger("Map");

Map::Map()
	: width(0), height(0) {}

Map::Map(int width, int height)
	: width(width), height(height) {}

Map::~Map() {
	clear();
}

void Map::clear() {
	for (auto& elem : data) {
		delete elem.second;
	}
	data.clear();
}

void Map::loadFromMapAsset(IGame& game_interface, std::shared_ptr<MapAsset> map_asset) {
	clear();
	auto& asset_data = map_asset->getData();
	auto palette = map_asset->getPalette();

	for (auto& [pos, id] : asset_data) {
		if (!id.compare("SOLID"))
			setTile(game_interface, new SolidTile(pos));
		else if (!id.compare("PLATFORM"))
			setTile(game_interface, new PlatformTile(pos));
		else {
			logger << "Invalid tile id of " << id << logger.error;
			logger << "Map was not loaded properly! " << logger.error;
		}
	}
}

void Map::draw(const Camera& camera) const {
	for (auto& [pos, tile] : data) {
		tile->draw(camera);
	}
}


void Map::handleCollision(IEntityPhysics* ep) {
	for (auto& [pos, tile] : data) {
		if (tile->isCollision(ep))
			tile->onCollision(ep);
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

bool Map::hasTile(Vector3<int> pos) const {
	return data.find(pos) != data.end();
}