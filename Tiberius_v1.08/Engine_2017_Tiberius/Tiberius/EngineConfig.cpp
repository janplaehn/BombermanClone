#include "stdafx.h"
#include "EngineConfig.h"

// Window
const char* EngineConfig::WINDOW_TITLE = "BOMBERMAN 2018";
const int EngineConfig::WINDOW_WIDTH = 680;
const int EngineConfig::WINDOW_HEIGHT = 480;
const int EngineConfig::TILE_WIDTH = 40;

// Audio
const int EngineConfig::AUDIO_FLAGS = MIX_INIT_OGG;
const int EngineConfig::AUDIO_FREQUENCY = 44100;
const Uint16 EngineConfig::AUDIO_FORMAT = MIX_DEFAULT_FORMAT;
const int EngineConfig::AUDIO_CHANNELS = 2;
const int EngineConfig::AUDIO_CHUNKSIZE = 1024;

// Image
const int EngineConfig::IMAGE_FLAGS = IMG_INIT_JPG | IMG_INIT_PNG;