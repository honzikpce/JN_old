//
//  Errors.cpp
//  GameEngine
//
//  Created by Honzik on 10.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//




#include "Errors.hpp"
namespace JN {

void fatalError(std::string error) {
    std::cout << error << std::endl;
    SDL_Quit();
    exit(69);
}
}
