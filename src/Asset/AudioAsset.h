#pragma once
#include <string>
#include <sstream>
#include <iostream>

#include "Asset/Asset.h"
#include "Util/Logger.h"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

enum AudioType{SONG, EFFECT};
class AudioAsset: public Asset {
public:
	using Asset::Asset;
	~AudioAsset();
	
	void load() override;
	void play();
	void pause();
	void stop();
	void setVolume(float v);

private:
	static ma_uint32 data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
	float second;
	float volume;
	AudioType type;
	ma_decoder decoder;
	ma_device device;

	static Logger logger;
};