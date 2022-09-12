#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../../../shader/shader.h"
#include "../../../../shader/shader.cpp"

using namespace std;

// Window dimensions
const GLint HEIGHT = 600, WIDTH = 800;


int main() {

    if(!glfwInit()) {
        cout << "Error" << endl;
        glfwTerminate();                // terminate GLFW
        return 1;
    }

    // set some properties
    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwInitHint(GLFW_OPENGL_CORE_PROFILE,GL_TRUE);
    glfwInitHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    // create the main window object
    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH,HEIGHT,"OpenGL",NULL,NULL);

// --------------------------------------------------------------------------------------------------------
// check for error in creation of mainWindow
    if(!mainWindow) {
        cout << "ERROR" << endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
// ========================================================================================================

    // get the buffer dimaension data
    int bufferWidth{0},bufferHeight{0};
    glfwGetFramebufferSize(mainWindow,&bufferWidth,&bufferHeight);

    // make mainWindow the current context
    glfwMakeContextCurrent(mainWindow);

    // enable experimental featureset
    glewExperimental = GL_TRUE;

// --------------------------------------------------------------------------------------------------------
// Intialise GLEW and check for error in initialisation
    if(glewInit()!= GLEW_OK) {
        cout << "ERROR" << endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
    }
// ========================================================================================================

    // triangle's vertex data
    float vertexAttribs[] = {
        // location         // color
         0.5,-0.5,0.0,      1.0f,0.0f,0.0f,      // bottom left
        -0.5,-0.5,0.0,      0.0f,1.0f,0.0f,      // bottom right
         0.0, 0.5,0.0,      0.0f,0.0f,1.0f       // top
    };

    GLuint VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertexAttribs),vertexAttribs,GL_STATIC_DRAW);
            // position attribute
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
            glEnableVertexAttribArray(0);
            // color attribute
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    float offset_horizontal = 0.1f;

    shader shaderProgram{"vertexShader.GLSL","fragmentShader.GLSL"};
    shaderProgram.use();
        int unilocation = glGetUniformLocation(shaderProgram.ID,"offset");
        glUniform1f(unilocation,offset_horizontal);
    shaderProgram.unuse();

    // mainWindow event loop
    while(!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();
        glClearColor(0.0f,0.0f,0.0f,1.0f);          // clear the window with the given colour
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
            glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES,0,3);
            glBindVertexArray(0);
        shaderProgram.unuse();

        glfwSwapBuffers(mainWindow);        // swap the buffers so we can see the result
    }

    


    return 0;
}