#pragma once

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class Asset {
public:
	// Empty path for standalone assets
	explicit Asset(std::string id)
		: file_path(fs::path()), id(id) {}

	explicit Asset(std::string id, const fs::path& file_path)
		: file_path(file_path), id(id) {}

	virtual ~Asset() {};

	virtual void load() = 0;

protected:
	const fs::path& file_path;
	std::string id;
	bool valid = true;

};