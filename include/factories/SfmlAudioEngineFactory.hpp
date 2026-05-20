#pragma once

#include "factories/AudioFactory.hpp"
#include "data-source/SfmlAudioEngine.hpp"

#include <iostream>

class SfmlAudioEngineFactory : public AudioFactory
{
public:
    AudioEngine* createAudioEngine() override;
};
