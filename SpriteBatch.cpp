//
//  SpriteBatch.cpp
//  JNgine
//
//  Created by Honzik on 13.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#include "SpriteBatch.hpp"
#include <cstddef> // offsetof
#include <algorithm>
#include <iostream>


namespace JN {
    
    void Glyph::rotatePoint(glm::vec2 &point, float angle) {
        float oldX = point.x;
        float oldY = point.y;
        point.x = oldX * cos(angle) -  oldY * sin(angle);
        point.y = oldX * sin(angle) +  oldY * cos(angle);
    }
    
    glm::vec2 Glyph::rotateDirection(glm::vec2 point, glm::vec2 direction){
        glm::vec2 baseVec = glm::vec2(0.0f, 1.0f);
        float angle = acos(glm::dot(baseVec, direction));
        if (direction.x > 0.0f) angle = - angle;
        rotatePoint(point, angle);
        return point;
    }
    
    Glyph::Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color)
    {
        _texture = texture;
        _depth = depth;
        
        
        _topLeft.color = color;
        _topLeft.setPosition(destRect.x, destRect.y + destRect.w);
        //_topLeft.setPosition(destRect.x - 0.5 * destRect.z, destRect.y + 0.5 * destRect.w);
        _topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
        
        _bottomLeft.color = color;
        _bottomLeft.setPosition(destRect.x, destRect.y);
        //_bottomLeft.setPosition(destRect.x - 0.5 * destRect.z, destRect.y - 0.5 * destRect.w);
        _bottomLeft.setUV(uvRect.x, uvRect.y);
        
        _bottomRight.color = color;
        _bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
        //_bottomRight.setPosition(destRect.x + 0.5 * destRect.z, destRect.y - 0.5 * destRect.w);
        _bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
        
        _topRight.color = color;
        _topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
        //_topRight.setPosition(destRect.x + 0.5 * destRect.z, destRect.y + 0.5 * destRect.w);
        _topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
        
    }
    
    Glyph::Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color, float angle){
        
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
        
        _texture = texture;
        _depth = depth;
        
        _topLeft.color = color;
        _topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
        //_topLeft.setPosition(destRect.x - 0.5 * destRect.z, destRect.y + 0.5 * destRect.w);
        _topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
        
        _bottomLeft.color = color;
        _bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
        //_bottomLeft.setPosition(destRect.x - 0.5 * destRect.z, destRect.y - 0.5 * destRect.w);
        _bottomLeft.setUV(uvRect.x, uvRect.y);
        
        _bottomRight.color = color;
        _bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
        //_bottomRight.setPosition(destRect.x + 0.5 * destRect.z, destRect.y - 0.5 * destRect.w);
        _bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
        
        _topRight.color = color;
        _topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
        //_topRight.setPosition(destRect.x + 0.5 * destRect.z, destRect.y + 0.5 * destRect.w);
        _topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
        
        //printf("Sprite Vertex 1 >> %f  :  %f\n", _topLeft.position.x, _topLeft.position.y);
        //printf("Sprite Vertex 2 >> %f  :  %f\n", _bottomLeft.position.x, _bottomLeft.position.y);
        //printf("Sprite Vertex 3 >> %f  :  %f\n", _bottomRight.position.x, _bottomRight.position.y);
        //printf("Sprite Vertex 4 >> %f  :  %f\n", _topRight.position.x, _topRight.position.y);
        
    }
    
    Glyph::~Glyph() {
        
    }
    
    
    SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
    {
        
    }
    
    void SpriteBatch::init(){
        createVertexArray();
    }
    
    SpriteBatch::~SpriteBatch(){
        if (_vbo != 0) glDeleteBuffers(1, &_vbo);
        if (_vao != 0) glDeleteBuffers(1, &_vao);
        
        
    }
    
    void SpriteBatch::begin(GlyphSortType sortType /* = TEXTURE*/){
        
        _sortType = sortType;
        _renderBatches.clear();
        _glyphs.clear();
    }
    
    void SpriteBatch::end(){
        // set the pointers for fast sorting
        _glyphsPointers.resize(_glyphs.size());
        for (int i=0; i < _glyphsPointers.size(); i++)
            _glyphsPointers[i] = &_glyphs[i];
        
        sortGlyphs();
        createRenderBatches();
        
    }
    
    void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color){
        _glyphs.emplace_back(destRect, uvRect, texture, depth, color);
        //Glyph::Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color, float angle)
    }
    
    void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture,float depth, const Color &color, float angle) {
        _glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
    }
    
    void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture,float depth, const Color &color, glm::vec2 direction) {
        glm::vec2 baseVec = glm::vec2(0.0f, 1.0f);
        //glm::vec2 dir = glm::normalize(direction);
        // compute angle between vecs
        float angle = acos(glm::dot(baseVec, direction));
        //std::cout << angle << std::endl;
        if (direction.x > 0.0f) angle = - angle;
        _glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
        
    }
    
    
    
    void SpriteBatch::renderBatch(){
        glBindVertexArray(_vao);
        for (int i = 0; i < _renderBatches.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
            glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
        }
        glBindVertexArray(0);
    }
    
    void SpriteBatch::createRenderBatches(){
        
        std::vector<Vertex> vertices;
        vertices.resize(_glyphs.size() * 6);
        if (_glyphs.empty())
            return;
        int offset = 0;
        int cv=0; // current vertex
        _renderBatches.emplace_back(offset, 6, _glyphs[0]._texture);
        vertices[cv++] = _glyphs[0]._topLeft;
        vertices[cv++] = _glyphs[0]._bottomLeft;
        vertices[cv++] = _glyphs[0]._bottomRight;
        vertices[cv++] = _glyphs[0]._bottomRight;
        vertices[cv++] = _glyphs[0]._topRight;
        vertices[cv++] = _glyphs[0]._topLeft;
        offset += 6;
        
        
        for (int cg = 1; cg < _glyphs.size(); cg++){
            if (_glyphs[cg]._texture != _glyphs[cg-1]._texture){
                _renderBatches.emplace_back(offset, 6, _glyphs[cg]._texture);
            }
            else {
                _renderBatches.back().numVertices += 6;
            }
            
            vertices[cv++] = _glyphs[cg]._topLeft;
            vertices[cv++] = _glyphs[cg]._bottomLeft;
            vertices[cv++] = _glyphs[cg]._bottomRight;
            vertices[cv++] = _glyphs[cg]._bottomRight;
            vertices[cv++] = _glyphs[cg]._topRight;
            vertices[cv++] = _glyphs[cg]._topLeft;
            offset += 6;
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void SpriteBatch::createVertexArray(){
        
        if (_vao == 0)
            glGenVertexArrays(1, &_vao);
        
        
        if (_vbo == 0)
            glGenBuffers(1, &_vbo);
        
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

        
        
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
        
        glBindVertexArray(0);
        
    }
    
     bool SpriteBatch::compareBackToFront(Glyph * a, Glyph * b){
        return (a->_depth < b->_depth);
    }
     bool SpriteBatch::compareFrontToBack(Glyph * a, Glyph * b){
        return (a->_depth > b->_depth);
    }
     bool SpriteBatch::compareTexture(Glyph * a, Glyph * b){
        return (a->_texture < b->_texture);
    }
    
    void SpriteBatch::sortGlyphs(){
        
        switch (_sortType) {
            case GlyphSortType::BACK_TO_FRONT:
                std::stable_sort(_glyphsPointers.begin(), _glyphsPointers.end(), compareBackToFront);
                break;
            case GlyphSortType::FRONT_TO_BACK:
                std::stable_sort(_glyphsPointers.begin(), _glyphsPointers.end(), compareFrontToBack);
                break;
            case GlyphSortType::TEXTURE:
                std::stable_sort(_glyphsPointers.begin(), _glyphsPointers.end(), compareTexture);
                break;
                
            default:
                break;
        }
        
    }
    
    
    
}
