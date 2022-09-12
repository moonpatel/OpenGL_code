#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// options for camera movement
enum cameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// default camera parameters
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class camera
{
public:
    // camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // euler angles
    float yaw;
    float pitch;
    // camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    // constructor with vectors
    camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Up = glm::vec3(0.0f, 1.0, 0.0f), float Yaw = YAW, float Pitch = PITCH) : front{glm::vec3(0.0f, 0.0f, -1.0f)}, movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {
        position = pos;
        worldUp = Up;
        yaw = Yaw;
        pitch = Pitch;
        updateCameraVectors();
    }

    // constructor with scalar values
    camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw_val, float picth_val) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {
        position = glm::vec3(posX, posY, posZ);
        worldUp = glm::vec3(upX, upY, upZ);
        yaw = yaw_val;
        pitch = picth_val;
    }

    // returns the calculated view matrix
    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    // processes input received from any keyboard-like input systems.
    // Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void processKeyboard(cameraMovement direction_val, float deltaTime) {
        float velocity = movementSpeed*deltaTime;
        if(direction_val == FORWARD)
            position += front*velocity;
        if(direction_val == BACKWARD)
            position -= front*velocity;
        if(direction_val == LEFT)
            position -= right*velocity;
        if(direction_val == RIGHT)
            position += right*velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processMouseMovement(float xoffset, float yoffset, GLboolean constraintPitch = true)
    {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure when pitch is out of bounds, screen doesn't get flipped
        if(constraintPitch) {
            if(pitch > 89.0f)
                pitch = 89.0f;
            if(pitch < -89.0f)
                pitch = -89.0f;
        }

        // update front, right, and up vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void processMouseScroll(float yoffset) {
        zoom -= float(yoffset);
        if(zoom < 1.0f)
            zoom = 1.9f;
        if(zoom > 45.0f)
            zoom = 45.0f;
    }

private:
    // calculates the front vector from the camera's (updated) Euler angles
    void updateCameraVectors()
    {
        // calculate the new front vector
        glm::vec3 front_vec;
        front_vec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front_vec.y = sin(glm::radians(pitch));
        front_vec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front_vec);
        // recalculate the right and up vector
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
};

#endif