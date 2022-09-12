#include <iostream>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// Vertex shader
const char* vertexShader = "        \n\
#version 330                        \n\
                                    \n\
layout (location=0) in vec3 pos;    \n\
                                    \n\
void main() {                       \n\
    gl_Position = vec4(pos,1.0f);   \n\
}                                   \n\
\0";

// Fragment shader
const char* fragmentShader = "                  \n\
#version 330                                    \n\
                                                \n\
out vec4 fragmentcolour;                        \n\
                                                \n\
void main() {                                   \n\
    fragmentcolour = vec4(1.0f,1.0f,0.0f,1.0f); \n\
}                                               \n\
\0";

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

void createTriangle();
void compileShader();
void addShader(GLuint shaderProgram, const char* shaderSource, GLenum shaderType);



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

    createTriangle();
    compileShader();

    while(!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
            glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES,0,3);
            glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}

void addShader(GLuint shaderProgram, const char* shaderSource, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);
    
    const GLchar* theCode[1];
    theCode[0] = shaderSource;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderSource);

    glShaderSource(theShader,1,theCode,codeLength);
    glCompileShader(theShader);

    GLint result=0;
    GLchar infoLog[512]={0};

    glGetShaderiv(theShader,GL_COMPILE_STATUS,&result);
    if(!result) {
        glGetShaderInfoLog(theShader,sizeof(infoLog),NULL,infoLog);
        cout << infoLog << endl;
        return;
    }

    glAttachShader(shaderProgram,theShader);
}


void createTriangle() {
    GLfloat vertices[] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
        glGenBuffers(1,&VBO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void compileShader() {
    shader = glCreateProgram();

    if(!shader) {
        cout << "error creating shader program" << endl;
        return;
    }

    addShader(shader,vertexShader,GL_VERTEX_SHADER);
    addShader(shader,fragmentShader,GL_FRAGMENT_SHADER);

    glLinkProgram(shader);
    GLint result=0;
    GLchar infoLog[512]={0};

    glGetProgramiv(shader,GL_LINK_STATUS,&result);
    if(!result) {
        glGetProgramInfoLog(shader,sizeof(infoLog),NULL,infoLog);
        cout << infoLog << endl;
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader,GL_VALIDATE_STATUS,&result);
    if(!result) {
        glGetProgramInfoLog(shader,sizeof(infoLog),NULL,infoLog);
        cout << infoLog << endl;
        return;
    }
    
}