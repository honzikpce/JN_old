//
//  ResourceManager.hpp
//  GameEngine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <stdio.h>
#include "TextureCache.hpp"
#include <string>
#include "glTexture.h"

namespace JN {

class ResourceManager {

private:
    static TextureCache _textureCache;
    

    
public:
    static GLTexture getTexture(std::string texturePath);
};


}
#endif /* ResourceManager_hpp */
