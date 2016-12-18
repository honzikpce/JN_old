//
//  DebugRenderer.cpp
//  JN
//
//  Created by Honzik on 11.12.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "DebugRenderer.hpp"

namespace JN {
    DebugRenderer::DebugRenderer()
    :_vao(0), _vbo(0), _iao(0)
    {
        
    }
    
    
    void DebugRenderer::init() {
        
        // generate buffers
        if (_vao == 0)
            glGenVertexArrays(1, &_vao);
        
        if (_vbo == 0)
            glGenBuffers(1, &_vbo);
        
        if (_iao == 0)
            glGenBuffers(1, &_iao);
        
        // init shaders
        _program.addAttribute("vertexPosition");
        _program.addAttribute("vertexColor");
        
        _program.compileShaders("shaders/debug.vert", "shaders/debug.frag");
        
        // binding buffers
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        
        
        
        
        // set data pointers
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void *)offsetof(DebugVertex, position));
        
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void *)offsetof(DebugVertex, color));
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iao);
        
        glBindVertexArray(0);
    }
    
    
    void DebugRenderer::end() {
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        // orphan buffer and upload vertex data
        glBufferData(GL_ARRAY_BUFFER, _verts.size() * sizeof(DebugVertex) , nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, _verts.size() * sizeof(DebugVertex), _verts.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iao);
        // upload indices
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint) , nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, _indices.size() * sizeof(GLuint), _indices.data());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        _numElements = (int)_indices.size();
        _indices.clear();
        _verts.clear();
        
    }
    
    void rotatePoint(glm::vec2 &point, float angle) {
        float oldX = point.x;
        float oldY = point.y;
        point.x = oldX * cos(angle) -  oldY * sin(angle);
        point.y = oldX * sin(angle) +  oldY * cos(angle);
    }

    
    void DebugRenderer::drawRectangle(glm::vec4 destRect, float angle, Color color) {
        int start = (int)_verts.size();
        // allocate vector for additional verts
        _verts.resize(start + 4);
        
        glm::vec2 halfVec(destRect.z / 2.0f, destRect.w / 2.0f);
        
        glm::vec2 tl(-halfVec.x, halfVec.y);
        glm::vec2 tr(halfVec.x, halfVec.y);
        glm::vec2 bl(-halfVec.x, -halfVec.y);
        glm::vec2 br(halfVec.x, -halfVec.y);
        
        rotatePoint(tl, angle);
        rotatePoint(tr, angle);
        rotatePoint(bl, angle);
        rotatePoint(br, angle);
        
        
        tl += halfVec;
        tr += halfVec;
        bl += halfVec;
        br += halfVec;
        
        
        _verts[start].color = color;
        _verts[start].position = glm::vec2(destRect.x + tl.x, destRect.y + tl.y);
        
        _verts[start + 1].color = color;
        _verts[start + 1].position = glm::vec2(destRect.x + bl.x, destRect.y + bl.y);
        
        _verts[start + 2].color = color;
        _verts[start + 2].position = glm::vec2(destRect.x + br.x, destRect.y + br.y);
        
        _verts[start + 3].color = color;
        _verts[start + 3].position = glm::vec2(destRect.x + tr.x, destRect.y + tr.y);


        // describe lines between vertices

        _indices.reserve(8);
        for (int i = 0; i < 3; i++) {
            _indices.push_back(start + i);
            _indices.push_back(start + i + 1);
        }
        _indices.push_back(start + 3);
        _indices.push_back(start);
        
        
    }
    
    void DebugRenderer::drawCircle(glm::vec2 center, float radius, Color color) {
        float pi = 22 / 7.0f;
        int numCircleVerts = 100;
        int start = (int)_verts.size();
        // allocate vector for additional verts
        _verts.resize(start + numCircleVerts);

        for (int i = 0; i < numCircleVerts - 1; i++) {
            _verts[start + i].position =
                    glm::vec2(
                            center.x + sinf(pi * i * 2.0f / numCircleVerts) * radius,
                            center.y + cosf(pi * i * 2.0f / numCircleVerts) * radius);
            _indices.push_back(start + i);
            _indices.push_back(start + i + 1);
        }
        _verts[start + numCircleVerts - 1].position =
                glm::vec2(
                        center.x + sinf(pi * start + numCircleVerts - 1 * 2.0f / numCircleVerts) * radius,
                        center.y + cosf(pi * start + numCircleVerts - 1 * 2.0f / numCircleVerts) * radius);
        _indices.push_back(start + numCircleVerts - 1);
        _indices.push_back(start);
    }
    
    void DebugRenderer::render(const glm::mat4 &projection, float thickness) {
        
        
        _program.use();
        
        //upload uniforms to shaders
        GLuint camLoc = _program.getUniformLocation("P");
        glUniformMatrix4fv(camLoc, 1, GL_FALSE, &projection[0][0]);

        
        
        
        glLineWidth(thickness);
        
        glBindVertexArray(_vao);// render stuff
        glDrawElements(GL_LINES, _numElements, GL_UNSIGNED_INT, 0);
        // rendering done - unbinding everything...
        glBindVertexArray(0);
        _program.unUse();
        
        
    }
    
    void DebugRenderer::dispose() {
        // delete buffers
        if (_vbo != 0) glDeleteBuffers(1, &_vbo);
        if (_iao != 0) glDeleteBuffers(1, &_iao);
        if (_vao != 0) glDeleteVertexArrays(1, &_vao);
        _indices.clear();
        _verts.clear();
    }
    
    DebugRenderer::~DebugRenderer() {
        
    }
    
}
