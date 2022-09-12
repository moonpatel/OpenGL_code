#include <iostream>
#include <iomanip>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "window.h"

using namespace std;

// window dimensions
const GLuint WIDTH=1366,HEIGHT=768;

int main() {
    int numOfVertices=3000;
    float offset=-100;
    GLfloat vertexData[3*numOfVertices];

    GLfloat m,c;
    m=1.0f, c=0.0f;

    for(int i=0; i<numOfVertices; i++) {
        vertexData[3*i] = (i-49)*0.05 + offset;
        // vertexData[3*i+1] = m*vertexData[3*i] + c;                  // straight line
        vertexData[3*i+1] = (vertexData[3*i])*(vertexData[3*i]); // parabola
        // vertexData[3*i+1] = sin(vertexData[3*i]);                // sine
        // vertexData[3*i+1] = sqrt(vertexData[3*i]);               // square root
        // vertexData[3*i+1] = log(vertexData[3*i]);                // logarithm
        vertexData[3*i+2] = 0;
    }

    // create a blank window
    window mainWindow(WIDTH,HEIGHT,"LearnOpenGL");
    // compile and link the shader program
    shader lineShader("vs.GLSL","fs.GLSL");

    // copying data in the buffer objects
    GLuint VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
            glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);


    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::scale(transform,glm::vec3(1,float(WIDTH)/HEIGHT,0));

    float point_size = 3;
    glPointSize(point_size);     // set the size of points

    while(!glfwWindowShouldClose(mainWindow.win)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1,0.1,0.1,1);

        if(glfwGetKey(mainWindow.win,GLFW_KEY_Z)==GLFW_PRESS) {
            if(glfwGetKey(mainWindow.win,GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS) {
                transform = glm::scale(transform,glm::vec3(1.01,1.01,1.01));
                glPointSize(point_size*1.01);
            }
            else {
                transform = glm::scale(transform,glm::vec3(1.1,1.1,1.1));
                glPointSize(point_size*1.1);
            }
        }
        if(glfwGetKey(mainWindow.win,GLFW_KEY_M)==GLFW_PRESS) {
            transform = glm::scale(transform,glm::vec3(0.9,0.9,0.9));
            glPointSize(point_size);
        }
        if(glfwGetKey(mainWindow.win,GLFW_KEY_RIGHT)==GLFW_PRESS)
            transform = glm::translate(transform,glm::vec3(-0.01,0.0,0.0));
        if(glfwGetKey(mainWindow.win,GLFW_KEY_LEFT)==GLFW_PRESS)
            transform = glm::translate(transform,glm::vec3(0.01,0.0,0.0));
        if(glfwGetKey(mainWindow.win,GLFW_KEY_UP)==GLFW_PRESS)
            transform = glm::translate(transform,glm::vec3(0.0,-0.01,0.0));
        if(glfwGetKey(mainWindow.win,GLFW_KEY_DOWN)==GLFW_PRESS)
            transform = glm::translate(transform,glm::vec3(0.0,0.01,0.0));

        glUniformMatrix4fv(glGetUniformLocation(lineShader.ID,"transform"),1,GL_FALSE,glm::value_ptr(transform));

        
        glBindVertexArray(VAO);
        
        glUniform4f(glGetUniformLocation(lineShader.ID,"Color"),0.1,0.7,0.2,1);
        glUseProgram(lineShader.ID);
        glDrawArrays(GL_LINE_STRIP,0,numOfVertices);
        // glUniform4f(glGetUniformLocation(lineShader.ID,"Color"),0.7,0.2,0.1,1);
        // glDrawArrays(GL_POINTS,0,numOfVertices);       // draw the points

        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow.win);
    }

    return 0;
}