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
        if (key == SDL_BUTTON_LEFT) {
            _isMouseDown = true;
            _lastClickCoords = _mouseCoords;
        }
    }
    
    
    void ControlManager::releaseKey(uint32_t key){
        _keyMap[key] = false;
        if (key == SDL_BUTTON_LEFT) {
            _isMouseDown = false;
            if (_mouseCoords == _lastClickCoords) _mouseClicked = true;
        }
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
        _mouseClicked = false;
        for (auto& record : _keyMap) {
            if (_gui != nullptr) {
                // send messages to gui
                auto result = _previousKeyMap.find(record.first);
                if (result != _keyMap.end() && (_previousKeyMap[record.first] != _keyMap[record.first])) {
                    // change of key state has just happend
                    if (_keyMap[record.first]) {
                        // key pressed
                        _gui->onKeyDown(record.first);
                    }
                    else {
                        // key released
                        _gui->onKeyUp(record.first);
                    }
                }
            }
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

        if (_isMouseDown && (fabsf(_lastClickCoords.x - x) > 3.0f || fabsf(_lastClickCoords.y - y) > 3.0f)) {
            if (!_isMouseDragging) _dragStarted = true;
            else _dragStarted = false;

            _isMouseDragging = true;
        }
        else _isMouseDragging = false;

            _mouseCoords.x = x;
            _mouseCoords.y = y;

            if (_gui != nullptr) {
                _gui->onMouseMove(glm::vec2(x, y));
            }
    }

    void ControlManager::attachGui(GUI *gui) {
        _gui = gui;

    }

    bool ControlManager::isMouseDragging() {
        return _isMouseDragging;
    }

    bool ControlManager::isMouseDragged() {
        return _dragStarted;
    }

    glm::vec2 ControlManager::getDragStartCoords() {
        if (_isMouseDragging){
            return _lastClickCoords;
        }
        else return glm::vec2();
    }

    bool ControlManager::isMouseClicked() {
        return _mouseClicked;
    }

    bool ControlManager::isDragFinished() {
        // _isMouseDragging is being reset in update method
        return _isMouseDragging && !isKeyDown(SDL_BUTTON_LEFT);
    }

}
