#include "data-source/TrackRepository.hpp"

#include <iostream>
#include <filesystem>

TrackRepository::TrackRepository(const std::string &dataFolder)
    : dataFolderPath(dataFolder)
{
}

void TrackRepository::setDataFolderPath(const std::string &path)
{
    dataFolderPath = path;
}
Playlist TrackRepository::loadTracks() const
{
    Playlist playlist;

    for(const auto& entry : std::filesystem::directory_iterator(dataFolderPath))
    {
        if(entry.is_regular_file())
        {
            std::string filePath = entry.path().string();
            std::string fileName = entry.path().filename().string();
            playlist.addTrack(Track(fileName, filePath));
        }
    }
    return playlist;
}
