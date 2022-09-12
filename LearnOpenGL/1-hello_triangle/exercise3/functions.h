#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <GL/glew.h>

bool isShaderCompiled(GLuint shader);
bool isShaderProgramLinked(GLuint shaderProgram);

bool attachShader(GLuint shaderProgram, GLuint shaderType, const char* shaderSource);

#endif