#pragma once

#include <string>
#include "domain/Playlist.hpp"
#include "domain/AudioEngine.hpp"
#include "domain/Track.hpp"

class PlaybackQueue: public AudioEngineListener
{
private:
    Playlist playlist;
    AudioEngine* audioEngine;
    int currentTrackIndex = -1; // -1 indicates no track is currently playing
    bool isPaused = false;
    bool isLooping = false;
public:
    PlaybackQueue(AudioEngine* engine);
    void setPlaylist(const Playlist& newPlaylist);
    void playCurrentTrack();
    void playNextTrack();
    void playPreviousTrack();
    void pause();
    void stop();
    void toggleLooping();
    void seek(float position); // Position in seconds
    const Track* getCurrentTrack() const;
    const Playlist& getPlaylist() const;
    void onTrackEnded() override;
    void setVolume(float volume);
    
};
