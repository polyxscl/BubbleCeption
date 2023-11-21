#include "AudioAsset.h"
#include <thread> // for demonstration purposes

AudioAsset::AudioAsset(std::string id, const fs::path& file_path)
    : Asset(id, file_path), playing(false) {}

AudioAsset::~AudioAsset() {
    stop(); // Ensure audio is stopped before destruction (cleanup).
}

void AudioAsset::load() {
    // For demonstration purposes, print a message indicating loading.
    std::cout << "Loading audio file: " << file_path << std::endl;
    // Additional code to load audio file can be added here.
}

void AudioAsset::play() {
    // For demonstration purposes, print a message indicating playback.
    std::cout << "Playing audio: " << id << std::endl;

    // In a real scenario, use a proper audio library to handle playback.
    // Here, we simulate playback with a delay using a thread.
    playing = true;
    std::thread playbackThread([this]() {
        // Simulate audio playback (replace this with actual playback code).
        // This is a placeholder, and you need to implement the actual playback.
        while (playing) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Audio playing..." << std::endl;
        }
        });

    playbackThread.detach(); // Detach thread to run in the background.
}

void AudioAsset::stop() {
    // For demonstration purposes, print a message indicating stopping.
    std::cout << "Stopping audio: " << id << std::endl;

    // In a real scenario, use a proper audio library to handle stopping.
    // Here, we just update the playing flag (replace this with actual stopping code).
    playing = false;
}