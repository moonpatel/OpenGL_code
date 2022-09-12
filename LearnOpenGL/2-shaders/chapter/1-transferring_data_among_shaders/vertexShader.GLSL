#version 330 core

layout (location = 0) in vec3 position;
out vec3 ourColor;

void main() {
    gl_Position = vec4(position,1.0f);
    if(position.x>=0)
        ourColor = vec3(1,0.3,0.4);
    else
        ourColor = vec3(0,0,0);
}