#pragma once

#include <string>
#include "domain/Playlist.hpp"

class TrackRepository
{
private:
    std::string dataFolderPath;
public:
    TrackRepository(const std::string& dataFolder);
    Playlist loadTracks() const;
};
