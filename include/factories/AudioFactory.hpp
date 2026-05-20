#pragma once

#include "domain/AudioEngine.hpp"

class AudioFactory
{
public:
    virtual ~AudioFactory() = default;
    virtual AudioEngine* createAudioEngine() = 0;
};
