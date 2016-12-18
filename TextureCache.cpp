//
//  TextureCache.cpp
//  GameEngine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#include "TextureCache.hpp"
#include "imgLoader.hpp"
#include <iostream>


namespace JN {

TextureCache::TextureCache(){
    
}

TextureCache::~TextureCache(){
    
}


GLTexture TextureCache::getTexture(std::string texturePath){
    
    auto mapIterator = _textureMap.find(texturePath);
    if (mapIterator == _textureMap.end()) {
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);
        
        _textureMap.insert(std::make_pair(texturePath, newTexture));
        
        //std::cout << "Loading texture from file : " << texturePath << std::endl;
        return newTexture;
    }
    //std::cout << "Using cached texture : " << texturePath << std::endl;
    return mapIterator->second;
}
}
