//
//  IGameScreen.hpp
//  JN
//
//  Created by Honzik on 07.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef IGameScreen_hpp
#define IGameScreen_hpp

#define SCREEN_INDEX_NO_SCREEN -1

namespace JN {
    
    enum class ScreenState {
        NONE,
        RUNNING,
        EXIT_APPLICATION,
        CHANGE_NEXT,
        CHANGE_PREVIOUS
    };


class IMainGame;
    
class IGameScreen {

protected:
    ScreenState _screenState = ScreenState::NONE;
    int _screenIndex = -1;
    IMainGame * _mainGame = nullptr;


public:
    friend class ScreenList;
    IGameScreen() {};
    virtual ~IGameScreen() {};
    
    virtual int getNextScreenIndex() const = 0;
    virtual int getPrevScreenIndex() const = 0;
    
    
    // creating and destroying screens
    virtual void build() = 0;
    virtual void destroy() = 0;
    // switch to and from screen;
    virtual void onEntry() = 0;
    virtual void onExit() = 0;
    // called from mainGame
    virtual void update() = 0;
    virtual void draw() = 0;
    
    void setRunning() { _screenState = ScreenState::RUNNING; }
    void setParrent(IMainGame * game) { _mainGame = game; }
    int getScreenIndex() const { return _screenIndex; }
    ScreenState getState() const { return _screenState; }
    
    
};
    
}


#endif /* IGameScreen_hpp */
