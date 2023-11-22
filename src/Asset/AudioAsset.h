#pragma once

#include "Asset.h"
#include <iostream>

class AudioAsset : public Asset {
public:
    AudioAsset(std::string id, const fs::path& file_path);
    ~AudioAsset() override;

    void load() override;
    void play();
    void stop();

private:
    // Additional members for handling audio playback can be added here
    // (e.g., using a third-party audio library).
    bool playing;
};