#pragma once

#include <string>
#include <SFML/Audio.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include "domain/AudioEngine.hpp"

class SfmlAudioEngine : public AudioEngine
{
private:
    sf::Music music;
    std::thread workerThread;
    std::mutex audioMutex;
    std::condition_variable audioCondition;
    std::atomic<bool> running{true};
    std::atomic<bool> playingStatus{false};
    std::vector<AudioEngineListener*> listeners;
    enum class CommandType
    {
        Play,
        Stop,
        Pause,
        Seek,
        SetVolume,
        Shutdown

    };
    struct Command
    {
        CommandType type;
        std::string filePath; // For Play command
        float volume;        // For SetVolume command
        float percentage;      // For Seek command
    };
    std::queue<Command> commandQueue;

    void theadLoop();
    void handleCommand(const Command& cmd);
    void pushCommand(const Command& cmd);
    

public:
    SfmlAudioEngine();
    ~SfmlAudioEngine();
    void playTrack(const std::string& filePath) override;
    void stop() override;
    bool isPlaying() const override;
    void setVolume(float volume) override;
    void pause() override;
    void seek(float percentage) override;
    void addListener(AudioEngineListener* listener) override;
    void removeListener(AudioEngineListener* listener) override;
};
