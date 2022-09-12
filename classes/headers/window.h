#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class window {
public:
    GLFWwindow* win;

    window(GLint WIDTH, GLint HEIGHT, const char* wintitle);

};

#endif