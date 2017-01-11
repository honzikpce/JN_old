//
//  Camera2D.cpp
//  JNgine
//
//  Created by Honzik on 12.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "Camera2D.hpp"
namespace JN {
 
    Camera2D::Camera2D():_scale(1.0f),_cameraMatrix(1.0f),_orthoMatrix(1.0f),_position(0.0f,0.0f),_screenWidth(500),_screenHeight(500),_needsMatrixUpdate(true)
    {
        
    }
    
    void Camera2D::init(int screenWidth, int screenHeight){
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        _orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
        
        
        
    }
    
    void Camera2D::update(){
        if (_needsMatrixUpdate){
            glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
            _cameraMatrix = glm::translate(_orthoMatrix, translate);

            glm::vec3 scale(_scale, _isYFlipped ? (-_scale) : (_scale), 0.0f);
            _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
            
            _needsMatrixUpdate = false;
        }
    }
    
    glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 coords){
        
        // invert y axis
        if (!_isYFlipped) coords.y = _screenHeight - coords.y;
        
        coords -= glm::vec2(_screenWidth/2, _screenHeight/2);
        
        coords /= _scale;
        coords += _position;
        
        return coords;
    }
    
    bool Camera2D::isBoxInView(glm::vec2 position, glm::vec2 dimensions) {
        glm::vec2 scaledScreenDims = glm::vec2(_screenWidth, _screenHeight) / _scale;
        
        const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDims.x / 2;
        const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDims.y / 2;
        
        
        glm::vec2 boxCenter = position + dimensions / 2.0f;
        
        // vector between camera center and box center
        glm::vec2 distance = _position - boxCenter;
        
        float xDepth = MIN_DISTANCE_X - std::abs(distance.x);
        float yDepth = MIN_DISTANCE_Y - std::abs(distance.y);
        
        if (xDepth > 0 && yDepth > 0)
            return true; ///< we have a collision!
        return false;
    }
    
}
