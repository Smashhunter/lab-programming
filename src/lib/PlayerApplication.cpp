#include "presentation/PlayerApplication.hpp"

PlayerApplication::PlayerApplication(AudioFactory *factory, TrackRepository *repository)
    : audioFactory(factory), trackRepository(repository)
{
    audioEngine = audioFactory->createAudioEngine();
    playbackQueue = new PlaybackQueue(audioEngine);
    consoleMenu = new ConsoleMenu(playbackQueue);
    playbackQueue->setPlaylist(trackRepository->loadTracks());
    audioEngine->addListener(playbackQueue);
}

void PlayerApplication::run()
{
    consoleMenu->displayMenu();
    playbackQueue->playCurrentTrack();
    while (isRunning)
    {        
        consoleMenu->handleUserInput(trackRepository);
    } 
}
