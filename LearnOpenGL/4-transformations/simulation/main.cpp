#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "window.h"

using namespace std;

glm::vec3 u = glm::vec3(2,0,0);     // intial velocity of the particle
glm::vec3 g = glm::vec3(0,-9.8,0);  // gravitational constant

// window dimensions
const GLuint WIDTH=800,HEIGHT=600;

int main() {
    // vertex data of the objects
    GLfloat vertexData[] {
        0,0,0,
        0.5,-1,0,
        -0.5,-1,0
    };

    // create a blank window
    window mainWindow(WIDTH,HEIGHT,"LearnOpenGL");
    // compile and link the shader program
    shader shaderProgram("vertexShader.GLSL","fragmentShader.GLSL");

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

    float sFactor = 0.05;
    glm::vec3 scale_vector = glm::vec3(sFactor,sFactor,sFactor);

    glm::mat4 trans = glm::mat4(1.0f);
    // here transforms are applied to scale the triangle and move it to the lower left corner
    trans = glm::translate(trans,glm::vec3(-0.95,-0.25,0));
    trans = glm::scale(trans,scale_vector);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID,"transform"),1,GL_FALSE,glm::value_ptr(trans));

    glm::vec3 displacement_vector = glm::vec3(0);

    while(!glfwWindowShouldClose(mainWindow.win)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0,0,0,1);

        // get the running time in seconds
        GLfloat time = glfwGetTime();

        // -------------------------------
        // // simulate freely falling body
        // displacement_vector = (time*glm::vec3(u) + (glm::vec3(g))*time*(time/2));
        // displacement_vector = glm::vec3(displacement_vector*glm::vec3(0.01));
        // -------------------------------

        // ----------------------------------------------
        // simulate projectile motion of a particle in 2d
        if(displacement_vector.y<-1.055) {}
        else {displacement_vector = glm::vec3((u*time) + g*(time*time*float(0.5))*float(0.5))*float(0.4);
        // NOTE: In above statement the formula is incorrect according to physics because of the constant
        // at the end of the statement which is added only to slow down the particle animation
        // ----------------------------------------------

        // apply transforms
        trans = glm::translate(trans,displacement_vector);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID,"transform"),1,GL_FALSE,glm::value_ptr(trans));
        }
        cout << displacement_vector.x << ", " << displacement_vector.y << ", " << displacement_vector.z << "\n";
        // draw the triangle
        shaderProgram.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);     // draw the triangles
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow.win);
    }

    return 0;
}