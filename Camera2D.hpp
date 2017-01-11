//
//  Camera2D.hpp
//  JNgine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef Camera2D_hpp
#define Camera2D_hpp

#include <stdio.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace JN {
    
    class Camera2D {
        
    public:
        Camera2D();
        void update();
        void init(int screenWidth, int screenHeight);
        
        void setPosition(glm::vec2  newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
        void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }
        void flipY() { _isYFlipped = !_isYFlipped; _needsMatrixUpdate = true; }
        
        
        glm::vec2 convertScreenToWorld(glm::vec2 coords);
        glm::vec2 getPosition() { return _position; }
        float getScale() { return _scale; }
        glm::mat4 getCameraMatrix() { return _cameraMatrix; }
        bool isBoxInView(glm::vec2 position, glm::vec2 dimensions);
        
    private:
        int _screenWidth;
        int _screenHeight;
        bool _needsMatrixUpdate;
        float _scale;
        bool _isYFlipped = false;
        glm::mat4 _cameraMatrix;
        glm::mat4 _orthoMatrix;
        glm::vec2 _position;
        
        
        
        
        
        
    };
    
    
    
}



#endif /* Camera2D_hpp */
