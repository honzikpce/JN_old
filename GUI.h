//
// Created by Honzik on 19.12.16.
//

#ifndef NINJA_GUI_H
#define NINJA_GUI_H

#include <Rocket/core.h>
#include <SDL_keycode.h>
#include "GUIRenderer.h"
#include "Camera2D.hpp"


namespace JN {

    class ControlManager;

    class GUI : public Rocket::Core::SystemInterface {

    public:
        float GetElapsedTime() override;

        void update(float elapsedTime);

        void init(Camera2D *camera, const char* contextName);

        void draw();

        void onKeyDown(const SDL_Keycode &key);

        void onKeyUp(const SDL_Keycode &key);

        void onMouseMove(const glm::vec2 &coords);

        Rocket::Core::ElementDocument * loadDocument(const char* filePath);


    private:
        Camera2D *_camera = nullptr;
        float _elapsedTime = 0;
        GUIRenderer *_renderer = nullptr;
        Rocket::Core::Context *_mainContext = nullptr;
        Rocket::Core::ElementDocument *_testDocument = nullptr;
        ControlManager * _controlMngr = nullptr;
    };

}
#endif //NINJA_GUI_H
