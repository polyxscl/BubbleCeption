#pragma once

#include "Asset.h"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

class AudioAsset : public Asset {
public:
    AudioAsset(std::string id, const fs::path& file_path);
    ~AudioAsset() override;

    void load() override;
    void play();
    void stop();

private:
    sf::Music music;
    bool playing;
};