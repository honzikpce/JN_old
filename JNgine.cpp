//
//  JNgine.cpp
//  JNgine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "JNgine.hpp"
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <string>
#include "Errors.hpp"

namespace JN {
    
    void init(){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::string error = SDL_GetError();
            fatalError("Error initializing SDL! " + error);
        }
        
        // mac specific attribs
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetSwapInterval(1); // vertical sync
        
        
        
    }
    
    
}
