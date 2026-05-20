#pragma once

#include "domain/Track.hpp"

class TrackPrinter
{
public:
    static void printTrackInfo(const Track& track, bool isCurrent);
};
