#include "domain/PlaybackQueue.hpp"

PlaybackQueue::PlaybackQueue(AudioEngine *engine)
    : audioEngine(engine)
{
}

void PlaybackQueue::setPlaylist(const Playlist &newPlaylist)
{
    playlist = newPlaylist;
    currentTrackIndex = 0; // Start with the first track
    }

void PlaybackQueue::playCurrentTrack()
{
    const Track *currentTrack = getCurrentTrack();
    if (currentTrack){
        audioEngine->playTrack(currentTrack->getFilePath());
    } else {
    }
}

void PlaybackQueue::playNextTrack()
{
    if (currentTrackIndex + 1 < playlist.getTrackCount()){
        currentTrackIndex++;
        playCurrentTrack();
        
    } else {
        currentTrackIndex = 0; // Loop back to the first track
        playCurrentTrack();
    }
    
}

void PlaybackQueue::playPreviousTrack()
{
    if (currentTrackIndex > 0){
        currentTrackIndex--;
        playCurrentTrack();
    } else {
        currentTrackIndex = playlist.getTrackCount() - 1; // Loop back to the last track
        playCurrentTrack();
    }
}

void PlaybackQueue::pause()
{
    audioEngine->pause();
}

void PlaybackQueue::stop()
{
    audioEngine->stop();
}

void PlaybackQueue::toggleLooping()
{
    isLooping = !isLooping;
}

void PlaybackQueue::seek(float position)
{
    audioEngine->seek(position);
}

const Track *PlaybackQueue::getCurrentTrack() const
{
    return (currentTrackIndex >= 0 && currentTrackIndex < playlist.getTrackCount()) ? &playlist.getTracks()[currentTrackIndex] : nullptr;
}
const Playlist &PlaybackQueue::getPlaylist() const
{
    return playlist;
}

void PlaybackQueue::onTrackEnded()
{
    if (isLooping)
    {
        playCurrentTrack();
    }
    else
    {
        playNextTrack();
    }
}

void PlaybackQueue::setVolume(float volume)
{
    audioEngine->setVolume(volume);
}
