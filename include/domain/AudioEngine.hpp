#pragma once

#include <string>

class AudioEngineListener
{
public:
    virtual ~AudioEngineListener() = default;
    virtual void onTrackEnded() = 0;
};

class AudioEngine
{
public:
    virtual ~AudioEngine() = default;
    virtual void playTrack(const std::string& filePath) = 0;
    virtual void stop() = 0;
    virtual bool isPlaying() const = 0;
    virtual void setVolume(float volume) = 0; // Volume range: 0.0 (mute) to 1.0 (max)
    virtual void pause() = 0;
    virtual void seek(float position) = 0; // Position in seconds
    virtual void addListener(AudioEngineListener* listener) = 0;
    virtual void removeListener(AudioEngineListener* listener) = 0;
};
