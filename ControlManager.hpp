//
//  ControlManager.hpp
//  JNgine
//
//  Created by Honzik on 14.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef ControlManager_hpp
#define ControlManager_hpp

#include <stdio.h>
#include <unordered_map>
#include "glm/glm.hpp"

namespace JN {
    
    class ControlManager {
    
    public :
        void pressKey(uint32_t key);
        void releaseKey(uint32_t key);
        //bool getKeyState(uint32_t key);
        
        bool isKeyPressed(uint32_t key);
        bool isKeyDown(uint32_t key);
        
        void update();
        
        void setMouseCoords(float x, float y);
        glm::vec2 getMouseCoords() { return _mouseCoords; }
        
    private:
        std::unordered_map<uint32_t, bool> _keyMap;
        std::unordered_map<uint32_t, bool> _previousKeyMap;
        glm::vec2 _mouseCoords;
        
        
        
    };
    
    
}


#endif /* ControlManager_hpp */
