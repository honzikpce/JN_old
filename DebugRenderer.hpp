//
//  DebugRenderer.hpp
//  JN
//
//  Created by Honzik on 11.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef DebugRenderer_hpp
#define DebugRenderer_hpp

#include "GLSLProgram.hpp"
#include <OpenGL/gl3.h>
#include "Vertex.h"
#include "glm/glm.hpp"
#include "Camera2D.hpp"
#include <vector>

namespace JN {
    
    class DebugRenderer {
    
        struct DebugVertex {
            glm::vec2 position;
            Color color;
        };
        
        
    public:
        DebugRenderer();
        ~DebugRenderer();
        
        void init();
        void end();
        void drawRectangle(glm::vec4 destRect, float angle, Color color);
        void drawCircle(glm::vec2 center, float radius, Color color);
        
        //void killBug();
        
        void render(const glm::mat4 &projection, float thickness);
        
        void dispose();
        
    private:
        GLuint _vbo, _vao, _iao;
        GLSLProgram _program;
        std::vector<DebugVertex> _verts;
        std::vector<GLuint> _indices;
        int _numElements = 0;
    };
    
    
    
}

#endif /* DebugRenderer_hpp */
