//
//  ScreenList.hpp
//  JN
//
//  Created by Honzik on 07.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef ScreenList_hpp
#define ScreenList_hpp



#include <vector>
#include "IGameScreen.hpp"

namespace JN {

    class IMainGame;
    
    class ScreenList {
    public :
        ScreenList(IMainGame * mGame);
        ~ScreenList();
        
        IGameScreen * moveNext();
        IGameScreen * movePrevious();
        IGameScreen * getCurrent();
        
        void addScreen(IGameScreen * newScreen);
        void setScreen(int newScreen);
        
        void destroy();
        
    
    protected:
        std::vector<IGameScreen *> _screens;
        int _currentScreenIndex = -1;
        IMainGame * _mainGame = nullptr;
        
        
    };
    
    
    
}

#endif /* ScreenList_hpp */
