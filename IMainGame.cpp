//
//  IMainGame.cpp
//  JN
//
//  Created by Honzik on 06.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "IMainGame.hpp"
#include "JNgine.hpp"
#include "Timing.hpp"

namespace JN {


IMainGame::IMainGame() {
    
}

IMainGame::~IMainGame() {
    
}
    
    void IMainGame::init() {
        JN::init();
        initSystems();
        onInit();
        _screenList = new ScreenList(this);
        addScreens();
        
        _currentScreen = _screenList->getCurrent();
        if (_currentScreen == nullptr) printf("WTF ? currentscreen is nullptr!");
        _currentScreen->onEntry();
        _currentScreen->setRunning();
    }
    
    void IMainGame::initSystems() {
        _window.create("defaultWindow", 800, 600, WindowFlags::NO_OTHER_ATTRIB);
        
    }

    void IMainGame::onSDLEvent(SDL_Event& evnt){
        switch (evnt.type) {
            case SDL_QUIT:
                _isRunning = false;
                break;
            case SDL_KEYDOWN:
                _controlMngr.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _controlMngr.releaseKey(evnt.key.keysym.sym);
            case SDL_MOUSEBUTTONDOWN:
                _controlMngr.pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _controlMngr.releaseKey(evnt.button.button);
                break;
            case SDL_MOUSEMOTION:
                _controlMngr.setMouseCoords(evnt.motion.x, evnt.motion.y);

            default:
                break;
        }
    }
    
    void IMainGame::run() {
        
        init();
        
        _isRunning = true;
        FpsLimiter fpsLimiter(60.0f);
        while (_isRunning) {
            fpsLimiter.beginFrame();
            
            _controlMngr.update();
            
            update();

            draw();
            
            _fps = fpsLimiter.endFrame();
        }
        exitGame();
        
    }
    
    void IMainGame::update() {
        if (_currentScreen) {
            switch (_currentScreen->getState()) {
                case ScreenState::RUNNING:
                    _currentScreen->update();
                    break;
                case ScreenState::CHANGE_NEXT:
                    _currentScreen->onExit();
                    _currentScreen = _screenList->moveNext();
                    if (_currentScreen) {
                        _currentScreen->setRunning();
                        _currentScreen->onEntry();
                    }
                    break;
                case ScreenState::CHANGE_PREVIOUS:
                    _currentScreen->onExit();
                    _currentScreen = _screenList->movePrevious();
                    if (_currentScreen) {
                        _currentScreen->setRunning();
                        _currentScreen->onEntry();
                    }
                    break;
                case ScreenState::EXIT_APPLICATION:
                    _isRunning = false;
                    break;
                default:
                    break;
            }
        }
        else _isRunning = false; ///< if no current screen
    }
    
    void IMainGame::draw() {
        if (_currentScreen && _currentScreen->getState() == ScreenState::RUNNING)
            _currentScreen->draw();
        _window.swapBuffers();
    }
    

    
    void IMainGame::exitGame() {
        _isRunning = false;
        if (_screenList) {
            _currentScreen->onExit();
            _screenList->destroy();
            delete _screenList;
        }
        onExit();
        SDL_Quit();
    }


}
