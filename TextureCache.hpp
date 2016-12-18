//
//  TextureCache.hpp
//  GameEngine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#ifndef TextureCache_hpp
#define TextureCache_hpp

#include <stdio.h>
#include "glTexture.h"
#include <map>
#include <string>

namespace JN {

class TextureCache {
    
private:
    std::map<std::string, GLTexture> _textureMap;
    
public:
    TextureCache();
    ~TextureCache();
    
    GLTexture getTexture(std::string texturePath);
    
    
};
}

#endif /* TextureCache_hpp */
