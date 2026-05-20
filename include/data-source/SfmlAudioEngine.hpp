#pragma once

#include <string>
#include <SFML/Audio.hpp>
#include "domain/AudioEngine.hpp"

class SfmlAudioEngine : public AudioEngine
{
private:
    sf::Music music;
    bool playingStatus = false;
public:
    SfmlAudioEngine() = default;
    ~SfmlAudioEngine() = default;
    void playTrack(const std::string& filePath) override;
    void stop() override;
    bool isPlaying() const override;
    void setVolume(float volume) override;
    void pause() override;
    void seek(float position) override;
};
