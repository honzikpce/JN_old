//
//  ResourceManager.cpp
//  GameEngine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#include "ResourceManager.hpp"

namespace JN {


TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(std::string texturePath){
    return _textureCache.getTexture(texturePath);
}

}
