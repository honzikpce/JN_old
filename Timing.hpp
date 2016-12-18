//
//  Timing.hpp
//  JNgine
//
//  Created by Honzik on 14.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef Timing_hpp
#define Timing_hpp

#include <stdio.h>

namespace JN {
    
    class FpsLimiter {
    public:
        FpsLimiter(float maxFPS = 60.0);
        void beginFrame();
        float endFrame();
        
    private:
        float _maxFPS;
        float _fps;
        int _num_samples = 10;
        float _frameTimes[10];
        int _currentFrame;
        float _startTicks;
    };
}


#endif /* Timing_hpp */




