//
//  AudioEngine.hpp
//  JNgine
//
//  Created by Honzik on 27.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef AudioEngine_hpp
#define AudioEngine_hpp

#include <stdio.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include <map>


namespace JN {
    
    
    class SoundEffect {
    public:
        friend class AudioEngine;
        void play(int loops = 0);
        
        
    private:
        Mix_Chunk * _chunk = nullptr;
        
    };
    
    class Music {
    public:
        static void stop();
        static void resume();
        static void pause();
        
        friend class AudioEngine;
        void play(int loops = -1);
        
        
    private:
        Mix_Music * _music = nullptr;
        
    };
    
    
    class AudioEngine {
    public:
        AudioEngine();
        ~AudioEngine();
        void init();
        void destroy();
        
        
        
        SoundEffect loadSoundEffect(const std::string &filePath);
        Music loadMusic(const std::string &filePath);
        
        
    private:
        bool _isInitialized = false;
        std::map<std::string, Mix_Chunk* > _effectMap;
        std::map<std::string, Mix_Music* > _musicMap;
    };
    
    
    
    
}



#endif /* AudioEngine_hpp */
