#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "functions.h"

using namespace std;

// Window dimensions
const GLint HEIGHT = 600,WIDTH = 800;

// vertex shader source
const char* vertexShaderSource = "\n\
#version 330 core\n\
\n\
layout (location=0) in vec3 position;\n\
\n\
void main() {\n\
    gl_Position = vec4(position,1.0f);\n\
}\n\
\0";

// fragment shader source
const char* fragmentShaderSource = "\n\
#version 330 core\n\
\n\
out vec4 fragmentColour;\n\
\n\
void main() {\n\
    fragmentColour = vec4(1.0f,0.0f,0.0f,1.0f);\n\
}\n\
\0";


int main() {
    // Initialise GLFW
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

    GLfloat vertices[] = {
        // triangle1
        -0.9f,-0.4f,0.0f,
        -0.3f,-0.4f,0.0f,
        -0.6f,0.4f,0.0f,
        // triangle2
        0.9f,-0.4f,0.0f,
        0.3f,-0.4f,0.0f,
        0.6f,0.4f,0.0f
    };

    // declare shader objects
    GLuint vertexShader,fragmentShader;
    GLuint shaderProgram;

    // create shader program id
    shaderProgram = glCreateProgram();
    // create shader ids
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // copy shader source in shaders
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);

    // compile shaders
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // check for errors
    if(!isShaderCompiled(vertexShader)) return 1;
    if(!isShaderCompiled(fragmentShader)) return 1;

    // attach the shaders to the shader program
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);

    // link shader program
    glLinkProgram(shaderProgram);
    // check for linking errors
    if(!isShaderProgramLinked(shaderProgram)) return 1;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // declaring the required variables
    GLuint triangleVAO[2];
    GLuint triangleVBO[2];

    // create the required ids
    glGenVertexArrays(2,triangleVAO);
    glGenBuffers(2,triangleVBO);

    // copy data into first VBO
    glBindVertexArray(triangleVAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER,triangleVBO[0]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices)/2,vertices,GL_STATIC_DRAW);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    // copy data into second VBO
    glBindVertexArray(triangleVAO[1]);
        glBindBuffer(GL_ARRAY_BUFFER,triangleVBO[1]);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices)/2,&(vertices[9]),GL_STATIC_DRAW);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    // mainWindow event loop
    while(!glfwWindowShouldClose(mainWindow)) {
        // poll events like clicking, button push etc
        glfwPollEvents();

        glClearColor(0.0f,0.0f,0.0f,1.0f);          // clear the window with the given colour
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

            glBindVertexArray(triangleVAO[0]);
                glDrawArrays(GL_TRIANGLES,0,3);
            glBindVertexArray(0);


            glBindVertexArray(triangleVAO[1]);
                glDrawArrays(GL_TRIANGLES,0,3);
            glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);        // swap the buffers so we can see the result
    }


    return 0;
}