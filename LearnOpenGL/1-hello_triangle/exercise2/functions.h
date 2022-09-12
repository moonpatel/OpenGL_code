#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <GL/glew.h>

bool isShaderCompiled(GLuint shader);
bool isShaderProgramLinked(GLuint shaderProgram);

void addShader(GLuint shaderProgram, GLuint shader, const char* shaderSource);

#endif