//
//  GLSLProgram.hpp
//  GameEngine
//
//  Created by Honzik on 11.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#ifndef GLSLProgram_hpp
#define GLSLProgram_hpp

#include <stdio.h>
#include <string>
#include <OpenGL/gl3.h>
#include "Errors.hpp"

namespace JN {

class GLSLProgram {
    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;
    int _attributesCount;
    
    void linkShaders();
    void compileShader(const std::string & ShaderFilePath, GLuint shaderID);

    
    
public:
    GLSLProgram();
    ~GLSLProgram();
    void compileShaders(const std::string & VertexShaderFilePath, const std::string & FragmentShaderFilePath);
    void addAttribute(const std::string &attributeName);
    void use();
    void unUse();
    GLint getUniformLocation(const char * uniformName);
};

}

#endif /* GLSLProgram_hpp */
