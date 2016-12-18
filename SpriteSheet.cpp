//
// Created by Honzik on 16.12.16.
//

#include "SpriteSheet.h"

namespace JN {
    SpriteSheet::SpriteSheet() {
        //empty
    }

    SpriteSheet::~SpriteSheet() {
        //empty
    }

    void SpriteSheet::init(const GLTexture &texture, int columns, int rows) {
        _texture = texture;
        _columns = columns;
        _rows = rows;
    }

    glm::vec4 SpriteSheet::getUVs(int index) {

        int xTile = index % _columns;
        int yTile = index / _columns;

        glm::vec4 uvs;
        uvs.x =  xTile / (float)_columns;
        uvs.y =  yTile / (float) _rows;
        uvs.z = 1.0f / (float)_columns;
        uvs.w = 1.0f / (float)_rows;

        return  uvs;
    }


}