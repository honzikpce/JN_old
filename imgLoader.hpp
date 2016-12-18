//
//  imgLoader.hpp
//  GameEngine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#ifndef imgLoader_hpp
#define imgLoader_hpp



#include <stdio.h>
#include <string>
#include "glTexture.h"

namespace JN {

class ImageLoader {
    
    
public:
    static GLTexture loadPNG(std::string filePath);
};


}
#endif /* imgLoader_hpp */

