#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "../../../../classes/headers/shader.h"
#include "../../../../classes/headers/window.h"
// #include "window.h"

// Window dimensions
GLuint WIDTH = 800, HEIGHT = 600;
float fov = 45.0f;
const float sensitivity = 0.1f;
bool firstMouse = true;
float cameraSpeed = 0.05f;
float lastX = 400;
float lastY = 300;
float yaw = -90.0f;
float pitch = 0.0f;

// camera properties
glm::vec3 cameraPos = glm::vec3(0.0f,0.0f,3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f,1.0f,0.0f);

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_callback_disabled(GLFWwindow* window, double xpos, double ypos);
// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void (*func_ref)(GLFWwindow*,double,double);

using namespace std;


window mainWindow(WIDTH,HEIGHT,"LearnOpenGL");      // main window
shader shaderProgram("vertexShader.GLSL","fragmentShader.GLSL");    // compile and link shaders
int main() {

    GLfloat vertexData[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // random positions for cubes
    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    int height,width,nrChannels;
    unsigned char* imgData = stbi_load("grassTexture.png",&width,&height,&nrChannels,0);
    // image loading
    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(imgData) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,imgData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        cout << "Failed to load textures" << "\n";

    stbi_image_free(imgData);

    // buffer objects
    GLuint VAO,VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER,VBO);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);
            // position data
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),0);
            glEnableVertexAttribArray(0);
            // texture coordinates data
            glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER,0);

    glBindVertexArray(0);

    glm::mat4 view;
    view = glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
    glm::mat4 projection = glm::mat4(1);
    glm::vec3 direction;
    
    direction.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);


    float radius = 10.0f;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glEnable(GL_DEPTH_TEST);
    
    func_ref = &mouse_callback;
    glfwSetInputMode(mainWindow.win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while(!glfwWindowShouldClose(mainWindow.win)) {
        // called when cursor is moved
        glfwSetCursorPosCallback(mainWindow.win,func_ref);
        // called when mouse wheel is scrolled
        glfwSetScrollCallback(mainWindow.win,scroll_callback);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame-lastFrame;
        lastFrame = currentFrame;
        cameraSpeed = 2.5f*deltaTime;

        processInput(mainWindow.win);
        view = glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
        projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

        glfwPollEvents();
        glClearColor(0.2,0.2,0.2,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID,"projection"),1,GL_FALSE,glm::value_ptr(projection));

        glBindTexture(GL_TEXTURE_2D,texture);
        shaderProgram.use();
        glBindVertexArray(VAO);
        for(int i=0; i<10; i++) {
            glm::mat4 model = glm::mat4(1);
            model = glm::translate(model,cubePositions[i]);
            float angle = i*10.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1,0.3,0.5));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID,"model"),1,GL_FALSE,glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES,0,36);
        }
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow.win);
    }


    return 0;
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
        cameraPos += cameraSpeed*cameraFront;
    if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
        cameraPos -= cameraSpeed*cameraFront;
    if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraUp, cameraFront))*cameraSpeed;
    if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraUp, cameraFront))*cameraSpeed;
    if(glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS)
        cameraPos += cameraSpeed*cameraUp;
    if(glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS)
        cameraPos -= cameraSpeed*cameraUp;
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS) {
        glfwSetInputMode(mainWindow.win,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
        func_ref = &mouse_callback_disabled;
        firstMouse = true;
    }
    if(glfwGetKey(window,GLFW_KEY_TAB)==GLFW_PRESS) {
        glfwSetInputMode(mainWindow.win,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
        func_ref = &mouse_callback;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch>89.0f)
        pitch = 89.0f;
    if(pitch<-89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void mouse_callback_disabled(GLFWwindow* window, double xpos, double ypos) {
    return;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= float(yoffset);
    if(fov<1.0f)
        fov = 1.0f;
    else if(fov>45.0f)
        fov = 45.0f;
}