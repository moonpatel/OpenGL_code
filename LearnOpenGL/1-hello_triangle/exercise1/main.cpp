#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// Window dimensions
const GLint HEIGHT = 600,WIDTH = 800;

GLuint VAO,VBO,shaderProgram;

// vertex data
GLfloat vertices[] = {
    // triangle1
    -0.9f,-0.4f,0.0f,
    -0.6f,0.4f,0.0f,
    -0.3f,-0.4f,0.0f,
    // tiangle2
    0.9f,-0.4f,0.0f,
    0.6f,0.4f,0.0f,
    0.3f,-0.4f,0.0f
};

// vertex shader source
const char* vertexShaderSource = "          \n\
#version 330 core                           \n\
                                            \n\
layout (location=0) in vec3 position;       \n\
                                            \n\
void main() {                               \n\
    gl_Position = vec4(position,1.0f);      \n\
}\0";

// fragment shader source
const char* fragmentShaderSource = "        \n\
#version 330 core                           \n\
                                            \n\
out vec4 colour;                            \n\
                                            \n\
void main() {                               \n\
    colour = vec4(1.0f,0.0f,0.0f,1.0f);     \n\
}\0";


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

    // Create a shader program id
    shaderProgram = glCreateProgram();


    // set the dimensions in which OpenGL should draw
    glViewport(0,0,bufferWidth,bufferHeight);

    // Create the shader ids
    GLuint vertexShader,fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // copy the shader source in the respetive shaders
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);

    // compile the shaders
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);


    // to store information about compilation and linking status
    int success;
    char infoLog[1024];

// -------------------------------------------------------------------------------------------------------
// Check for vertex shader compilation error
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success) {
        glGetShaderInfoLog(vertexShader,1024,NULL,infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << endl;
    }
// Check for fragment shader compilation error
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader,1024,NULL,infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << endl;
    }
// ========================================================================================================

    // Attach the shaders to the shader program
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);

    // Link the shader program
    glLinkProgram(shaderProgram);

// --------------------------------------------------------------------------------------------------------
// Check for linking error
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram,1024,NULL,infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog << endl;
    }
// ========================================================================================================

    // Delete the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



// ########################################################################################################
    glGenVertexArrays(1,&VAO);          // create id for VAO
    glBindVertexArray(VAO);             // bind VAO
        glGenBuffers(1,&VBO);           // create id for VBO
        glBindBuffer(GL_ARRAY_BUFFER,VBO);      // bind VBO

            // copy vertex data in currently bound VBO
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);       // make VAO point to the vertex attribute
            glEnableVertexAttribArray(0);                           // Enable the vertex attribute

        glBindBuffer(GL_ARRAY_BUFFER,0);        // Unbind the VBO
    glBindVertexArray(0);           // Unbind the VAO
// #########################################################################################################



    // mainWindow event loop
    while(!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();
        glClearColor(0.0f,0.0f,0.0f,1.0f);          // clear the window with the given colour
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES,0,6);

        glfwSwapBuffers(mainWindow);        // swap the buffers so we can see the result
    }


    return 0;
}