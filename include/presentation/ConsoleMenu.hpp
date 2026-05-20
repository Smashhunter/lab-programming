#pragma once

#include "domain/PlaybackQueue.hpp"
#include "presentation/PlaylistPrinter.hpp"

class ConsoleMenu
{
private:
    PlaybackQueue* playbackQueue;
    PlaylistPrinter playlistPrinter;
public:
    ConsoleMenu(PlaybackQueue* queue);
    void displayMenu() const;
    void handleUserInput();
};
