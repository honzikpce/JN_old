//
//  Timing.cpp
//  JNgine
//
//  Created by Honzik on 14.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "Timing.hpp"
#include <SDL2/SDL.h>

namespace JN {
    
    FpsLimiter::FpsLimiter(float maxFPS):
    _maxFPS(maxFPS), _currentFrame(0)
    {

    }
    
    void FpsLimiter::beginFrame(){
        _startTicks = SDL_GetTicks();
    }
    
    float FpsLimiter::endFrame(){
        
        unsigned int currentTicks = SDL_GetTicks();
        
        unsigned int count;
        
        unsigned int frameTime = currentTicks - _startTicks;
        _frameTimes[_currentFrame % _num_samples] = frameTime;
        
        _startTicks = currentTicks;
        
        _currentFrame++;
        
        if (_currentFrame < _num_samples){
            count = _currentFrame;
        }
        else count = _num_samples;
        
        float frameTimeAverage = 0;
        for (int i=0; i < count; i++){
            frameTimeAverage += _frameTimes[i];
        }
        frameTimeAverage /= count;
        
        if (frameTimeAverage > 0) {
            _fps = 1000 / frameTimeAverage;
        }
        else _fps = _maxFPS;

        return _fps;
    }
}
