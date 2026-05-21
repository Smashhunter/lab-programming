#include "presentation/PlaylistPrinter.hpp"

#include <iostream>

void PlaylistPrinter::printQueue(const PlaybackQueue &queue)
{
    std::cout << "========== CURRENT PLAYLIST ==========" << std::endl;
    const Playlist& playlist = queue.getPlaylist();
    const auto& tracks = playlist.getTracks();
    for (const auto& track : tracks) {
        trackPrinter.printTrackInfo(track, &track == queue.getCurrentTrack());
    }
}
