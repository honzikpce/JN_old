//
//  AudioEngine.cpp
//  JNgine
//
//  Created by Honzik on 27.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "AudioEngine.hpp"
#include "Errors.hpp"

namespace JN {

    
    void SoundEffect::play(int loops) {
        if (Mix_PlayChannel(-1, _chunk, loops) == -1)
            fatalError("Sound Effect failed to play! " + std::string(Mix_GetError()));
    }
    
    void Music::play(int loops) {
        if (Mix_PlayMusic(_music, loops) == -1)
            fatalError("Music failed to play! " + std::string(Mix_GetError()));

    }
    
    void Music::stop() {
        Mix_HaltMusic();
    }
    
    void Music::resume() {
        Mix_ResumeMusic();
    }
    
    void Music::pause() {
        Mix_PauseMusic();
    }
    
    
    AudioEngine::AudioEngine() {
        ///< empty
    }
    AudioEngine::~AudioEngine() {
        destroy();
    }
    
    void AudioEngine::init(){
        
        if (Mix_Init(MIX_InitFlags::MIX_INIT_OGG | MIX_InitFlags::MIX_INIT_MP3) == -1)
            fatalError("Audio Mixer init failuire! " + std::string(Mix_GetError()));
        
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == - 1)
            fatalError("Audio Mixer init failuire! " + std::string(Mix_GetError()));
        _isInitialized = true;
    }
    
    void AudioEngine::destroy(){
        if (_isInitialized) {
            _isInitialized = false;
            Mix_Quit();
        }
    }
    
    
    SoundEffect AudioEngine::loadSoundEffect(const std::string &filePath){
        
        SoundEffect effect;
        
        auto it = _effectMap.find(filePath);
        if (it == _effectMap.end()){
            // effect not found, need to load from file
            Mix_Chunk * chunk = Mix_LoadWAV(filePath.c_str());
            if (chunk == nullptr) fatalError("Error loading sound effect file! " + std::string(Mix_GetError()));
            _effectMap[filePath] = chunk;
            effect._chunk = chunk; ///< setting private var through friend
        }
        else {
            // effect found, just return the cached resource
            effect._chunk = it->second;
        }
        return effect;
    }
    
    Music AudioEngine::loadMusic(const std::string &filePath) {
        Music music;
        
        auto it = _musicMap.find(filePath);
        if (it == _musicMap.end()){
            // effect not found, need to load from file
            Mix_Music * mus = Mix_LoadMUS(filePath.c_str());
            if (mus == nullptr) fatalError("Error loading music file! " + std::string(Mix_GetError()));
            _musicMap[filePath] = mus;
            music._music = mus; ///< setting private var through friend
        }
        else {
            // effect found, just return the cached resource
            music._music = it->second;
        }
        return music;
        
    }
    

    
    
    
}
