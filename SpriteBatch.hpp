//
//  SpriteBatch.hpp
//  JNgine
//
//  Created by Honzik on 13.11.16.
//  Copyright © 2016 Jan Novak. All rights reserved.
//

#ifndef SpriteBatch_hpp
#define SpriteBatch_hpp

#include <OpenGL/gl3.h>
#include "Vertex.h"
#include "glm/glm.hpp"
#include <vector>

namespace JN {
    
    enum class GlyphSortType {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE
    };
    
    class Glyph {
    private:
        
        
    public:
        static void rotatePoint(glm::vec2 &point, float angle);
        static glm::vec2 rotateDirection(glm::vec2 point, glm::vec2 direction);
        
        GLuint _texture;
        float _depth;
        
        Vertex _topLeft;
        Vertex _bottomLeft;
        Vertex _topRight;
        Vertex _bottomRight;
        
        Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color);
        Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color, float angle);
        ~Glyph();
    };
    
    
    class RenderBatch {
    public:
        RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture){
            
        }
        GLuint offset;
        GLuint numVertices;
        GLuint texture;
    };
    
    class SpriteBatch {
    
    private:
        GLuint _vbo;
        GLuint _vao;
        GlyphSortType _sortType;
        
        std::vector<Glyph> _glyphs;
        std::vector<Glyph *> _glyphsPointers;
        
        void createVertexArray();
        void sortGlyphs();
        void createRenderBatches();
    
        static bool compareBackToFront(Glyph * a, Glyph * b);
        static bool compareFrontToBack(Glyph * a, Glyph * b);
        static bool compareTexture(Glyph * a, Glyph * b);
        std::vector<RenderBatch> _renderBatches;
        
        
    public:
        SpriteBatch();
        ~SpriteBatch();
        void init();
        void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
        void end();
        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture,float depth, const Color &color);
        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture,float depth, const Color &color, float angle);
        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture,float depth, const Color &color, glm::vec2 direction);
        void renderBatch();
        
        
    };
}


#endif /* SpriteBatch_hpp */
