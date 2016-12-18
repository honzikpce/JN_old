//
//  Window.hpp
//  JNgine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <OpenGL/gl3.h>


enum WindowFlags {
    NO_OTHER_ATTRIB = 0,
    FULLSCREEN = 0x1,
    HIDDEN = 0x2,
    BORDERLESS = 0x4,
};

namespace JN {
    
    class Window {
        
    private:
        SDL_Window* _window;
        GLuint _defaultVAO;
    public:
        GLuint getDefaultVAO() { return _defaultVAO; }
        int create(std::string windowName, int width, int height, WindowFlags flags);
        void setBackgroundColor(float r, float g, float b, float a);
        void swapBuffers();
    };
    
    
    
}

#endif /* Window_hpp */
