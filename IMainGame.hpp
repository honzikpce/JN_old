//
//  IMainGame.hpp
//  JN
//
//  Created by Honzik on 06.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef IMainGame_hpp
#define IMainGame_hpp

#include <memory>
#include "Window.hpp"
#include "ScreenList.hpp"
#include "ControlManager.hpp"

namespace JN {

        
    class IMainGame {
    public:
        IMainGame();
        virtual ~IMainGame();
        
        void run();
        void exitGame();
        void onSDLEvent(SDL_Event& evnt);
        
        ControlManager * getControlManager() { return &_controlMngr; }
        
        virtual void onInit() = 0;
        virtual void addScreens() = 0;
        virtual void onExit() = 0;
        
        virtual void update();
        virtual void draw();
        
        
        
    protected:
        void init();
        void initSystems();
        
        
        ScreenList* _screenList;
        IGameScreen * _currentScreen = nullptr;
        bool _isRunning = false;
        float _fps = 0.0f;
        Window _window;
        ControlManager _controlMngr;
    };
}

#endif /* IMainGame_hpp */
