#include <iostream>
#include <cstring>
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

bool attachShader(GLuint shaderProgram, GLenum shaderType, const char* shaderSource) {
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderSource;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderSource);

    glShaderSource(theShader,1,theCode,codeLength);
    glCompileShader(theShader);

    GLint success = 0;
    GLchar infoLog[512]={0};

    glGetShaderiv(theShader,GL_COMPILE_STATUS,&success);
    if(!success) {
        glGetShaderInfoLog(theShader,512,NULL,infoLog);
        std::cout << infoLog << std::endl;
        return false;
    }

    glAttachShader(shaderProgram,theShader);
    return true;
}