//
//  Window.cpp
//  JNgine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "Window.hpp"
#include "Errors.hpp"


namespace JN {
    
    int Window::create(std::string windowName, int width, int height, WindowFlags flags){
        
        Uint32 sdlFlags = SDL_WINDOW_OPENGL;
        if (flags & FULLSCREEN) sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        if (flags & HIDDEN) sdlFlags |= SDL_WINDOW_HIDDEN;
        if (flags & BORDERLESS) sdlFlags |= SDL_WINDOW_BORDERLESS;
        
        
        _window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, sdlFlags);
        if (_window == nullptr)
        fatalError("Error creating OpenGL window!");
        
        SDL_GLContext glContext = SDL_GL_CreateContext(_window);
        if (glContext == nullptr){
            fatalError(std::string(SDL_GetError()) + "Error creating OpenGL context!");
        }
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        // MacOsX fix
        
        glGenVertexArrays(1, &_defaultVAO);
        glBindVertexArray(_defaultVAO);
        
        
        

        std::printf("*** Running OpenGL version %s ***\n", glGetString(GL_VERSION));
        return 0;
    }
    
    void Window::setBackgroundColor(float r, float g, float b, float a){
        glClearColor(r, g, b, a);
    }
    
    void Window::swapBuffers(){
        SDL_GL_SwapWindow(_window);
    }
    
    
    
    
    

}
