//
//  GLSLProgram.cpp
//  GameEngine
//
//  Created by Honzik on 11.11.16.
//  Copyright © 2016 Honzik. All rights reserved.
//

#include "GLSLProgram.hpp"
#include <fstream>
#include <vector>

namespace JN {

GLSLProgram::GLSLProgram():
_programID(0), _vertexShaderID(0), _fragmentShaderID(0), _attributesCount(0)
{
    
}

GLSLProgram::~GLSLProgram(){
    
}

void GLSLProgram::compileShaders(const std::string & VertexShaderFilePath, const std::string & FragmentShaderFilePath){
    
    _programID = glCreateProgram();
    if (_programID==0) fatalError("Creating shader program failed!");
    
    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (_vertexShaderID ==0) fatalError("Error creating vertex shader!");
    
    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (_fragmentShaderID ==0) fatalError("Error creating fragment shader!");

    compileShader(VertexShaderFilePath, _vertexShaderID);
    compileShader(FragmentShaderFilePath, _fragmentShaderID);
    
    linkShaders();
    
    glBindFragDataLocation(_programID, 0, "color");
    
    
}

void GLSLProgram::compileShader(const std::string &ShaderFilePath, GLuint shaderID){
    std::ifstream vertexFile(ShaderFilePath);
    if (vertexFile.fail()) {
        fatalError("Error opening file " + ShaderFilePath);
    }
    
    std::string fileContents = "";
    std::string line = "";
    
    while (std::getline(vertexFile, line)) {
        fileContents += line + "\n";
    }
    vertexFile.close();
    
    const char * contentsPtr = fileContents.c_str();
    glShaderSource(shaderID, 1, &contentsPtr, nullptr);
    glCompileShader(shaderID);
    
    GLint succes = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succes);
    
    if (!succes){
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
        glDeleteShader(shaderID);
        std::printf("%s\n", &errorLog[0]);
        fatalError("Shader failed to compile!");
    }
}


void GLSLProgram::linkShaders(){
    
    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);
    
    glLinkProgram(_programID);
    
    GLint succes = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, &succes);
    
    if (!succes){
        GLint maxLength = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);
        glDeleteProgram(_programID);
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
        
        std::printf("%s\n", &errorLog[0]);
        fatalError("GLSL program failed to link!");
    }
    
    glDetachShader(_programID, _vertexShaderID);
    glDetachShader(_programID, _fragmentShaderID);
    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
}


void GLSLProgram::addAttribute(const std::string &attributeName){
    glBindAttribLocation(_programID, _attributesCount++, attributeName.c_str());
}

GLint GLSLProgram::getUniformLocation(const char *uniformName){
    GLuint location = glGetUniformLocation(_programID, uniformName);
    if (location == GL_INVALID_INDEX) fatalError("Uniform location not found in shader!");
    return location;
    
}

void GLSLProgram::use(){
    glUseProgram(_programID);
    for (int i = 0; i < _attributesCount; i++){
        glEnableVertexAttribArray(i);
    }
}


void GLSLProgram::unUse(){
    glUseProgram(0);
    for (int i = 0; i < _attributesCount; i++){
        glDisableVertexAttribArray(i);
    }
}
}
