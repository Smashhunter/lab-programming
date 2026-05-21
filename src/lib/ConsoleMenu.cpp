#include "presentation/ConsoleMenu.hpp"

#include <iostream>

ConsoleMenu::ConsoleMenu(PlaybackQueue *queue)
{
    playbackQueue = queue;
}

void ConsoleMenu::displayMenu() const
{
    std::cout << "========== CONSOLE MUSIC PLAYER ==========" << std::endl;
    std::cout << "    ____  __    ___  __  __ ______ ____  " << std::endl;
    std::cout << "   / __ \\/ /   /   | \\ \\/ // ____// __ \\ " << std::endl;
    std::cout << "  / /_/ / /   / /| |  \\  // __/  / /_/ / " << std::endl;
    std::cout << " / ____/ /___/ ___ |  / // /___ / _, _/  " << std::endl;
    std::cout << "/_/   /_____/_/  |_| /_//_____//_/ |_|" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "Commands:\n"
     << "  play - Play the current track\n"
     << "  next - Play the next track\n"
     << "  prev - Play the previous track\n"
     << "  pause - Pause the current track\n"
     << "  loop - Toggle looping\n"
     << "  seek <percentage> - Seek to a specific percentage in the current track\n"
     << "  playlist - show current playlist\n"
     << "  volume <percentage> - set volume to a specific percentage\n"
     << "  load <path> - load a new playlist\n"
     << "  help - show this menu again\n"
     << "  exit - Exit the application\n"
     << "============================================" << std::endl;
}

void ConsoleMenu::handleUserInput(TrackRepository* repository)
{
    std::cout << "Enter command: ";
    std::string command;
    std::getline(std::cin, command);

    if (command == "play") {
        playbackQueue->playCurrentTrack();
    } else if (command == "next") {
        playbackQueue->playNextTrack();
    } else if (command == "prev") {
        playbackQueue->playPreviousTrack();
    } else if (command == "pause") {
        playbackQueue->pause();
    } else if (command == "loop") {
        playbackQueue->toggleLooping();
    } else if (command.rfind("seek ", 0) == 0) {
        try {
            float percentage = std::stof(command.substr(5));
            playbackQueue->seek(percentage);
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid seek command. Usage: seek <seconds>" << std::endl;
        }
    } else if (command == "exit") {
        std::cout << "Exiting application." << std::endl;
        exit(0);
    } else if (command == "playlist") {
        playlistPrinter.printQueue(*playbackQueue);
    } else if (command.rfind("volume ", 0) == 0) {
        try {
            float percentage = std::stof(command.substr(7));
            playbackQueue->setVolume(percentage * 0.01f);
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid volume command. Usage: volume <percentage>" << std::endl;
        }
    } else if (command.rfind("load ", 0) == 0) {
        std::string path = command.substr(5);
        // Here you would implement loading a new playlist from the specified path
        std::cout << "Loading playlist from: " << path << std::endl;
        // For example:
        // Playlist newPlaylist = loadPlaylistFromFile(path);
        repository->setDataFolderPath(path);
        playbackQueue->setPlaylist(repository->loadTracks());
    } else if (command == "help") {
        displayMenu();
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }
}
