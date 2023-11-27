#pragma once
#include <string>
#include <sstream>

#include "Asset/Asset.h"
#include "Util/Logger.h"

#include <miniaudio.h>
#include <iostream>

enum AudioType{SONG, EFFECT};
class AudioAsset: public Asset {
public:
	using Asset::Asset;
	void load() override;
	void play();
	void pause();
	void stop();
	void setvolume(float v);
	~AudioAsset();
private:
	static ma_uint32 data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
	float second;
	float volume;
	AudioType type;
	ma_decoder decoder;
	ma_device device;

	static Logger logger;
};