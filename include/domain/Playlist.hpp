#pragma once

#include <string>
#include <vector>
#include "domain/Track.hpp"

class Playlist
{
private:
    std::vector<Track> tracks;
public:
    void addTrack(const Track& track);
    void removeTrack(int index);
    const std::vector<Track>& getTracks() const;
    int getTrackCount() const;
};
