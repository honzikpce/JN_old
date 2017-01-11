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
#include "GUI.h"

namespace JN {

    class ControlManager {
    
    public :
        void pressKey(uint32_t key);
        void releaseKey(uint32_t key);
        //bool getKeyState(uint32_t key);
        
        bool isKeyPressed(uint32_t key);
        bool isKeyDown(uint32_t key);
        bool isMouseDragging();
        bool isMouseDragged();
        bool isMouseClicked();
        bool isDragFinished();
        
        void update();
        void attachGui(GUI * gui);
        
        void setMouseCoords(float x, float y);
        glm::vec2 getMouseCoords() { return _mouseCoords; }
        glm::vec2 getDragStartCoords();
        
    private:
        std::unordered_map<uint32_t, bool> _keyMap;
        std::unordered_map<uint32_t, bool> _previousKeyMap;
        glm::vec2 _mouseCoords;
        bool _isMouseDown = false;
        bool _dragStarted = false;
        bool _mouseClicked = false;
        glm::vec2 _lastClickCoords = glm::vec2();
        bool _isMouseDragging = false;
        GUI * _gui = nullptr;
        
    };
    
    
}


#endif /* ControlManager_hpp */
