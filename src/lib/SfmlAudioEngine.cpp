#include "data-source/SfmlAudioEngine.hpp"
#include <iostream>

void SfmlAudioEngine::theadLoop()
{
    std::unique_lock<std::mutex> lock(audioMutex);
    while (running){
        audioCondition.wait_for(lock, std::chrono::milliseconds(100), [this] {
        return !commandQueue.empty() || !running ||
               (music.getStatus() == sf::Music::Status::Stopped && playingStatus);
        });
        if (!running) break;

        bool trackEnded = (music.getStatus() == sf::Music::Status::Stopped && playingStatus);

        std::vector<AudioEngineListener*> listenersCopy;
        if (trackEnded) {
            playingStatus = false;
            listenersCopy = listeners;
        }

        if (trackEnded) {
            lock.unlock();
            for (auto* listener : listenersCopy) {
                listener->onTrackEnded();
            }
            lock.lock();
        }

        if (commandQueue.empty()) continue;

        Command cmd = commandQueue.front();
        commandQueue.pop();
        lock.unlock();

        handleCommand(cmd);

        lock.lock();
    }
}

void SfmlAudioEngine::handleCommand(const Command &cmd)
{
    switch (cmd.type)
    {
        case CommandType::Play:
            if(music.getStatus() == sf::Music::Status::Paused)
            {
                music.play();
                playingStatus = true;
            } else if(music.openFromFile(cmd.filePath))
            {
                music.play();
                playingStatus = true;
            }
            else
            {
                std::cerr << "Failed to load track: " << cmd.filePath << std::endl;
            }
            break;
        case CommandType::Stop:
            music.stop();
            playingStatus = false;
            break;
        case CommandType::Pause:
            if(playingStatus)
            {
                music.pause();
                playingStatus = false;
            }
            break;
        case CommandType::Seek:
            if(playingStatus)
            {
                music.setPlayingOffset(sf::seconds(cmd.percentage * 0.01f * music.getDuration().asSeconds()));
            }
            break;
        case CommandType::SetVolume:
            music.setVolume(cmd.volume * 100); // SFML volume is 0-100
            break;
        case CommandType::Shutdown:
            running = false;
            break;
    }
}

void SfmlAudioEngine::pushCommand(const Command &cmd)
{
    {
        std::lock_guard<std::mutex> lock(audioMutex);
        commandQueue.push(cmd);
    }
    audioCondition.notify_one();
}

SfmlAudioEngine::SfmlAudioEngine()
{
    workerThread = std::thread(&SfmlAudioEngine::theadLoop, this);
}

SfmlAudioEngine::~SfmlAudioEngine()
{
    pushCommand({CommandType::Shutdown, "", 0.0f, 0.0f});
    if(workerThread.joinable())
    {
        workerThread.join();
    }
}

void SfmlAudioEngine::playTrack(const std::string &filePath)
{
    pushCommand({CommandType::Play, filePath, 0.0f, 0.0f});
}

void SfmlAudioEngine::stop()
{
    pushCommand({CommandType::Stop, "", 0.0f, 0.0f});
}

bool SfmlAudioEngine::isPlaying() const
{
    return playingStatus.load();
}

void SfmlAudioEngine::setVolume(float volume)
{
    pushCommand({CommandType::SetVolume, "", volume, 0.0f});
}

void SfmlAudioEngine::pause()
{
    pushCommand({CommandType::Pause, "", 0.0f, 0.0f});
}

void SfmlAudioEngine::seek(float percentage)
{
    pushCommand({CommandType::Seek, "", 0.0f, percentage});
}

void SfmlAudioEngine::addListener(AudioEngineListener *listener)
{
    listeners.push_back(listener);
}
void SfmlAudioEngine::removeListener(AudioEngineListener *listener)
{
    listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
}
