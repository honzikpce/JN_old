//
//  imgLoader.cpp
//  GameEngine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#include "imgLoader.hpp"

#include "picopng.h"
#include "Errors.hpp"
#include "IOManager.hpp"
#include <OpenGL/gl3.h>


namespace JN {

GLTexture ImageLoader::loadPNG(std::string filePath){
    GLTexture texture = {};
    
     
     
     std::vector<unsigned char> out;
     unsigned long width, height;
     
     std::vector<unsigned char> in;
     if (!IOManager::readFileToBuffer(filePath, in))
     fatalError("Failed to load PNG file to buffer!");
     
     
     int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
     
     if (errorCode != 0) fatalError("Failed to decode PNG file!" + std::to_string(errorCode));
     
     
     glGenTextures(1, &(texture.id));
     glBindTexture(GL_TEXTURE_2D, texture.id);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLint)width, (GLint)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
     
     glGenerateMipmap(GL_TEXTURE_2D);
     glBindTexture(GL_TEXTURE_2D, 0);
     
     texture.widht = (int)width;
     texture.height = (int)height;
    
    return texture;
}
}
