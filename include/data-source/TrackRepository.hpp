#pragma once

#include <string>
#include "domain/Playlist.hpp"

class TrackRepository
{
private:
    std::string dataFolderPath;
public:
    TrackRepository(const std::string& dataFolder);
    void setDataFolderPath(const std::string& path);
    Playlist loadTracks() const;
};
