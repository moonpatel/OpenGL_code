#include <iostream>

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
    window mainWindow(WIDTH,HEIGHT,"Learn OpenGL");
    shader shaderProgram("vertexShader.GLSL","fragmentShader.GLSL");

    // vertex data
    GLfloat vertexData[] = {
        0.5f,-0.5f,0.0f,     1.0f,0.0f,0.0f,
        -0.5f,-0.5f,0.0f,    0.0f,1.0f,0.0f,
        0.0f,0.35f,0.0f,      0.0f,0.0f,1.0f
    };

    // 
    // trans = glm::rotate(trans,glm::radians(90.0f),glm::vec3(0.0f,0.0f,1.0f));    // rotate the vector


    float xOffset = 0.0f;
    float yOffset = 0.0f;
    float offset = 0.005f;
    float rotationalOffset = 0.0f;
    float rotOffsetConst = 1.0f;
    float scaleFactor = 0.8f;

    // buffer objects
    GLuint VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    GLuint location = glGetUniformLocation(shaderProgram.ID,"transform");

    while(!glfwWindowShouldClose(mainWindow.win)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0,0,0,1);

        if(glfwGetKey(mainWindow.win,GLFW_KEY_A)==GLFW_PRESS)
            xOffset -= offset;
        else if(glfwGetKey(mainWindow.win,GLFW_KEY_D)==GLFW_PRESS)
            xOffset += offset;
        else if(glfwGetKey(mainWindow.win,GLFW_KEY_W)==GLFW_PRESS)
            yOffset += offset;
        else if(glfwGetKey(mainWindow.win,GLFW_KEY_S)==GLFW_PRESS)
            yOffset -= offset;
        else if(glfwGetKey(mainWindow.win,GLFW_KEY_RIGHT)==GLFW_PRESS)
            rotationalOffset += rotOffsetConst;
        else if(glfwGetKey(mainWindow.win,GLFW_KEY_LEFT)==GLFW_PRESS)
            rotationalOffset -= rotOffsetConst;
        else if(glfwGetKey(mainWindow.win,GLFW_KEY_KP_ADD)==GLFW_PRESS)
            scaleFactor += 0.01;
        else if(glfwGetKey(mainWindow.win,GLFW_KEY_KP_SUBTRACT)==GLFW_PRESS)
            scaleFactor -= 0.01;
        else if(glfwGetKey(mainWindow.win,GLFW_KEY_BACKSPACE)==GLFW_PRESS)
            {
                xOffset = 0;
                yOffset = 0;
                rotationalOffset = 0;
                scaleFactor = 1;
            }


        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans,glm::vec3(xOffset,yOffset,0.0f));
        trans = glm::rotate(trans,glm::radians(-rotationalOffset),glm::vec3(0.0,0.0,1.0));
        trans = glm::scale(trans,glm::vec3(scaleFactor,scaleFactor,scaleFactor));
        
        shaderProgram.use();
        glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        // shaderProgram.unuse();

        glfwSwapBuffers(mainWindow.win);
    }

    return 0;
}