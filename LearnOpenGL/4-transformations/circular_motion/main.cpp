#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"
#include "shader.h"

using namespace std;

const GLint WIDTH=600,HEIGHT=600;

int main() {
    window mainWindow(WIDTH,HEIGHT,"Learn OpenGL");                     // create a window
    shader shaderProgram("vertexShader.GLSL","fragmentShader.GLSL");    // compile and link shader

    // vertex data
    GLfloat vertexData[] = {
         0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
         0.5f,-0.5f, 0.0f,
        -0.5f,-0.5f, 0.0f,
         0.5f,-0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    float time=0;

    // buffer objects
    GLuint VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
        glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    GLuint location = glGetUniformLocation(shaderProgram.ID,"transform");

    float scaleFactor=0.1, radius=0.4;
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform,glm::vec3(radius,0,0));
    transform = glm::rotate(transform,glm::radians(40.0f),glm::vec3(0,0,1));
    transform = glm::scale(transform,glm::vec3(scaleFactor));

    while(!glfwWindowShouldClose(mainWindow.win)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0,0,0,1);

        // get the running time
        // time = glfwGetTime();
        
        glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(transform));
        shaderProgram.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,6);
        shaderProgram.unuse();

        glfwSwapBuffers(mainWindow.win);
    }

    return 0;
}