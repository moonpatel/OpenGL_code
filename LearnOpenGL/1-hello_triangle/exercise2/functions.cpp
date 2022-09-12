#include <iostream>
#include "functions.h"

bool isShaderCompiled(GLuint shader) {
    int success;
    char infoLog[1024];

    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success) {
        glGetShaderInfoLog(shader,1024,NULL,infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FALIED" << infoLog << std::endl;
        return false;
    }
    else return true;
}

bool isShaderProgramLinked(GLuint shaderProgram) {
    int success;
    char infoLog[1024];

    glGetShaderiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram,1024,NULL,infoLog);
        std::cout << "ERROR::SHADER::LINKING_FALIED" << infoLog << std::endl;
        return false;
    }
    else return true;
}

