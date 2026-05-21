#include "domain/Playlist.hpp"

void Playlist::addTrack(const Track &track)
{
    tracks.push_back(track);
}

void Playlist::removeTrack(int index)
{
    if (index >= 0 && index < tracks.size())
    {
        tracks.erase(tracks.begin() + index);
    }
}

const std::vector<Track> &Playlist::getTracks() const
{
    return tracks;
}

int Playlist::getTrackCount() const
{
    return tracks.size();
}
