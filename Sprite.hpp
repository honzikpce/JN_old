//
//  Sprite.hpp
//  GameEngine
//
//  Created by Honzik on 10.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>
#include "Vertex.h"
#include "Errors.hpp"
#include <cstddef> // offsetof
#include "glTexture.h"

namespace JN {

class Sprite {
    float _x;
    float _y;
    float _width;
    float _height;
    GLuint _vboID;
    GLTexture _texture;
    
public:
    void init(float x, float y, float width, float height, std::string texturePath);
    void draw();
    ~Sprite();
    
};

}
#endif /* Sprite_hpp */
