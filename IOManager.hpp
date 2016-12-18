//
//  IOManager.hpp
//  GameEngine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#ifndef IOManager_hpp
#define IOManager_hpp

#include <stdio.h>
#include <vector>
#include <string>

namespace JN {

class IOManager {
    
    
public:
    static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
};



}




#endif /* IOManager_hpp */
