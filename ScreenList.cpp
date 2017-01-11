//
//  ScreenList.cpp
//  JN
//
//  Created by Honzik on 07.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "ScreenList.hpp"

namespace JN {
    
    ScreenList::ScreenList(IMainGame * mGame)
    :_mainGame(mGame)
    {
        
    }
    
    ScreenList::~ScreenList(){
        destroy();
    }
    
    IGameScreen * ScreenList::moveNext(){
        IGameScreen * currentScreen = getCurrent();
        if (currentScreen->getNextScreenIndex() != SCREEN_INDEX_NO_SCREEN){
            _currentScreenIndex = currentScreen->getNextScreenIndex();
        }
        return getCurrent();
    }
    
    IGameScreen * ScreenList::movePrevious(){
        IGameScreen * currentScreen = getCurrent();
        if (currentScreen->getPrevScreenIndex() != SCREEN_INDEX_NO_SCREEN){
            _currentScreenIndex = currentScreen->getPrevScreenIndex();
        }
        return getCurrent();
    }
    
    IGameScreen * ScreenList::getCurrent() {
        if (_currentScreenIndex == SCREEN_INDEX_NO_SCREEN) return nullptr;
        //printf("returning %d as _currentScreenIndex\n", _currentScreenIndex);
        return _screens[_currentScreenIndex];
    }
    
    void ScreenList::setScreen(int newScreen){
        _currentScreenIndex = newScreen;
    }
    
    void ScreenList::addScreen(IGameScreen * newScreen){
        _screens.push_back(newScreen);
        newScreen->_screenIndex = (int)_screens.size() - 1;
        newScreen->setParrent(_mainGame);
        newScreen->build();
    }
    
    void ScreenList::destroy(){
        for (int i = 0; i < _screens.size(); i++) {
            _screens[i]->destroy();
        }
        _screens.resize(0);
        _currentScreenIndex = SCREEN_INDEX_NO_SCREEN;
    }
    
    
}
