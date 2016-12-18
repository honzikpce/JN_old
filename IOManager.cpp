//
//  IOManager.cpp
//  GameEngine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#include "IOManager.hpp"
#include <fstream>
#include <iostream>

namespace JN {

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer){
    std::ifstream file(filePath, std::ios::binary);
    if (file.fail()) {
        perror(filePath.c_str());
        return false;
    }
    file.seekg(0, file.end);
    
    int fileSize = (int)file.tellg();
    
    file.seekg(0, file.beg);
    
    buffer.resize(fileSize);
    
    std::cout << buffer.size() << " - size of buffer.\n";
    file.read((char *)&buffer[0], fileSize);
    
    file.close();
    return true;
}

}
