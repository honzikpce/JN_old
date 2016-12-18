//
//  Vertex.h
//  GameEngine
//
//  Created by Honzik on 10.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#ifndef Vertex_h
#define Vertex_h


#include <OpenGL/gl3.h>

namespace JN {

struct Color {
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
    
    // defaults to white
    Color () : r(255), g(255), b(255), a(255) {}
    
    // set to defined params
    Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A) {
        r = R;
        g = G;
        b = B;
        a = A;
    }
};

struct Position {
    GLfloat x;
    GLfloat y;
};

struct UV {
    float u;
    float v;
};

struct Vertex {
    Position position;
    Color color;
    UV uv;
    
    void setColor(GLuint r, GLuint g, GLuint b, GLuint a){
        color.a = a;
        color.r = r;
        color.g = g;
        color.b = b;
    }
    void setUV(float u, float v){
        uv.u = u;
        uv.v = v;
    }
    
    void setPosition(float x, float y){
        position.x = x;
        position.y = y;
    }

    };

}


#endif /* Vertex_h */
