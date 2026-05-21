#pragma once

#include "domain/PlaybackQueue.hpp"
#include "presentation/PlaylistPrinter.hpp"
#include "data-source/TrackRepository.hpp"

class ConsoleMenu
{
private:
    PlaybackQueue* playbackQueue;
    PlaylistPrinter playlistPrinter;
public:
    ConsoleMenu(PlaybackQueue* queue);
    void displayMenu() const;
    void handleUserInput(TrackRepository* repository);
};
