//
// Created by Honzik on 19.12.16.
//


#include "GUI.h"

namespace JN {

    float GUI::GetElapsedTime() {
        return 0;
    }

    void GUI::update(float elapsedTime) {
        _elapsedTime = elapsedTime;


        _mainContext->Update();


    }


    void GUI::init(Camera2D *camera, const char* contextName) {

        _camera = camera;

        // set system and render interfaces
        Rocket::Core::SetSystemInterface(this);
        _renderer = new GUIRenderer();
        _renderer->init(camera);
        Rocket::Core::SetRenderInterface(_renderer);

        // init system
        Rocket::Core::Initialise();

        // create context
        _mainContext = Rocket::Core::CreateContext(contextName, Rocket::Core::Vector2i(800, 600));

        // load fonts
        Rocket::Core::String font_names[4];
        font_names[0] = "Delicious-Roman.otf";
        font_names[1] = "Delicious-Italic.otf";
        font_names[2] = "Delicious-Bold.otf";
        font_names[3] = "Delicious-BoldItalic.otf";

        for (int i = 0; i < sizeof(font_names) / sizeof(Rocket::Core::String); i++) {
            Rocket::Core::FontDatabase::LoadFontFace(Rocket::Core::String("../gui-assets/") + font_names[i]);

        }


    }

    void GUI::onKeyDown(const SDL_Keycode &key) {
        //Rocket::Core::Input::KeyIdentifier rocketKey = nullptr;

        switch (key) {
            case SDL_BUTTON_LEFT :
                _mainContext->ProcessMouseButtonDown(0, 0);
                return;
            case SDL_BUTTON_RIGHT :
                _mainContext->ProcessMouseButtonDown(1, 0);
                return;
            default: break;
            // TODO: KEYS
        }
    }

    void GUI::onKeyUp(const SDL_Keycode &key) {
        switch (key) {
            case SDL_BUTTON_LEFT :
                _mainContext->ProcessMouseButtonUp(0, 0);
                printf("left-click\n");
                return;
            case SDL_BUTTON_RIGHT :
                _mainContext->ProcessMouseButtonUp(1, 0);
                printf("left-click\n");
                return;
            default: break;
                // TODO: KEYS
        }
    }

    void GUI::onMouseMove(const glm::vec2 &coords) {
        glm::vec2 worldCoords = _camera->convertScreenToWorld(coords);
        //printf("mouse move >>> %f : %f\n", worldCoords.x, worldCoords.y);
        _mainContext->ProcessMouseMove((int) worldCoords.x, (int) worldCoords.y, 0); ///< not dealing with modifiers now
    }

    void GUI::draw() {
        _mainContext->Render();
    }

    Rocket::Core::ElementDocument * GUI::loadDocument(const char* filePath) {
        Rocket::Core::ElementDocument * loadedDoc = _mainContext->LoadDocument(Rocket::Core::String(filePath));
        if (loadedDoc != nullptr) {
            return loadedDoc;
        } else {
            fatalError("Error loading GUI document!");
        }
        return nullptr;
    }
}