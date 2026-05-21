#pragma once

#include "factories/AudioFactory.hpp"
#include "domain/AudioEngine.hpp"
#include "data-source/TrackRepository.hpp"
#include "domain/PlaybackQueue.hpp"
#include "presentation/ConsoleMenu.hpp"

#include <iostream>

class PlayerApplication
{
private:
    AudioFactory* audioFactory;
    AudioEngine* audioEngine;
    TrackRepository* trackRepository;
    PlaybackQueue* playbackQueue;
    ConsoleMenu* consoleMenu;
    bool isRunning = true;
public:
    PlayerApplication(AudioFactory* factory, TrackRepository* repository);
    void run();
};
