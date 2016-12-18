//
// Created by Honzik on 16.12.16.
//

#ifndef JN_SPRITESHEET_H
#define JN_SPRITESHEET_H

#include <glm/vec4.hpp>
#include "glTexture.h"

namespace JN {
    class SpriteSheet {
    public:
        SpriteSheet();
        ~SpriteSheet();

        void init(const GLTexture &texture, int columns, int rows);
        glm::vec4 getUVs(int index);

    private:
        int _columns = 0;
        int _rows = 0;
        GLTexture _texture;
    };

}

#endif //JN_SPRITESHEET_H
