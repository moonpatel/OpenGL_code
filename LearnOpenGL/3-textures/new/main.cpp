#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"

using namespace std;

// Window dimensions
const GLint HEIGHT = 600,WIDTH = 800;

GLuint VAO,VBO,EBO,shaderProgram;

// vertex data
GLfloat vertices[] = {
    // position     // color    // texture
    0.0,0.5,0,      1,0,0,      0.5,1,        // top
    0.5,-0.5,0,     0,1,0,      1,0,        // bottom right
    -0.5,-0.5,0,    0,0,1,      0,0,        // bottom left
};


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

    int width, height, nrChannels;
    unsigned char* data = stbi_load("container.jpg",&width,&height,&nrChannels,0);


    // texture are referenced by IDs similar to VAO and VBO
    GLuint texture;
    glGenTextures(1,&texture);  // gen the ID for texture
    glBindTexture(GL_TEXTURE_2D, texture);      // bind the texture
        // set the texture wrapping and filtering options
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        if(data) {
            glTexImage2D(GL_TEXTURE_2D, 0,GL_RG,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);   // creates texture from the loaded image
            glGenerateMipmap(GL_TEXTURE_2D);        // create the mipmaps for the texture currently bound
        }
        else cout << "Failed to load texture" << endl;
    stbi_image_free(data);

// compiling and linking shader program
    shader shaderProgram("vertexShader.GLSL","fragmentShader.GLSL");

// creating and filling buffers
    GLuint VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindVertexArray(0);

// #########################################################################################################

    // glPolygonMode(GL_FRONT,GL_LINE);

    // mainWindow event loop
    while(!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();
        glClearColor(0.0f,0.0f,0.0f,1.0f);          // clear the window with the given colour
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D,texture);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwSwapBuffers(mainWindow);        // swap the buffers so we can see the result
    }

    glfwTerminate();


    return 0;
}