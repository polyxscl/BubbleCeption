#include "AudioAsset.h"
#include <thread> // for demonstration purposes

AudioAsset::AudioAsset(std::string id, const fs::path& file_path)
    : Asset(id, file_path), playing(false) {
    std::string Path = file_path.string();
    if (!this->music.openFromFile(Path)) {
        std::cerr << "Failed to load music file: " << Path << std::endl;
    }
}

AudioAsset::~AudioAsset() {
    stop(); 
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

/*
int main() {
    // MP3 파일 경로
    std::string filePath = "path/to/your/song.mp3";

    // 노래를 로드합니다.
    sf::Music music;
    if (!music.openFromFile(filePath)) {
        std::cerr << "Failed to load music file: " << filePath << std::endl;
        return 1;
    }

    // 노래를 재생합니다.
    music.play();

    // 여기에 다른 작업을 추가할 수 있습니다.

    // 일정 시간 대기 후 노래를 멈춥니다.
    sf::sleep(sf::seconds(10)); // 10초 동안 대기

    // 노래를 멈춥니다.
    music.stop();

    return 0;
}
*/

/*
int main() {
    // MP3 파일 경로
    std::string filePath = "path/to/your/song.mp3";

    // 노래를 로드합니다.
    sf::Music music;
    if (!music.openFromFile(filePath)) {
        std::cerr << "Failed to load music file: " << filePath << std::endl;
        return 1;
    }

    // 시작 시간을 5초로 설정합니다.
    sf::Time startTime = sf::seconds(5.0f);
    music.setPlayingOffset(startTime);

    // 노래를 재생합니다.
    music.play();

    // 여기에 다른 작업을 추가할 수 있습니다.

    // 일정 시간 동안 대기한 후 노래를 멈춥니다.
    sf::sleep(sf::seconds(10)); // 10초 동안 대기

    // 노래를 멈춥니다.
    music.stop();

    return 0;
}
*/