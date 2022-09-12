#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;


int main() {
    if(!glfwInit()) {
        cout << "ERROR" << endl;
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH,HEIGHT,"OpenGL",NULL,NULL);

    if(!mainWindow) {
        cout << "ERROR" << endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    int bufferWidth{0},bufferHeight{0};
    glfwGetFramebufferSize(mainWindow,&bufferWidth,&bufferHeight);

    glfwMakeContextCurrent(mainWindow);

    glewExperimental = GL_TRUE;

    if(glewInit()!= GLEW_OK) {
        cout << "ERROR" << endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
    }

    glViewport(0,0,bufferWidth,bufferHeight);

    while(!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();
        glClearColor(1.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}