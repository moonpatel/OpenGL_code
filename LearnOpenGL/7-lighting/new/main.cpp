#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../../classes/headers/shader.h"
#include "../../../classes/headers/window.h"

// Window dimensions
GLuint WIDTH=800,HEIGHT=600;

using namespace std;

glm::vec3 lightColor = glm::vec3(1,1,1);
glm::vec3 objectColor = glm::vec3(1,0,0);

int main() {
    window mainWindow(WIDTH,HEIGHT,"LearnOpenGL");      // create window
    shader lightShader("lightVShader.GLSL","lightFShader.GLSL");
    shader cubeShader("cubeVShader.GLSL","cubeFShader.GLSL");

    GLfloat vertexData[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
    // buffer objects
    GLuint lightVAO,cubeVAO,VBO;
    glGenVertexArrays(1,&lightVAO);
    glGenVertexArrays(1,&cubeVAO);
    glGenBuffers(1,&VBO);

    // copying data into buffer
    glBindVertexArray(lightVAO);

        glBindBuffer(GL_ARRAY_BUFFER,VBO);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);
            // position data
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),0);
            glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);

    glBindVertexArray(cubeVAO);

        glBindBuffer(GL_ARRAY_BUFFER,VBO);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);

    float y = 0;
    glm::vec3 lightPosition = glm::vec3(2,1,0);
    // transform matrices
    glm::mat4 lightModel = glm::mat4(1);
    glm::mat4 cubeModel = glm::mat4(1);
    glm::mat4 view = glm::mat4(1);
    glm::mat4 projection = glm::mat4(1);

    lightModel = glm::translate(lightModel,lightPosition);
    lightModel = glm::scale(lightModel,glm::vec3(0.1,0.1,0.1));
    // cubeModel = glm::scale(cubeModel,glm::vec3(2,10,10));
    view = glm::translate(view,glm::vec3(0,-1,-6));
    view = glm::rotate(view,glm::radians(-45.0f),glm::vec3(0,1,0));
    view = glm::scale(view,glm::vec3(0.5,0.5,0.5));
    projection = glm::perspective(glm::radians(45.0f),800.0f/600.0f,0.1f,100.0f);

    float time;

    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(mainWindow.win)) {
        glfwPollEvents();
        glClearColor(0.05,0.1,0.05,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(glfwGetKey(mainWindow.win,GLFW_KEY_A)==GLFW_PRESS)
            lightPosition.x += 0.01;
        if(glfwGetKey(mainWindow.win,GLFW_KEY_D)==GLFW_PRESS)
            lightPosition.x -= 0.01;

        lightShader.use();
        // update the transforms
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID,"lightModel"),1,GL_FALSE,glm::value_ptr(lightModel));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID,"projection"),1,GL_FALSE,glm::value_ptr(projection));
        glUniform3f(glGetUniformLocation(lightShader.ID,"lightColor"),lightColor.x,lightColor.y,lightColor.z);


        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES,0,36);
        glBindVertexArray(0);
        lightShader.unuse();

        cubeShader.use();
        glUniformMatrix4fv(glGetUniformLocation(cubeShader.ID,"cubeModel"),1,GL_FALSE,glm::value_ptr(cubeModel));
        glUniformMatrix4fv(glGetUniformLocation(cubeShader.ID,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(cubeShader.ID,"projection"),1,GL_FALSE,glm::value_ptr(projection));
        glUniform3f(glGetUniformLocation(cubeShader.ID,"lightColor"),lightColor.x,lightColor.y,lightColor.z);
        glUniform3f(glGetUniformLocation(cubeShader.ID,"objectColor"),objectColor.x,objectColor.y,objectColor.z);
        glUniform3f(glGetUniformLocation(cubeShader.ID,"lightPos"),lightPosition.x,lightPosition.y,lightPosition.z);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES,0,36);
        glBindVertexArray(0);

        cubeShader.unuse();

        glfwSwapBuffers(mainWindow.win);
    }


    return 0;
}