//
//  ControlManager.cpp
//  JNgine
//
//  Created by Honzik on 14.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "ControlManager.hpp"

namespace JN {
    
    void ControlManager::pressKey(uint32_t key){
        _keyMap[key] = true;
    }
    
    
    void ControlManager::releaseKey(uint32_t key){
        _keyMap[key] = false;
    }
    /*
    bool ControlManager::getKeyState(uint32_t key){
        auto result = _keyMap.find(key);
        if (result != _keyMap.end()) {
            return  result->second;
        }
        return false;
    }
    */
    
    void ControlManager::update() {
        for (auto& record : _keyMap) {
            _previousKeyMap[record.first] = record.second;
        }
    }
    
    bool ControlManager::isKeyPressed(uint32_t key) {
        auto result = _keyMap.find(key);
        if (result != _keyMap.end()) {
            return  result->second && !_previousKeyMap[key];
        }
        return false;
    }
    
    bool ControlManager::isKeyDown(uint32_t key){
        auto result = _keyMap.find(key);
        if (result != _keyMap.end()) {
            return  result->second;
        }
        return false;
    }
    
    void ControlManager::setMouseCoords(float x, float y){
        _mouseCoords.x = x;
        _mouseCoords.y = y;
    }
    
    
    
}
