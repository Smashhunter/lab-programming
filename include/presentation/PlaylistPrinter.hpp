#pragma once

#include "presentation/TrackPrinter.hpp"
#include "domain/PlaybackQueue.hpp"

class PlaylistPrinter
{
private:
    TrackPrinter trackPrinter;
public:
    void printQueue(const PlaybackQueue& queue);
};
