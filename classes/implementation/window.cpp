#include <iostream>
#include "window.h"

window::window(GLint WIDTH, GLint HEIGHT, const char* wintitle) {
    if(!glfwInit()) {
        std::cout << "Error" << std::endl;
        glfwTerminate();                // terminate GLFW
        throw std::runtime_error("Error in initiating GLFW");
    }

    // set some properties
    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwInitHint(GLFW_OPENGL_CORE_PROFILE,GL_TRUE);
    glfwInitHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    win = glfwCreateWindow(WIDTH,HEIGHT,wintitle,NULL,NULL);

    // check for error in creation of mainWindow
    if(!win) {
        std::cout << "ERROR" << std::endl;
        glfwDestroyWindow(win);
        glfwTerminate();
        throw std::runtime_error("Error in creating window");
    }

    // get the buffer dimaension data
    int bufferWidth{0},bufferHeight{0};
    glfwGetFramebufferSize(win,&bufferWidth,&bufferHeight);

    // make mainWindow the current context
    glfwMakeContextCurrent(win);

    // enable experimental featureset
    glewExperimental = GL_TRUE;

    // Intialise GLEW and check for error in initialisation
    if(glewInit()!= GLEW_OK) {
        std::cout << "ERROR" << std::endl;
        glfwDestroyWindow(win);
        glfwTerminate();
        throw std::runtime_error("Error in initialising GLEW");
    }
}