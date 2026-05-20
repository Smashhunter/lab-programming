#include "factories/SfmlAudioEngineFactory.hpp"

AudioEngine *SfmlAudioEngineFactory::createAudioEngine()
{
    return new SfmlAudioEngine();
}
