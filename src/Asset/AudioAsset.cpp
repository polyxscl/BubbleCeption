#include "Asset/AudioAsset.h"

void AudioAsset::load() {
    ma_result result = ma_decoder_init_file(file_path.string().c_str(), NULL, &decoder);
    if (result != MA_SUCCESS) {
        std::cerr << "Failed to load audio file: " << file_path << std::endl;
        this->valid = false;
    }
    if (valid) {
        ma_decoder_seek_to_pcm_frame(&decoder, 0);

        ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
        deviceConfig.playback.format = decoder.outputFormat;
        deviceConfig.playback.channels = decoder.outputChannels;
        deviceConfig.sampleRate = decoder.outputSampleRate;
        deviceConfig.dataCallback = AudioAsset::data_callback;
        deviceConfig.pUserData = this;

        ma_result result = ma_device_init(NULL, &deviceConfig, &device);
        if (result != MA_SUCCESS) {
            std::cerr << "Failed to initialize playback device" << std::endl;
            valid = false;
            return;
        }
    }
}

void AudioAsset::play() {
    if (valid) {
        if (ma_device_is_started(&device)) {
            ma_device_set_master_volume(&device, this->volume);
        }
        else {
            ma_result result = ma_device_start(&device);
            if (result != MA_SUCCESS) {
                std::cerr << "Failed to start playback device" << std::endl;
                valid = false;
                return;
            }
        }
    }
}

void AudioAsset::pause() {
    if (valid) {
        ma_device_stop(&device);
    }
}
void AudioAsset::stop() {
    if (valid) {
        ma_device_uninit(&device);
    }
}

void AudioAsset::setvolume(float v) {
    this->volume = v;
    ma_device_set_master_volume(&device, this->volume);
}

AudioAsset::~AudioAsset() {
    if (valid) {
        this->stop();
        ma_decoder_uninit(&decoder);

    }
}

ma_uint32 AudioAsset::data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
   AudioAsset* pAudioAsset = static_cast<AudioAsset*>(pDevice->pUserData);
        if (pAudioAsset == nullptr) {
            return 0;
        }
   return ma_decoder_read_pcm_frames(&pAudioAsset->decoder, pOutput, frameCount, nullptr);
}